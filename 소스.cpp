#include<core.hpp>
#include<highgui.hpp>
#include<iostream>
#include<math.h>


#include<imgproc.hpp>


#pragma warning(disable : 4996)

using namespace cv;
using namespace std;

Mat getBinaryInvMat(const Mat &src) {
	Mat dst(Size(src.cols, src.rows), CV_8U);

	for (int i = 0; i < src.cols; i++) {
		for (int j = 0; j < src.rows; j++) {
			uchar temp = (src.at<Vec3b>(j, i)[0] + src.at<Vec3b>(j, i)[1] + src.at<Vec3b>(j, i)[2]) / 3;
			if (temp > 200) {
				dst.at<uchar>(j, i) = 0;
			}
			else {
				dst.at<uchar>(j, i) = 255;
			}
			
		}
	}

	return dst;

}


Point2i findFirstPoint(const Mat& src) {

	Point2i result;
	//mat.at<type>(row=y,column=x) or mat.at<type>(cv::Point(x=col,y=row))
	//at(y,x), at(row, col), row : 0번 차원, col : 1번 차원
	// x: col : j
	// y: row : i
	for (int i = 0; i < src.rows; i++) {
		for (int j = 0; j < src.cols; j++) {
			if (src.at<uchar>(i, j) == 255) {
				result.x = j;
				result.y = i;
				goto A;
			}
		}
	}
	

A:
	//x, y 넣어서 초기화하는 것 맞음
	//Point2i t = Point2i(x,y);



	return result;
}

bool isAvailPoint(int rows, int cols, int row, int col) {
	if (rows <= row || cols <= col || 0 > row || 0 > col) {
		return false;
	}
	return true;
}

bool isAvailPoint(int rows, int cols, Point2i p) {
	if (rows <= p.y || cols <= p.x || 0 > p.y || 0 > p.x) {
		return false;
	}
	return true;
}


Point2i ccw[8] = {Point2i(1,-1), Point2i(0,-1), Point2i(-1,-1),
					Point2i(-1,0), Point2i(-1,1),
					Point2i(0,1), Point2i(1,1), Point2i(1,0)};

int getCCWidx(Point2i p) {
	
	for (int i = 0; i < 8; i++) {
		if (ccw[i] == p)
			return i;
	}
	return -1;

}


double perpendicularDistance(Point2i l1, Point2i l2, Point2i p) {
	

	if (l2.x - l1.x == 0) {
		return abs(l1.x - p.x);
	}
	else {
		double diff = (l2.y - l1.y) / (double) (l2.x - l1.x);
		return abs(diff * p.x - p.y + l1.y - diff * l1.x) / sqrt(diff * diff + 1);
	}
	
	

	
}

vector<Point2i> *DouglasPeucker(vector<Point2i> *PointList, double epsilon) {

	vector<Point2i> *result = new vector<Point2i>;

	int start_idx=0;
	int end_idx= PointList->size() - 1;

	int idx = 0;
	double dmax = 0;
	for (int i = 1; i < PointList->size()-1; i++) {
		double d = perpendicularDistance(PointList->at(start_idx), PointList->at(end_idx), PointList->at(i));
		if (d > dmax) {
			idx = i;
			dmax = d;
		}
	}

	if (dmax > epsilon) {

		std::vector<Point2i> *split_lo = new vector<Point2i>(PointList->begin(), PointList->begin() + idx+1);
		std::vector<Point2i> *split_hi = new vector<Point2i>(PointList->begin() + idx+1, PointList->end());


		vector<Point2i>* L_result = DouglasPeucker(split_lo, epsilon);
		vector<Point2i>* R_result =  DouglasPeucker(split_hi, epsilon);

		L_result->insert(L_result->end(), R_result->begin(), R_result->end());
		result->insert(result->end(), L_result->begin(), L_result->end());


		//delete L_result;
		//delete R_result;

	}
	else {
		result->push_back(PointList->at(0));
		result->push_back(PointList->at(PointList->size() - 1));
	}

	return result;
}





// x: col : j
// y: row : i

int borderCount(Mat& src, Point2i p) {

	//int i = p.x; //row
	//int j = p.y; // col

	vector<Point2i> contour;

	int start = (3 + 1) % 8;
	while (true) {

		for (int i = 0; i < 8; i++) {
			Point2i temp = p + ccw[(start + i) % 8];
			if (isAvailPoint(src.rows, src.cols, temp)) {
				if (src.at<uchar>(temp) == 255) {
					src.at<uchar>(p) = 2;
					contour.push_back(p);
					start = (getCCWidx(p - temp) +1) % 8;

					p = temp;
					break;
				}
				else if (src.at<uchar>(temp) == 2) {
					src.at<uchar>(p) = 2;
					contour.push_back(p);

					goto borderCountWHILE;
				}
			}
		}
	}
	borderCountWHILE:
	

	
	vector<Point2i> custom_out;
	custom_out = *DouglasPeucker(&contour, 10);



	vector<int> delete_target;

	for (int q = 0; q < custom_out.size(); q++) {
		Point2i temp = custom_out.at(q) - custom_out.at((q + 1) % custom_out.size());
		if (abs(temp.x) < 2 && abs(temp.y) < 2) {
			delete_target.push_back(q);
		}
	}



	int change_count = custom_out.size() - delete_target.size();




	for (int i = 0; i < contour.size()-1; i++) {

		circle(src, contour.at(i), 2, Scalar(127), 2);
	}

	for (int i = 0; i < custom_out.size() - 1; i++) {

		circle(src, custom_out.at(i), 2, Scalar(70), 2);
	}


	
	
	


	
	//cout << change_count << endl;




	return change_count;
}

/*
int main() {
	for (int fileidx = 1; fileidx < 5; fileidx++){
		//String filepath("C:\\input\\triangle.jpg");
		String filepath;
		filepath.resize(200);
		sprintf((char*)filepath.c_str(), "C:\\input\\%d.jpg", fileidx);
		
		
		Mat img = imread(filepath);

		if (img.empty()) {
			//std::cout << "Could not read the image." << std::endl;
			return -1;
			//continue;
		}

		Mat bin = getBinaryInvMat(img);



		Point2i p = findFirstPoint(bin);
		
		int ret = borderCount(bin, p);


		cout << "for the file"<< filepath  << ", "<< ret <<" point is detacted, so it is ";
		if (ret == 4) {
			cout << "rectangle"<<endl;
		}
		else {
			cout << "triangle" << endl;
		}

		
		imshow(filepath, bin);

		

	}
	waitKey(0);


}
*/