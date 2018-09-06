//
// Created by mtb on 18/09/06.
//

#include <iostream>
using namespace std;

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "imageComparator.h"

int main()
{
    // Read reference image
    cv::Mat image= cv::imread("../images/waves.jpg");
    if (!image.data)
        return 0;

    // Display image
    cv::namedWindow("Query Image");
    cv::imshow("Query Image",image);

    ImageComparator c;
    c.setReferenceImage(image);

    // Read an image and compare it with reference
    cv::Mat input= cv::imread("../images/dog.jpg");
    cout << "waves vs dog: " << c.compare(input) << endl;

    // Read an image and compare it with reference
    input= cv::imread("../images/marais.jpg");
    cout << "waves vs marais: " << c.compare(input) << endl;

    // Read an image and compare it with reference
    input= cv::imread("../images/bear.jpg");
    cout << "waves vs bear: " << c.compare(input) << endl;

    // Read an image and compare it with reference
    input= cv::imread("../images/beach.jpg");
    cout << "waves vs beach: " << c.compare(input) << endl;



    cv::waitKey();
    return 0;
}