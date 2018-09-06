//
// Created by mtb on 18/08/26.
//

#include <iostream>
#include<opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>


using namespace std;


int main(int argc, char const *argv[]) {

    cv::Mat image = cv::imread("../images/boldt.jpg", 1);
    cv::Rect rectangle(70, 60, 210, 300);
//

    cv::Mat result;
    cv::Mat bgModel, fgModel;


    cv::grabCut(image, result, rectangle, bgModel, fgModel, 30, cv::GC_INIT_WITH_RECT);

    cv::compare(result, cv::GC_PR_FGD, result, cv::CMP_EQ);

    cv::Mat foreground(image.size(), CV_8UC3, cv::Scalar(255, 255, 255));

    image.copyTo(foreground, result);
    cv::rectangle(image, rectangle, cv::Scalar(255, 255, 255));


//    cv::imshow("window",image);
    cv::imshow("result",result);
    cv::imshow("window", image);
    cv::imshow("foreground", foreground);
    cv::waitKey(0);

    return 0;

}





