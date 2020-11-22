#include "SquareTracker.h"
#include <imgproc.hpp>

void SquareTracker::trackAndAction(std::vector<cv::Point2f> input, TrackerOption option)
{
	

	cv::Moments mom = cv::moments(input);

	cv::Point rectLocation = cv::Point(mom.m10/mom.m00, mom.m01/mom.m00);
	if (rectLocation.x > option.x1) {
		if (rectLocation.y < option.y1) {
			(option.keyCodes)[0];
			//1
		}
		else if (rectLocation.y >= option.y1 && rectLocation.y < option.y2) {
			//(option.keyCodes)[2] == -1
			//3 pass
		}
		else {
			(option.keyCodes)[4];
			//5
		}
	}
	else {
		if (rectLocation.y < option.y1) {
			(option.keyCodes)[1];
			//2
		}
		else if (rectLocation.y >= option.y1 && rectLocation.y < option.y2) {
			(option.keyCodes)[3];
			//4
		}
		else {
			(option.keyCodes)[5];
			//6
		}
	}

}
