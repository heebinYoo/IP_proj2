#pragma once
#include <vector>
#include<core.hpp>
#include<highgui.hpp>
#include<iostream>
#include<math.h>
#include<imgproc.hpp>

class ExtractOption {
	friend class SquareExtractor;
public:
	

};

class SquareExtractor
{
public:
	std::vector<cv::Point2f> getSquareVertex(cv::InputArray _src, ExtractOption option);
};

