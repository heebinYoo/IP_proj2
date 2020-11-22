#pragma once
#include<core.hpp>
#include<highgui.hpp>
#include<iostream>
#include<math.h>
#include<imgproc.hpp>

/*
* ���� ���� �� �� ���͸��� ���ִ� Ŭ����
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

};

