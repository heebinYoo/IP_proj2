#pragma once
#include <vector>
#include<core.hpp>
#include<highgui.hpp>
#include<iostream>
#include<math.h>
#include<imgproc.hpp>

class ExtractOption {
public:
	friend SquareExtractor;

};

class SquareExtractor
{
public:
	/*
	* 8UC1 �� _src�� �޾� ������ 4���� �����Ѵ�.
	*/
	std::vector<cv::Point> getSquareVertex(cv::InputArray _src, ExtractOption option);
};

