#include<core.hpp>
#include<highgui.hpp>
#include<iostream>
#include<math.h>


#include<imgproc.hpp>
#include "HSVFilter.h"
#include "SquareExtractor.h"
#include "SquareTracker.h"

int main() {
	cv::VideoCapture cap(0);

	if (!cap.isOpened())
	{
		printf("Can't open the camera");
		return -1;
	}


	cv::Mat img;
	HSVFilter hsvFilter;
	SquareExtractor extractor;
	SquareTracker tracker;

	while (1)
	{
		cap >> img;
		cv::flip(img, img, 1);//웹캠이라서 좌우반전 걸어야 정상적으로 나옴

		//cv::imshow("camera img", img);
		
		/*
		cv::Mat redOnly;
		hsvFilter.getRedOnlyImage(img, redOnly, FilterOption());
		std::vector<cv::Point> result = extractor.getSquareVertex(redOnly, ExtractOption());
		tracker.trackAndAction(result, TrackerOption(1,2,3));
		*/

		cv::Mat img_guide;
		img.copyTo(img_guide);
		int rows = img_guide.rows;
		int cols = img_guide.cols;
		cv::line(img_guide, cv::Point(cols / 2, 0), cv::Point(cols / 2, rows - 1), cv::Scalar(255, 0, 0), 1, 8, 0);
		cv::imshow("guided image", img_guide);




		if (cv::waitKey(1) == 27)
			break;
	}


}
