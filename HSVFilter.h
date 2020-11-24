#pragma once
#include<opencv2/core.hpp>
#include<opencv2/highgui.hpp>
#include<iostream>
#include<math.h>
#include<opencv2/imgproc.hpp>

/*
* 전경 추출 및 색 필터링을 해주는 클래스
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
	제일 클래식한 인자 전달, 회수 방법
	이 In/Out은 _In/_Out클래스의 레퍼런스 타입으로 재정의된 것임, 즉 레퍼런스를 받는 놈
	
	_src는 8UC3
	_dst는 8UC1 : 그레이스케일로 주세요

	사용
	Mat src = _src.getMat();
	_dst.create(src.size(), cv::8UC1);
	Mat dst = _dst.getMat();

	옵션은 필요한 것에 맞추어 정의할 것
	*/

	void getRedOnlyImage(cv::InputArray _src, cv::OutputArray _dst, FilterOption option);
	void getBlueOnlyImage(cv::InputArray _src, cv::OutputArray _dst, FilterOption option);
	void getGreenOnlyImage(cv::InputArray _src, cv::OutputArray _dst, FilterOption option);

private:
	//통일된 방법으로 진행하는 추출 함수
	void getOnlyImage(cv::InputArray _src, cv::OutputArray _dst, FilterOption option);
	
	//h값 바운더리 체크용 함수
	bool HBoudaryCheck(int h, int baseColor, int boundary);
	
	//h, s, v값 바운더리 체크용
	bool isInBoundary(const int h, const int s, const int v, FilterOption option);
};

