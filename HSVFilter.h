#pragma once
#include<opencv2/core.hpp>
#include<opencv2/highgui.hpp>
#include<iostream>
#include<math.h>
#include<opencv2/imgproc.hpp>

/*
* ���� ���� �� �� ���͸��� ���ִ� Ŭ����
*/

enum Color
{
	red, green, blue
};

class FilterOption
{
public:
	friend class HSVFilter;
	void settingColor(Color colorName);
	int getColor();
	void setHBoundary(int b);
	void setSBoundary(int b);
	void setVBoundary(int b);
	int getHBoundary();
	int getSBoundary();
	int getVBoundary();

private:
	int baseColor=0;
	int HBoundary=60, SBoundary=250, VBoundary=250;
};

class HSVFilter
{
public:

	/*
	���� Ŭ������ ���� ����, ȸ�� ���
	�� In/Out�� _In/_OutŬ������ ���۷��� Ÿ������ �����ǵ� ����, �� ���۷����� �޴� ��
	
	_src�� 8UC3
	_dst�� 8UC1 : �׷��̽����Ϸ� �ּ���

	���
	Mat src = _src.getMat();
	_dst.create(src.size(), cv::8UC1);
	Mat dst = _dst.getMat();

	�ɼ��� �ʿ��� �Ϳ� ���߾� ������ ��
	*/

	void getRedOnlyImage(cv::InputArray _src, cv::OutputArray _dst, FilterOption option);
	void getBlueOnlyImage(cv::InputArray _src, cv::OutputArray _dst, FilterOption option);
	void getGreenOnlyImage(cv::InputArray _src, cv::OutputArray _dst, FilterOption option);

private:
	//���ϵ� ������� �����ϴ� ���� �Լ�
	void getOnlyImage(cv::InputArray _src, cv::OutputArray _dst, FilterOption option);
	
	//h�� �ٿ���� üũ�� �Լ�
	bool HBoudaryCheck(int h, int baseColor, int boundary);
	
	//h, s, v�� �ٿ���� üũ��
	bool isInBoundary(const int h, const int s, const int v, FilterOption option);
};

