#pragma once

#include <vector>
#include<core.hpp>
/*
Area
	  x1
	1 | 2
y1 =>
	3 | 4
y2 =>	
	5 | 6

*/


class TrackerOption {
	friend class SquareTracker;
public:
	TrackerOption(int horizon_y1, int horizon_y2, int vertical_x1, int* keyCodeArray)
		:y1(horizon_y1), y2(horizon_y2), x1(vertical_x1), keyCodes(keyCodeArray){}

private:
	//�켱 ������ �� 3���� ������. �׸� ���� ������
	//���� 2��, ������ 1��
	int y1;
	int y2;
	int x1;
	int* keyCodes;



};
class SquareTracker
{
public:
	cv::Point trackAndAction(std::vector <cv::Point2f> input, TrackerOption option);
};

