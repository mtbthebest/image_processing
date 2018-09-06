//
// Created by mtb on 18/09/06.
//

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "contentFinder.h"
#include "histogram.h"
#include "colordetector.h"

int main(int argc, char *argv[]) {

    cv::Mat image = cv::imread("../images/waves.jpg");
    if (!image.data) {
        return 0;
    }

    cv::Mat imageROI;
    imageROI = image(cv::Rect(216,33,24,30));

    cv::namedWindow("Reference");
    cv::imshow("Reference",imageROI);

    Histogram1D h;
    cv::Mat hist=h.getHistogramImage(imageROI);

    cv::namedWindow("Reference Hist");
    cv::imshow("Reference Hist",h.getHistogramImage(imageROI));

    ContentFinder finder;
    finder.setHistogram(hist);
    finder.setThreshold(0.01);

    cv::Mat result1 = finder.find(image);

//    cv::namedWindow("Result1");
//    cv::imshow("Result1",result1);

    cv::Mat tmp;
    result1.convertTo(tmp, CV_8U, -1.0, 255.0);
    cv::namedWindow("Backprojection result");
    cv::imshow("Backprojection result",tmp);

    finder.setThreshold(0.12f);
    result1 = finder.find(image);




    cv::waitKey(0);

    return 0;
}