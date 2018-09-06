//
// Created by mtb on 18/08/24.
//

#include <iostream>
#include<opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;

void salt_pepper() {
    cv::Mat image = cv::imread("../images/boldt.jpg", 1);

    std::default_random_engine generator;
    std::uniform_int_distribution<int> randomRow(0, image.rows - 1);
    std::uniform_int_distribution<int> randomCol(0, image.cols - 1);

    int i, j, n = 6000;


    for (int k = 0; k < n; k++) {
        i = randomCol(generator);
        j = randomRow(generator);
        if (image.type() == CV_8UC1) {
            image.at<uchar>(j, i) = 255;
        } else if (image.type() == CV_8UC3) {
//            std::cout<<image.at<cv::Vec3b>(j,i)<<endl;
//            std::cout<<image.at<cv::Vec2b>(j,i)<<endl;
            std::cout << image.at<cv::Vec3b>(j, i) << endl;
            //One way of writing
//            image.at<cv::Vec3b>(j,i)[0] = 255;
//            image.at<cv::Vec3b>(j,i)[1] = 255;
//            image.at<cv::Vec3b>(j,i)[2] = 255;

            //Two way of writing
            image.at<cv::Vec3b>(j, i) = cv::Vec3b(255, 255, 255);
        }
    }
    cv::imshow("window", image);
    cv::waitKey(0);
}

void colorReduce(int div = 128) {

    cv::Mat_<cv::Vec3b> image = cv::imread("../images/boldt.jpg", 1);

    int nl = image.rows;
    int nc = image.cols * image.channels();


    for (int j = 0; j < nl; j++) {
        uchar *data = image.ptr<uchar>(j);

        for (int i = 0; i < nc; i++) {
//            data[i] = data[i] / div * div + div/2;
            *data++ = *data / div * div + div / 2;
        }
    }
    cv::imshow("window", image);
    cv::waitKey(0);
}

void iterate_over(int div = 64) {
    cv::Mat image = cv::imread("../images/boldt.jpg", 1);

//    cv::MatIterator_<cv::Vec3b> it;


    int n = static_cast<int>(log(static_cast<double>(div)) / log(2.0) + 0.5);
    uchar mask = 0xFF << n;
    uchar div2 = div >> 1;

    cv::Mat_<cv::Vec3b>::iterator it = image.begin<cv::Vec3b>();
    cv::Mat_<cv::Vec3b>::iterator itend = image.end<cv::Vec3b>();

    for (; it != itend; ++it) {
        (*it)[0] &= mask;
        (*it)[0] += div2;
        (*it)[1] &= mask;
        (*it)[1] += div2;
        (*it)[2] &= mask;
        (*it)[2] += div2;
    }

    //Or
//    *it = *it/div*div+div2;

    cv::imshow("window", image);
    cv::waitKey(0);


}

void sharpen() {
    cv::Mat result, image;
    image = cv::imread("../images/boldt.jpg", 1);
    result.create(image.size(), image.type());

    int nchannels = image.channels();

    for (int j = 1; j < image.rows - 1; j++) {
        const uchar *previous = image.ptr<const uchar>(j - 1);
        const uchar *current = image.ptr<const uchar>(j);
        const uchar *next = image.ptr<const uchar>(j + 1);

        uchar *output = result.ptr<uchar>(j);

        for (int i = nchannels; i < (image.cols - 1) * nchannels; i++) {
            *output++=cv::saturate_cast<uchar>(5*current[i] -current[i-nchannels]-
                    current[i+nchannels] -previous[i]-next[i]);
        }
    }
    result.row(0).setTo(cv::Scalar(0));
    result.row(result.rows -1).setTo(cv::Scalar(0));
    result.col(0).setTo(cv::Scalar(0));
    result.col(result.cols -1).setTo(cv::Scalar(0));


    cv::imshow("window", image);
    cv::imshow("window2", result);
    cv::waitKey(0);
}

void sharpen2D() {
    cv::Mat result, image;
    cv::Mat kernel(3,3,CV_32F,cv::Scalar(0));

    kernel.at<float>(1,1) = 5.0;
    kernel.at<float>(0,1) = -1.0;
    kernel.at<float>(2,1) = -1.0;
    kernel.at<float>(1,0) = -1.0;
    kernel.at<float>(1,2) = -1.0;

    cv::filter2D(image, result, image.depth(),kernel);

    cv::imshow("window", image);
    cv::imshow("window2", result);
    cv::waitKey(0);
}

void split_merge_channels() {
    cv::Mat image = cv::imread("../images/boldt.jpg", 1);

    std::vector<cv::Mat> planes;

    cv::split(image, planes);

    cv::MatIterator_<uchar> it = planes[0].begin<uchar>();
    cv::MatIterator_<uchar> itend = planes[0].end<uchar>();

    for (; it != itend; ++it) {
        (*it) = 255;
    }

    cv::merge(planes, image);


    cv::imshow("window", image);

    cv::waitKey(0);

}



int main(int argc, char const *argv[]) {
//    salt_pepper();
//    colorReduce();

//    iterate_over();

//    sharpen();
    split_merge_channels();
    return 0;

}



