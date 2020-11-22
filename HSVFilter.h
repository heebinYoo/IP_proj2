#pragma once
#include<core.hpp>
#include<highgui.hpp>
#include<iostream>
#include<math.h>
#include<imgproc.hpp>

/*
* 전경 추출 및 색 필터링을 해주는 클래스
*/

class FilterOption
{
	friend class HSVFilter;
public:
	
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

};

