//
// Created by mtb on 18/09/06.
//

#include <iostream>
#include <vector>
using namespace std;

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/video/tracking.hpp>

#include "contentFinder.h"
#include "colorhistogram.h"

int main(){
    cv::Mat image = cv::imread("../images/baboon1.jpg");

    cv::Rect rect(110,260,35,40);
    cv::rectangle(image, rect, cv::Scalar(0, 0, 255));

    cv::Mat imageROI = image(rect);

    cv::namedWindow("Image 1");
    cv::imshow("Image 1",image);

    int minSat = 65;
    ColorHistogram hc;
    cv::Mat colorhist = hc.getHueHistogram(imageROI, minSat);

    ContentFinder finder;
    finder.setHistogram(colorhist);
    finder.setThreshold(0.2f);

    cv::Mat hsv;
    cv::cvtColor(image, hsv, CV_BGR2HSV);

    vector<cv::Mat> v;
    cv::split(hsv, v);

    cv::threshold(v[1], v[1], minSat, 255, cv::THRESH_BINARY);
    cv::namedWindow("Saturation mask");
    cv::imshow("Saturation mask",v[1]);

    image = cv::imread("../images/baboon2.jpg");
    cv::namedWindow("Image 2");
    cv::imshow("Image 2",image);

    cv::cvtColor(image, hsv, CV_BGR2HSV);
    int ch[1]={0};
    finder.setThreshold(-1.0f);
    cv::Mat result = finder.find(hsv,0.0f,180.0f,ch);

    cv::namedWindow("Backprojection on second image");
    cv::imshow("Backprojection on second image",result);

    cv::rectangle(image, rect, cv::Scalar(0, 0, 255));
    cv::TermCriteria criteria(cv::TermCriteria::MAX_ITER | cv::TermCriteria::EPS, 10, 1);
    cout<<"meanshift= "<<cv::meanShift(result,rect,criteria)<<endl;

    cv::rectangle(image, rect, cv::Scalar(0, 255, 0));

    cv::namedWindow("Image 2 result");
    cv::imshow("Image 2 result",image);


    cv::waitKey(0);

}