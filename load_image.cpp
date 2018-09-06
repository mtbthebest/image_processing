//
// Created by mtb on 18/08/19.
//

#include <iostream>
#include<opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;

void load_image1() {
    cv::Mat image;

    std::cout << "This image is " << image.rows << " x " << image.cols << endl;

    image = cv::imread("../images/puppy.bmp");

    if (image.empty()) {
        std::cout << "Empty" << endl;
    }

    cv::namedWindow("window");
    cv::imshow("window", image);
//    cv::waitKey(5000);
    cv::waitKey(0);

}

void load_image2() {
    cv::Mat image;


//    image = cv::imread("../images/puppy.bmp",cv::IMREAD_GRAYSCALE);
//    image = cv::imread("../images/puppy.bmp",cv::IMREAD_COLOR);
    image = cv::imread("../images/puppy.bmp", cv::IMREAD_COLOR);
    std::cout << cv::IMREAD_COLOR << endl;
    std::cout << "Channels: " << image.channels() << endl;
    if (image.empty()) {
        std::cout << "Empty" << endl;
    }

    cv::namedWindow("window");
    cv::imshow("window", image);
    cv::waitKey(0);

}

void flip_image() {
    cv::Mat image;
    image = cv::imread("../images/puppy.bmp");

    cv::Mat result;
    cv::flip(image, result, -1);
    cv::namedWindow("flip window");
    cv::imshow("flip window", result);
    //Save file
    cv::imwrite("../images/puppy_flip.bmp", result);
    cv::waitKey(0);

};

void onMouse(int event, int x, int y, int flags, void *param) {
    cv::Mat *im = reinterpret_cast<cv::Mat *>(param);
    switch (event) {
        case cv::EVENT_LBUTTONDOWN:
            std::cout << " at (" << x << " , " << y << ")value is: "
                      << static_cast<int>(im->at<uchar>(cv::Point(x, y)));
    }
}

void event_triggering() {
    cv::Mat image;
    image = cv::imread("../images/puppy.bmp");
    cv::namedWindow("window");
    cv::setMouseCallback("window", onMouse, reinterpret_cast<void *>(&image));
    cv::imshow("window", image);
    cv::waitKey(0);
}

void draw() {

    cv::Mat image = cv::imread("../images/puppy.bmp");
    cv::circle(image, cv::Point(100, 50), 25, cv::Scalar(255, 0, 0), 1);
    cv::namedWindow("window");
    cv::imshow("window", image);
    cv::waitKey(0);

}

void getRoi() {
    cv::Mat image = cv::imread("../images/puppy.bmp");
    cv::Mat logo = cv::imread("../images/logo.bmp");
    cv::Mat imageROI(image, cv::Rect(image.cols - logo.cols, image.rows - logo.rows, logo.cols, logo.rows));

    cv::Mat mask(logo);

//    logo.copyTo(imageROI);
    logo.copyTo(imageROI, mask);


//    cv::imshow("window", imageROI);
    cv::imshow("window_ROI", image);
    cv::waitKey(0);
}


int main(int argc, char const *argv[]) {

//    load_image1();
//    event_triggering();
//    draw();
    getRoi();


    return 0;

}

