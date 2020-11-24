#include "HSVFilter.h"


void HSVFilter::getRedOnlyImage(cv::InputArray _src, cv::OutputArray _dst, FilterOption option)
{
	option.settingColor(red);
	getOnlyImage(_src, _dst, option);
}

void HSVFilter::getBlueOnlyImage(cv::InputArray _src, cv::OutputArray _dst, FilterOption option)
{
	option.settingColor(blue);
	getOnlyImage(_src, _dst, option);
}

void HSVFilter::getGreenOnlyImage(cv::InputArray _src, cv::OutputArray _dst, FilterOption option)
{
	option.settingColor(green);
	getOnlyImage(_src, _dst, option);
}

//�� ������ �����ϸ� �ߺ��Ǵ� �����̱⿡ �ϳ��� �Լ��� ���� ����
void HSVFilter::getOnlyImage(cv::InputArray _src, cv::OutputArray _dst, FilterOption option)
{
	//src, dst ó��
	cv::Mat src = _src.getMat();
	_dst.create(src.size(), CV_8UC1);
	cv::Mat dst = _dst.getMat();

	//���̿� �ʺ� ����
	const int height = src.size().height;
	const int width = src.size().width;

	//s,v �ִ� �ּ� ������, 0=min, 1=max
	int sMinMax[2] = { 255,0 };
	int vMinMax[2] = { 255,0 };

	//������ ���� map ����
	int** map;
	map = new int* [height];
	for (int count = 0; count < height; count++) {
	
		map[count] = new int[width] {0};
	}

	//hsv �м��� ���� hsv�� mat ����
	cv::Mat hsvMat;
	cv::cvtColor(src, hsvMat, cv::COLOR_RGB2HSV);

	//s�� v ��Ʈ��Ī�� ���� �ּڰ�, �ִ� ����
	for (int y = 0; y < height; y++)
		for (int x = 0; x < width; x++) {
		
			sMinMax[0] > hsvMat.at<cv::Vec3b>(y, x)[1] ? 
				sMinMax[0] = hsvMat.at<cv::Vec3b>(y, x)[1] : false;
			sMinMax[1] < hsvMat.at<cv::Vec3b>(y, x)[1] ? 
				sMinMax[1] = hsvMat.at<cv::Vec3b>(y, x)[1] : false;

			vMinMax[0] > hsvMat.at<cv::Vec3b>(y, x)[2] ?
				vMinMax[0] = hsvMat.at<cv::Vec3b>(y, x)[2] : false;
			vMinMax[1] < hsvMat.at<cv::Vec3b>(y, x)[2] ?
				vMinMax[1] = hsvMat.at<cv::Vec3b>(y, x)[2] : false;
		}

	//��Ʈ��Ī �� �ٿ���� ��� ���� Ȯ��
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {

			//����� ���Ǽ��� ���� hsv�� ����
			int h = hsvMat.at<cv::Vec3b>(y, x)[0];
			int s = hsvMat.at<cv::Vec3b>(y, x)[1];
			int v = hsvMat.at<cv::Vec3b>(y, x)[2];

			//s�� v ��Ʈ��Ī
			s = (s - sMinMax[0]) * 255.0 / (double)(sMinMax[1] - sMinMax[0]);
			v = (v - vMinMax[0]) * 255.0 / (double)(vMinMax[1] - vMinMax[0]);


			//�ٿ���� �ۿ� ������ ��Ƽ���� �ѱ��, ���η� ���� ��� ���� ���� ����
			if (isInBoundary(h, s, v, option))
				continue;

			//��Ƽ���� �ȳѾ�����, �� �ٿ���� ������ ��� �ʿ� �ش� ��ǥ�� 1�� ���
			map[y][x] = 1;
		}
	}

	//���� ���� dst�� 1�� ��� 255����, 0�� ��� 0���� ����
	for (int y = 0; y < height; y++)
		for (int x = 0; x < width; x++) {
		
			if (map[y][x] == 1)
				dst.at<uchar>(y, x) = (unsigned char)255;
			else
				dst.at<uchar>(y, x) = (unsigned char)0;
		}
	
}

//h���� ���, 180=0�̹Ƿ�, ��ȯ�� ����� ������ �ٿ���� üũ �Լ� ����
bool HSVFilter::HBoudaryCheck(const int h, const int baseColor, const int boundary)
{
	int underH = h - 180;
	int upperH = h + 180;

	int min = baseColor - boundary;
	int max = baseColor + boundary;

	if ((h > min && h < max) ||
		(underH > min && underH < max) ||
		(upperH > min && upperH < max))
		return false;


	return true;
}

//�ٿ���� �� ���� ���� Ȯ��, �ٿ���� ���� ��� true ���, �ٿ���� ���� ��� false ���
bool HSVFilter::isInBoundary(const int h, const int s, const int v, FilterOption option)
{
	int correcH;
	if (HBoudaryCheck(h, option.getColor(), option.getHBoundary()))
		return true;

	correcH = h - option.getColor();

	if (correcH < 0)
		correcH *= -1;

	if (correcH > 90)
		correcH = 180 - correcH;

	//h���� �̻����� ��ġ�� �������� �ٿ������ ���� ����
	if (s < 255 - option.getSBoundary() * (double)(option.getHBoundary() - correcH) / (double)option.getHBoundary())
		return true;

	if (v < 255 - option.getVBoundary() * (double)(option.getHBoundary() - correcH) / (double)option.getHBoundary())
		return true;

	return false;
}

//�÷� ������
void FilterOption::settingColor(Color colorName)
{
	switch (colorName)
	{
	case red:
		baseColor = 120;
		break;
	case green:
		baseColor = 60;
		break;
	case blue:
		baseColor = 0;
		break;
	default:
		break;
	}
	return;
}

//�÷� �� ���
int FilterOption::getColor()
{
	return baseColor;
}

//H,S,V �ٿ���� ���� �� ��¿� �Լ�
void FilterOption::setHBoundary(int b)
{
	HBoundary = b;
	return;
}

void FilterOption::setSBoundary(int b)
{
	SBoundary = b;
	return;
}

void FilterOption::setVBoundary(int b)
{
	VBoundary = b;
	return;
}

int FilterOption::getHBoundary()
{
	return HBoundary;
}

int FilterOption::getSBoundary()
{
	return SBoundary;
}

int FilterOption::getVBoundary()
{
	return VBoundary;
}
