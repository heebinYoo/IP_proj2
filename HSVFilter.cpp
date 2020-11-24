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

//색 지정을 제외하면 중복되는 과정이기에 하나의 함수로 절차 통일
void HSVFilter::getOnlyImage(cv::InputArray _src, cv::OutputArray _dst, FilterOption option)
{
	//src, dst 처리
	cv::Mat src = _src.getMat();
	_dst.create(src.size(), CV_8UC1);
	cv::Mat dst = _dst.getMat();

	//높이와 너비 선언
	const int height = src.size().height;
	const int width = src.size().width;

	//s,v 최대 최소 보정용, 0=min, 1=max
	int sMinMax[2] = { 255,0 };
	int vMinMax[2] = { 255,0 };

	//맵핑을 해줄 map 선언
	int** map;
	map = new int* [height];
	for (int count = 0; count < height; count++) {
	
		map[count] = new int[width] {0};
	}

	//hsv 분석을 위한 hsv용 mat 선언
	cv::Mat hsvMat;
	cv::cvtColor(src, hsvMat, cv::COLOR_RGB2HSV);

	//s와 v 스트레칭을 위한 최솟값, 최댓값 연산
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

	//스트레칭 후 바운더리 통과 여부 확인
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {

			//계산의 편의성을 위해 hsv값 선언
			int h = hsvMat.at<cv::Vec3b>(y, x)[0];
			int s = hsvMat.at<cv::Vec3b>(y, x)[1];
			int v = hsvMat.at<cv::Vec3b>(y, x)[2];

			//s와 v 스트래칭
			s = (s - sMinMax[0]) * 255.0 / (double)(sMinMax[1] - sMinMax[0]);
			v = (v - vMinMax[0]) * 255.0 / (double)(vMinMax[1] - vMinMax[0]);


			//바운더리 밖에 있으면 컨티뉴로 넘기고, 내부로 있을 경우 다음 절차 시행
			if (isInBoundary(h, s, v, option))
				continue;

			//컨티뉴로 안넘어갔을경우, 즉 바운더리 내부일 경우 맵에 해당 좌표는 1로 기록
			map[y][x] = 1;
		}
	}

	//맵을 토대로 dst에 1인 경우 255으로, 0일 경우 0으로 지정
	for (int y = 0; y < height; y++)
		for (int x = 0; x < width; x++) {
		
			if (map[y][x] == 1)
				dst.at<uchar>(y, x) = (unsigned char)255;
			else
				dst.at<uchar>(y, x) = (unsigned char)0;
		}
	
}

//h값의 경우, 180=0이므로, 순환을 고려한 별도의 바운더리 체크 함수 지정
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

//바운더리 내 존재 여부 확인, 바운더리 밖일 경우 true 출력, 바운더리 밖일 경우 false 출력
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

	//h값이 이상적인 수치에 가까울수록 바운더리의 범위 증가
	if (s < 255 - option.getSBoundary() * (double)(option.getHBoundary() - correcH) / (double)option.getHBoundary())
		return true;

	if (v < 255 - option.getVBoundary() * (double)(option.getHBoundary() - correcH) / (double)option.getHBoundary())
		return true;

	return false;
}

//컬러 지정용
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

//컬러 값 출력
int FilterOption::getColor()
{
	return baseColor;
}

//H,S,V 바운더리 세팅 및 출력용 함수
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
