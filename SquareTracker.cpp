#include "SquareTracker.h"
#include <imgproc.hpp>
#include <Windows.h>
cv::Point SquareTracker::trackAndAction(std::vector<cv::Point2f> input, TrackerOption option)
{
	//Sleep(5); //may add
	cv::Moments mom = cv::moments(input);

	cv::Point rectLocation = cv::Point(mom.m10/mom.m00, mom.m01/mom.m00);
	
	INPUT key_input;
	ZeroMemory(&key_input, sizeof(INPUT)); //0으로 input을 초기화
	key_input.type = INPUT_KEYBOARD;
	
	if (rectLocation.x > option.x1) {
		if (rectLocation.y < option.y1) {
			key_input.ki.wVk = (BYTE) (option.keyCodes)[0];
			//1
		}
		else if (rectLocation.y >= option.y1 && rectLocation.y < option.y2) {
			//(option.keyCodes)[2] == -1
			//3 pass
		}
		else {
			key_input.ki.wVk = (option.keyCodes)[4];
			//5
		}
	}
	else {
		if (rectLocation.y < option.y1) {
			key_input.ki.wVk = (option.keyCodes)[1];
			//2
		}
		else if (rectLocation.y >= option.y1 && rectLocation.y < option.y2) {
			key_input.ki.wVk = (option.keyCodes)[3];
			//4
		}
		else {
			key_input.ki.wVk = (option.keyCodes)[5];
			//6
		}
	}

	SendInput(1, &key_input, sizeof(INPUT));
	key_input.ki.dwFlags = KEYEVENTF_KEYUP;
	SendInput(1, &key_input, sizeof(INPUT));

	return rectLocation;
}
