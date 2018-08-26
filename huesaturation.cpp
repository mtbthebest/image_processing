//
// Created by mtb on 18/08/26.
//


#include <iostream>
#include<opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;

void detectHScolor() {


}


int main(int argc, char const *argv[]) {
    cv::Mat image = cv::imread("../images/boldt.jpg", 1);
    if (!image.data)
        return 0;
    cv::imshow("image", image);

    cv::Mat hsv;
    cv::cvtColor(image, hsv, CV_BGR2HSV);

    cv::imshow("image", hsv);


    cv::waitKey(0);
    return 0;

}





