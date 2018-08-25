//
// Created by mtb on 18/08/25.
//


#include <iostream>
#include<opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "colordetector.h"

using namespace std;

void strategy_design_pattern() {
    ColorDetector cdetect;
    cv::Mat image = cv::imread("../images/boldt.jpg", 1);

    if (!image.data);

    cdetect.setTargetColor(130, 190, 230);


    cv::imshow("window", cdetect.process(image));
    cv::waitKey(0);
}

void strategy_design_pattern2() {
    ColorDetector cdetect;
    cv::Mat image = cv::imread("../images/boldt.jpg", 1);

    cv::imshow("window", cdetect.process(image));
    cv::waitKey(0);
}


int main(int argc, char const *argv[]) {
    strategy_design_pattern();
    return 0;

}




