//
// Created by mtb on 18/08/19.
//


#include<opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace std;

void load_image1(){
    cv::Mat image;

    std::cout<<"This image is "<<image.rows<<" x "<<image.cols<<endl;

    image = cv::imread("../images/puppy.bmp");

    if(image.empty()){
        std::cout<<"Empty"<<endl;
    }

    cv::namedWindow("window");
    cv::imshow("window", image);
    cv::waitKey(0);

}

void load_image2(){
    cv::Mat image;


//    image = cv::imread("../images/puppy.bmp",cv::IMREAD_GRAYSCALE);
//    image = cv::imread("../images/puppy.bmp",cv::IMREAD_COLOR);
    image = cv::imread("../images/puppy.bmp",cv::IMREAD_COLOR);
    std::cout<<cv::IMREAD_COLOR<<endl;
    std::cout<<"Channels: "<<image.channels()<<endl;
    if(image.empty()){
        std::cout<<"Empty"<<endl;
    }

    cv::namedWindow("window");
    cv::imshow("window", image);
    cv::waitKey(0);

}

void flip_image(){
        cv::Mat image;
        image = cv::imread("../images/puppy.bmp");

        cv::Mat result;
        cv::flip(image,result,-1);
        cv::namedWindow("flip window");
        cv::imshow("flip window", result);
        //Save file
        cv::imwrite("../images/puppy_flip.bmp",result);
        cv::waitKey(0);

};

void onMouse(int event,int x, int y,int flags,void *param){

}
void event_triggering(){
    cv::Mat image;
    image = cv::imread("../images/puppy.bmp");
    cv::namedWindow("window");
    cv::setMouseCallback("window",onMouse, reinterpret_cast<void*>(&image));


}



int main(int argc, char const *argv[]) {

//    load_image2();
    event_triggering():

    return 0;
}

