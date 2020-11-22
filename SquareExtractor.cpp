#include "SquareExtractor.h"
#include "vector"

using namespace cv;
using namespace std;
std::vector<cv::Point2f> SquareExtractor::getSquareVertex(cv::InputArray _src, ExtractOption option)
{
    double e_approxPolyDP = 0.02;
    


    Mat src = _src.getMat();
    Mat bin;
    //color region to 255, dark side to 0
    threshold(src, bin, 127, 255, THRESH_BINARY | THRESH_OTSU);
    
    //open calc, for reduce noise
    cv::Mat element5(5, 5, CV_8U, cv::Scalar(1));
    morphologyEx(bin, bin, MORPH_OPEN, element5);


    vector<vector<Point>> contours;

    double bestApproxSize = -1;
    vector<Point2f> bestApprox;

    findContours(bin, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
    for (int i = 0; i < contours.size(); i++) {
        
        double approxSize;
        vector<Point2f> approx;
        
        approxPolyDP(contours[i], approx, arcLength(contours[i], true) * e_approxPolyDP, true);
        approxSize = contourArea(approx, false);

        //find largest rect
        if (bestApproxSize < approxSize) {
            bestApprox = approx;
            bestApproxSize = approxSize;
        }

    }

    std::vector<cv::Point> result;

    //if (bestApprox.size() == 4) {
        return bestApprox;
   /* }
    else {
        //TODO, err handle
        return std::vector<cv::Point2f>();
    }
    

    */

  
}
