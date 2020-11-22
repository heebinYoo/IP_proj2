#pragma once

#include <vector>
#include<core.hpp>
class TrackerOption {
	friend class SquareTracker;
public:
	TrackerOption(int horizon_y1, int horizon_y2, int vertical_x1):y1(horizon_y1), y2(horizon_y2), x1(vertical_x1) {}

private:
	//우선 영역을 선 3개로 나눈다. 그를 위한 데이터
	//수평선 2개, 수직선 1개
	int y1;
	int y2;
	int x1;


};
class SquareTracker
{
public:
	void trackAndAction(std::vector <cv::Point> input, TrackerOption option);
};

