//
// Created by mtb on 18/08/26.
//


#include <iostream>
#include<opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;

void detectHScolor(const cv::Mat& image,double minHue, double maxHue,double minSat, double maxSat, cv::Mat& mask) {

    cv::Mat hsv;
    cv::cvtColor(image, hsv, CV_BGR2HSV);

    std::vector<cv::Mat> channels;
    cv::split(hsv, channels);

    cv::Mat mask1;

    cv::threshold(channels[0],mask1, maxHue,255,cv::THRESH_BINARY_INV);


    cv::Mat mask2;
    cv::threshold(channels[0],mask2, minHue,255,cv::THRESH_BINARY);

    cv::Mat hueMask;
    if(minHue < maxHue)
        hueMask = mask & mask2;
    else
        hueMask = mask1 | mask2;

    cv::threshold(channels[1], mask1, maxSat,255,cv::THRESH_BINARY_INV);
    cv::threshold(channels[1], mask2, minSat,255,cv::THRESH_BINARY);

    cv::Mat satMask;
    satMask = mask1 & mask2;
    mask = hueMask&satMask;




}


int main(int argc, char const *argv[]) {
    cv::Mat image = cv::imread("../images/boldt.jpg", 1);
    if (!image.data)
        return 0;
    cv::imshow("image", image);

    cv::Mat hsv;
    cv::cvtColor(image, hsv, CV_BGR2HSV);

    cv::imshow("hsv", hsv);

    std::vector<cv::Mat> channels;
    cv::split(hsv,channels);

    cv::imshow("value channel", channels[2]);
    cv::imshow("saturation channel", channels[1]);
    cv::imshow("hue channel", channels[0]);

    cv::Mat newImage;
    cv::Mat tmp(channels[2].clone());

    channels[2] = 255;

    cv::merge(channels, hsv);

    cv::cvtColor(hsv,newImage, CV_HSV2BGR);
    cv::imshow("new image",newImage);

    channels[1] =255;
    channels[2] = 255;
    cv::merge(channels, hsv);
    cv::cvtColor(hsv,newImage, CV_HSV2BGR);
    cv::imshow("fixed saturation",newImage);


    cv::Mat hs(128,360, CV_8UC3);
    for(int h=0;h<360;h++){
        for(int s=0;s<128;s++){
            hs.at<cv::Vec3b>(s,h)[0] = h/2;
            hs.at<cv::Vec3b>(s,h)[1] = 255 -s*2;
            hs.at<cv::Vec3b>(s,h)[2] = 255;
        }

    }
    cv::cvtColor(hs, newImage, CV_HSV2BGR);
    cv::imshow("hue/saturation", newImage);

    image= cv::imread("../images/girl.jpg");
    if(!image.data)
        return 0;

    cv::imshow("original image", image);

    cv::Mat mask;
    detectHScolor(image,160,10,25,166,mask);

    cv::Mat detected(image.size(), CV_8UC3, cv::Scalar(0,0,0));
    image.copyTo(detected, mask);

    cv::imshow("detection result", detected);

    cv::Mat linear(100,256,CV_8U);
    for(int i=0;i<256;i++){
        linear.col(i) = i;
    }

    linear.copyTo(channels[0]);
    cv::Mat constante(100,256,CV_8U,cv::Scalar(128));
    constante.copyTo(channels[1]);
    constante.copyTo(channels[2]);
    cv::merge(channels, image);

    cv::Mat brightness;
    cv::cvtColor(image,brightness, CV_Lab2BGR);
    cv::split(brightness, channels);

    cv::Mat combined(200,256, CV_8U);
    cv::Mat half1(combined,cv::Rect(0,0,256,100));
    linear.copyTo(half1);
    cv::Mat half2(combined,cv::Rect(0,100,256,100));
    channels[0].copyTo(half2);

    cv::namedWindow("Luminance vs Brightness");
    cv::imshow("Luminance vs Brightness",combined);

    cv::waitKey();

//    cv::imshow("linear", linear);




    cv::waitKey(0);
    return 0;

}





