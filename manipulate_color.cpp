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




    cv::waitKey(0);
}



int main(int argc, char const *argv[]) {
    colorDetection();
    return 0;

}




