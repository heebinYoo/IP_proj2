#pragma once

#include <vector>
#include<core.hpp>
class TrackerOption {
	friend class SquareTracker;
public:
	TrackerOption(int horizon_y1, int horizon_y2, int vertical_x1):y1(horizon_y1), y2(horizon_y2), x1(vertical_x1) {}

private:
	//�켱 ������ �� 3���� ������. �׸� ���� ������
	//���� 2��, ������ 1��
	int y1;
	int y2;
	int x1;


};
class SquareTracker
{
public:
	void trackAndAction(std::vector <cv::Point> input, TrackerOption option);
};

