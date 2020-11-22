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
		cv::flip(img, img, 1);//��ķ�̶� �¿���� �ɾ�� ���������� ����

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
            break;
        }

        

        cv::imshow("guided image", img_guide);
        cv::waitKey(1);
	}



    counter = 0;
    ip_proj_lineData::keyCode = (int*) malloc(6*sizeof(int));

    while (1) {
        cap >> img;
        cv::flip(img, img, 1);//��ķ�̶� �¿���� �ɾ�� ���������� ����
       
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
        else if (counter == 2) {
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

}
//cv::imshow("camera img", img);

		/*
		cv::Mat redOnly;
		hsvFilter.getRedOnlyImage(img, redOnly, FilterOption());
		std::vector<cv::Point2f> result = extractor.getSquareVertex(redOnly, ExtractOption());
		tracker.trackAndAction(result, TrackerOption(ip_proj_lineData::y1,ip_proj_lineData::y2,ip_proj_lineData::x1, ip_proj_lineData::keyCode));
		*/
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
    else if (event == EVENT_RBUTTONDOWN)
    {
        //std::cout << "Right button of the mouse is clicked - position (" << x << ", " << y << ")" << std::endl;
    }
    /*
    else if (event == EVENT_MBUTTONDOWN)
    {
        std::cout << "Middle button of the mouse is clicked - position (" << x << ", " << y << ")" << std::endl;
    }
    else if (event == EVENT_MOUSEMOVE)
    {
        std::cout << "Mouse move over the window - position (" << x << ", " << y << ")" << std::endl;
    }
    else if (event == EVENT_LBUTTONUP)
    {
        std::cout << "Left button of the mouse is released - position (" << x << ", " << y << ")" << std::endl;
    }
    else if (event == EVENT_RBUTTONUP)
    {
        std::cout << "Right button of the mouse is released - position (" << x << ", " << y << ")" << std::endl;
    }
    else if (event == EVENT_MBUTTONUP)
    {
        std::cout << "Middle button of the mouse is released - position (" << x << ", " << y << ")" << std::endl;
    }
    else if (event == EVENT_LBUTTONDBLCLK)
    {
        std::cout << "Left button of the mouse is double-clicked - position (" << x << ", " << y << ")" << std::endl;
    }
    else if (event == EVENT_RBUTTONDBLCLK)
    {
        std::cout << "Right button of the mouse is double-clicked - position (" << x << ", " << y << ")" << std::endl;
    }
    else if (event == EVENT_MBUTTONDBLCLK)
    {
        std::cout << "Middle button of the mouse is double-clicked - position (" << x << ", " << y << ")" << std::endl;
    }

    */

}