//
// Created by mtb on 18/08/26.
//
#include <iostream>
using namespace std;

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "histogram.h"

int main(int argc, char *argv[]) {
    cv::Mat image = cv::imread("../images/group.jpg",0);
    if(!image.data)
        return 0;
    cv::imwrite("../images/groupBW.jpg", image);

    cv::imshow("Image", image);

    Histogram1D h;
    cv::Mat histo = h.getHistogram(image);



//    std::cout<<"size: "<<histo.size();


//    for (int i = 0; i < 256; ++i) {
//        std::cout<<"Value: "<<i<<" = "<<histo.at<float>(i)<<endl;
//    }

    cv::imshow("Histogram", h.getHistogramImage(image));
//
    cv::Mat hi = h.getHistogramImage(image);
    cv::line(hi,cv::Point(70,0), cv::Point(70,255),cv::Scalar(128));
    cv::imshow("histogram with threshold", hi);

    cv::Mat thresholded ;
    cv::threshold(image,thresholded,70,255,cv::THRESH_BINARY);
    thresholded = 255 - thresholded;
    cv::imshow("Binary image", thresholded);

    cv::Mat eq = h.equalize(image);
    cv::imshow("equalized image", eq);

    cv::imshow("equalized H", h.getHistogramImage(eq));

    cv::Mat str = h.stretch(image,0.01f);
    cv::imshow("stretched image", str);
    cv::imshow("stretched H", h.getHistogramImage(str));

    cv::Mat lut(1,256,CV_8U);

    for (int i = 0; i < 256; i++) {
        lut.at<char>(i) = 255-i;
    }

    cv::imshow("negative image", h.applyLookup(image, lut));


    cv::waitKey(0);
    return 0;
}