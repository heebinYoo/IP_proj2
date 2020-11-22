#include<core.hpp>
#include<highgui.hpp>
#include<iostream>
#include<math.h>


#include<imgproc.hpp>
#include "HSVFilter.h"
#include "SquareExtractor.h"
#include "SquareTracker.h"


using namespace cv;
void CallBackFunc(int event, int x, int y, int flags, void* userdata);

namespace ip_proj_lineData {
    int x1;
    int y1;
    int y2;
    int* keyCode;
}
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

    int counter = 0;
    cap >> img;
    ip_proj_lineData::x1 = img.cols / 2;


    cv::namedWindow("guided image");
	cv::setMouseCallback("guided image", CallBackFunc, &counter);
   
	while (1)
	{
		cap >> img;
		cv::flip(img, img, 1);//웹캠이라서 좌우반전 걸어야 정상적으로 나옴

		cv::Mat img_guide;
		img.copyTo(img_guide);
		int rows = img_guide.rows;
		int cols = img_guide.cols;
		cv::line(img_guide, cv::Point(cols / 2, 0), cv::Point(cols / 2, rows - 1), cv::Scalar(255, 0, 0), 1, 8, 0);
		
        if (counter == 1) {
            cv::line(img_guide, cv::Point(0, ip_proj_lineData::y1), cv::Point(cols - 1, ip_proj_lineData::y1), cv::Scalar(255, 255, 0), 1, 8, 0);
       }
        else if (counter == 2) {
            cv::line(img_guide, cv::Point(0, ip_proj_lineData::y1), cv::Point(cols - 1, ip_proj_lineData::y1), cv::Scalar(255, 255, 0), 1, 8, 0);
            cv::line(img_guide, cv::Point(0, ip_proj_lineData::y2), cv::Point(cols - 1, ip_proj_lineData::y2), cv::Scalar(255, 0, 255), 1, 8, 0);
            cv::imshow("guided image", img_guide);
            cv::waitKey(1);
           
            if (ip_proj_lineData::y1 > ip_proj_lineData::y2) {
                int temp = ip_proj_lineData::y1;
                ip_proj_lineData::y1 = ip_proj_lineData::y2;
                ip_proj_lineData::y2 = temp;
            }
            cv::setMouseCallback("guided image", NULL, NULL);
            break;
        }

        

        cv::imshow("guided image", img_guide);
        cv::waitKey(1);
	}



    counter = 0;
    ip_proj_lineData::keyCode = (int*) malloc(6*sizeof(int));

    while (1) {
        cap >> img;
        cv::flip(img, img, 1);//웹캠이라서 좌우반전 걸어야 정상적으로 나옴
       
        cv::Mat img_guide;
        img.copyTo(img_guide);
        int rows = img_guide.rows;
        int cols = img_guide.cols;
        cv::line(img_guide, cv::Point(cols / 2, 0), cv::Point(cols / 2, rows - 1), cv::Scalar(255, 0, 0), 1, 8, 0);
        cv::line(img_guide, cv::Point(0, ip_proj_lineData::y1), cv::Point(cols - 1, ip_proj_lineData::y1), cv::Scalar(255, 255, 0), 1, 8, 0);
        cv::line(img_guide, cv::Point(0, ip_proj_lineData::y2), cv::Point(cols - 1, ip_proj_lineData::y2), cv::Scalar(255, 0, 255), 1, 8, 0);
        cv::putText(img_guide, "y1", cv::Point(0, ip_proj_lineData::y1), cv::FONT_HERSHEY_PLAIN, 2.0, cv::Scalar(0, 0, 255), 1);
        cv::putText(img_guide, "y2", cv::Point(0, ip_proj_lineData::y2), cv::FONT_HERSHEY_PLAIN, 2.0, cv::Scalar(0, 0, 255), 1);
        

        if (counter == 0) {  
        }
        else if (counter == 1) {
            cv::putText(img_guide, "V", cv::Point((ip_proj_lineData::x1 + 0) / 2, (ip_proj_lineData::y1 + 0) / 2), cv::FONT_HERSHEY_PLAIN, 2.0, cv::Scalar(0, 0, 255), 1);
        }

        else if (counter == 3) {
            cv::putText(img_guide, "V", cv::Point((ip_proj_lineData::x1 + 0) / 2, (ip_proj_lineData::y1 + 0) / 2), cv::FONT_HERSHEY_PLAIN, 2.0, cv::Scalar(0, 0, 255), 1);
            cv::putText(img_guide, "V", cv::Point((ip_proj_lineData::x1 + cols - 1) / 2, (ip_proj_lineData::y1 + 0) / 2), cv::FONT_HERSHEY_PLAIN, 2.0, cv::Scalar(0, 0, 255), 1);
        }
        else if (counter == 4) {
            cv::putText(img_guide, "V", cv::Point((ip_proj_lineData::x1 + 0) / 2, (ip_proj_lineData::y1 + 0) / 2), cv::FONT_HERSHEY_PLAIN, 2.0, cv::Scalar(0, 0, 255), 1);
            cv::putText(img_guide, "V", cv::Point((ip_proj_lineData::x1 + cols - 1) / 2, (ip_proj_lineData::y1 + 0) / 2), cv::FONT_HERSHEY_PLAIN, 2.0, cv::Scalar(0, 0, 255), 1);
            //cv::putText(img_guide, "V", cv::Point((ip_proj_lineData::x1 + 0) / 2, (ip_proj_lineData::y1 + ip_proj_lineData::y2) / 2), cv::FONT_HERSHEY_PLAIN, 2.0, cv::Scalar(0, 0, 255), 1);
            cv::putText(img_guide, "V", cv::Point((ip_proj_lineData::x1 + cols - 1) / 2, (ip_proj_lineData::y1 + ip_proj_lineData::y2) / 2), cv::FONT_HERSHEY_PLAIN, 2.0, cv::Scalar(0, 0, 255), 1);
        }
        else if (counter == 5) {
            cv::putText(img_guide, "V", cv::Point((ip_proj_lineData::x1 + 0) / 2, (ip_proj_lineData::y1 + 0) / 2), cv::FONT_HERSHEY_PLAIN, 2.0, cv::Scalar(0, 0, 255), 1);
            cv::putText(img_guide, "V", cv::Point((ip_proj_lineData::x1 + cols - 1) / 2, (ip_proj_lineData::y1 + 0) / 2), cv::FONT_HERSHEY_PLAIN, 2.0, cv::Scalar(0, 0, 255), 1);
           // cv::putText(img_guide, "V", cv::Point((ip_proj_lineData::x1 + 0) / 2, (ip_proj_lineData::y1 + ip_proj_lineData::y2) / 2), cv::FONT_HERSHEY_PLAIN, 2.0, cv::Scalar(0, 0, 255), 1);
            cv::putText(img_guide, "V", cv::Point((ip_proj_lineData::x1 + cols - 1) / 2, (ip_proj_lineData::y1 + ip_proj_lineData::y2) / 2), cv::FONT_HERSHEY_PLAIN, 2.0, cv::Scalar(0, 0, 255), 1);
            cv::putText(img_guide, "V", cv::Point((ip_proj_lineData::x1 + 0) / 2, (ip_proj_lineData::y2 + rows - 1) / 2), cv::FONT_HERSHEY_PLAIN, 2.0, cv::Scalar(0, 0, 255), 1);

        }
        else if (counter == 6) {
            /*
            cv::putText(img_guide, "V", cv::Point((ip_proj_lineData::x1 + 0) / 2,        (ip_proj_lineData::y1 + 0) / 2), cv::FONT_HERSHEY_PLAIN, 2.0, cv::Scalar(0, 0, 255), 1);
            cv::putText(img_guide, "V", cv::Point((ip_proj_lineData::x1 + cols - 1) / 2, (ip_proj_lineData::y1 + 0) / 2), cv::FONT_HERSHEY_PLAIN, 2.0, cv::Scalar(0, 0, 255), 1);
           // cv::putText(img_guide, "V", cv::Point((ip_proj_lineData::x1 + 0) / 2,        (ip_proj_lineData::y1 + ip_proj_lineData::y2) / 2), cv::FONT_HERSHEY_PLAIN, 2.0, cv::Scalar(0, 0, 255), 1);
            cv::putText(img_guide, "V", cv::Point((ip_proj_lineData::x1 + cols - 1) / 2, (ip_proj_lineData::y1 + ip_proj_lineData::y2) / 2), cv::FONT_HERSHEY_PLAIN, 2.0, cv::Scalar(0, 0, 255), 1);
            cv::putText(img_guide, "V", cv::Point((ip_proj_lineData::x1 + 0) / 2,        (ip_proj_lineData::y2 + rows - 1) / 2), cv::FONT_HERSHEY_PLAIN, 2.0, cv::Scalar(0, 0, 255), 1);
            cv::putText(img_guide, "V", cv::Point((ip_proj_lineData::x1 + cols - 1) / 2, (ip_proj_lineData::y2 + rows - 1) / 2), cv::FONT_HERSHEY_PLAIN, 2.0, cv::Scalar(0, 0, 255), 1);
            */
            break;
            
            
        }
        cv::imshow("guided image", img_guide);
        int ret = cv::waitKey(0);
        if (ret >= 97 && ret <= 122) {
            ret - 32;
        }
        ip_proj_lineData::keyCode[counter] = ret;
        counter++;
        if (counter == 2) {
            ip_proj_lineData::keyCode[counter] = -1;
            counter++;
        }

    }

    while (1) {
        cap >> img;
        cv::flip(img, img, 1);//웹캠이라서 좌우반전 걸어야 정상적으로 나옴

        cv::Mat img_guide;
        img.copyTo(img_guide);
        int rows = img_guide.rows;
        int cols = img_guide.cols;
        cv::line(img_guide, cv::Point(cols / 2, 0), cv::Point(cols / 2, rows - 1), cv::Scalar(255, 0, 0), 1, 8, 0);
        cv::line(img_guide, cv::Point(0, ip_proj_lineData::y1), cv::Point(cols - 1, ip_proj_lineData::y1), cv::Scalar(255, 255, 0), 1, 8, 0);
        cv::line(img_guide, cv::Point(0, ip_proj_lineData::y2), cv::Point(cols - 1, ip_proj_lineData::y2), cv::Scalar(255, 0, 255), 1, 8, 0);
        //cv::putText(img_guide, "y1", cv::Point(0, ip_proj_lineData::y1), cv::FONT_HERSHEY_PLAIN, 2.0, cv::Scalar(0, 0, 255), 1);
        //cv::putText(img_guide, "y2", cv::Point(0, ip_proj_lineData::y2), cv::FONT_HERSHEY_PLAIN, 2.0, cv::Scalar(0, 0, 255), 1);
        
        cv::Mat redOnly;
        hsvFilter.getRedOnlyImage(img, redOnly, FilterOption());
        std::vector<cv::Point2f> result = extractor.getSquareVertex(redOnly, ExtractOption());
        cv::Point pos = tracker.trackAndAction(result, TrackerOption(ip_proj_lineData::y1, ip_proj_lineData::y2, ip_proj_lineData::x1, ip_proj_lineData::keyCode));
        cv::circle(img_guide, pos, 2.0, Scalar(0, 0, 255), 3, 8);



        cv::imshow("guided image", img_guide);
        if (cv::waitKey(1) == 27) {
            break;
        }
    }

    return 0;
}



void CallBackFunc(int event, int x, int y, int flags, void* userdata)
{
    
    if (event == EVENT_LBUTTONDOWN)
    {
        if (*((int*)userdata) == 0) {
            ip_proj_lineData::y1 = y;
            (*((int*)userdata))++;
        }
        else if (*((int*)userdata) == 1) {
            ip_proj_lineData::y2 = y;
            (*((int*)userdata))++;
        }
    }
   
}