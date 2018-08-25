//
// Created by mtb on 18/08/25.
//

#if !defined PROJECT_COLORDETECT
#define PROJECT_COLORDETECT

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>

class ColorDetector {
private:
    int maxDist;
    cv::Vec3b target;
    cv::Mat converted;
    bool useLab;
    cv::Mat result;


public:
    ColorDetector() : maxDist(100), target(0, 0, 0), useLab(false) {}

    ColorDetector(bool useLab) : maxDist(100), target(0, 0, 0), useLab(useLab) {}

    ColorDetector(uchar blue, uchar green, uchar red, int mxDist = 100, bool useLab = false) :
            maxDist(mxDist), useLab(useLab) { setTargetColor(blue, green, red); }

    int getDistanceToTargetColor(const cv::Vec3b &color) {
        return getColorDistance(color, target);
    }

    int getColorDistance(const cv::Vec3b &color1, const cv::Vec3b &color2) const {
        return abs(color1[0] - color2[0]) +
               abs(color1[1] - color2[1]) +
               abs(color1[2] - color2[2]);

    }
    void setColorDistanceThreshold(int distance) {
        if (distance < 0)distance = 0;
        maxDist = distance;
    }

    int getColorDistanceThreshold() const {
        return maxDist;
    }

    void setTargetColor(uchar blue, uchar green, uchar red) {
        target = cv::Vec3b(blue, green, red);

        if (useLab) {
            cv::Mat tmp(1, 1, CV_8UC3);
            tmp.at<cv::Vec3b>(0, 0) = cv::Vec3b(blue, green, red);

            cv::cvtColor(tmp, tmp, CV_BGR2Lab);
            target = tmp.at<cv::Vec3b>(0, 0);
        }
    }

    void setTargetColor(cv::Vec3b color) {
        target = color;
    }

    cv::Vec3b getTargetColor() const {
        return target;
    }

    cv::Mat process(const cv::Mat &image);

    cv::Mat operator()(const cv::Mat &image) {
        cv::Mat input;
        if (useLab) {
            cv::cvtColor(image, input, CV_BGR2Lab);
        } else {
            input = image;
        }
        cv::Mat output;

        cv::absdiff(input, cv::Scalar(target), output);

        std::vector<cv::Mat> images;
        cv::split(output, images);

        output = images[0] + images[1] + images[2];
        cv::threshold(output, output, maxDist, 255, cv::THRESH_BINARY_INV);

        return output;


    }


};

//cv::Mat ColorDetector::process(const cv::Mat &image) {
//    result.create(image.rows, image.cols, CV_8U);
//
//
////    cv::Mat_<cv::Vec3b>::iterator it= image.begin<cv::Vec3b>();
////    cv::Mat_<cv::Vec3b>::iterator itend= image.end<cv::Vec3b>();
////
////    cv::Mat_<uchar>::iterator itout = result.begin<uchar>()
//
//    return result;
//}

#endif //PROJECT_COLORDETECTOR_H
