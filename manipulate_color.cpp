//
// Created by mtb on 18/08/25.
//


#include <iostream>
#include<opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "colordetector.h"

using namespace std;

void colorDetection() {
    ColorDetector cdetect;
    cv::Mat image = cv::imread("../images/boldt.jpg", 1);

    cv::imshow("image", image);


    cdetect.setTargetColor(230, 190, 130);

    cv::Mat result = cdetect.process(image);
    cv::imshow("result", result);

    ColorDetector colordetector(230, 190, 130, 45, true);
    result = colordetector(image);
    cv::imshow("colordetector", image);

    cv::floodFill(image, cv::Point(100, 50), cv::Scalar(255, 255, 255), (cv::Rect *) 0, cv::Scalar(35, 35, 35),
                  cv::Scalar(35, 35, 35), cv::FLOODFILL_FIXED_RANGE);

    result = colordetector(image);
    cv::imshow("flood fill", image);

    cv::Mat colors(100, 300, CV_8UC3, cv::Scalar(100, 200, 150));
    cv::Mat range = colors.colRange(0, 100);
    range = range + cv::Scalar(10, 10, 10);
    range = colors.colRange(200, 300);
    range += cv::Scalar(-10, -10, -10);

    cv::imshow("3 colors", colors);


    cv::Mat labImage(100, 300, CV_8UC3, cv::Scalar(100, 200, 150));
    cv::cvtColor(labImage, labImage, CV_BGR2Lab);
    range = colors.colRange(0, 100);
    range = range + cv::Scalar(10, 10, 10);
    range = colors.colRange(200, 300);
    range += cv::Scalar(-10, -10, -10);

    cv::cvtColor(labImage, labImage, CV_Lab2BGR);

    cv::imshow("3 colors (lab)", labImage);

    cv::Mat graylevels(100, 256, CV_8UC3);

    for (int i = 0; i < 256; ++i) {
        graylevels.col(i) = cv::Scalar(i, i, i);
    }
    range = graylevels.rowRange(50, 100);
    cv::Mat channels[3];
    cv::split(range, channels);

    channels[1] = 128;
    channels[2] = 128;

    cv::merge(channels, 3, range);
    cv::cvtColor(range, range, CV_Lab2BGR);
    cv::imshow("graycolors", graylevels);


    cv::waitKey(0);
}



int main(int argc, char const *argv[]) {
    colorDetection();
    return 0;

}




