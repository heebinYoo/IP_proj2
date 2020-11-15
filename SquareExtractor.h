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
	* 8UC1 인 _src를 받아 꼭지점 4개를 리턴한다.
	*/
	std::vector<cv::Point> getSquareVertex(cv::InputArray _src, ExtractOption option);
};

