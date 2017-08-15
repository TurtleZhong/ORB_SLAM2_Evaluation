#include <iostream>
#include <opencv2/opencv.hpp>
#include <eigen3/Eigen/Core>
#include <eigen3/Eigen/Dense>
#include <readimage.h>
#include <sstream>

#include <fstream>

#define BOLDBLUE "\033[1m\033[34m" /* Bold Blue */



using namespace std;
using namespace cv;

int main(int argc, char *argv[])
{

    ReadSteroImage imageRead;
    string caliLeftDir = "/home/m/KITTI/dataset/sequences/66/image_0/";
    string caliRightDir = "/home/m/KITTI/dataset/sequences/66/image_1/";
    string sum_of_zero = "";

    int zero_disparity;

    double Kleft[4] = {1198.433333, 1199.553515, 512.000000, 384.000000};
    double Kright[4] = {1201.789777, 1198.515594, 512.000000, 384.000000};
    double dleft[][1] = {-0.115961, 0.129450, 0.002855, 0.006877};
    double dright[][1] = {-0.112037, 0.097115, 0.001031, 0.010830};
    double c0_to_c1[4][4] = { {0.9999, -0.0062, -0.0131, -0.2500},
                             {0.0063, 1.0000, 0.0076, -0.0014},
                             {0.0131, -0.0077, 0.9999, -0.0057},
                             {0.0, 0.0, 0.0, 1.0}};


    cv::Size imageSize(1024, 768);

    cv::Mat K0 = cv::Mat::eye(3, 3, CV_64FC1);
    K0.at<double>(0, 0) = Kleft[0];
    K0.at<double>(1, 1) = Kleft[1];
    K0.at<double>(0, 2) = Kleft[2];
    K0.at<double>(1, 2) = Kleft[3];

    cv::Mat K1 = cv::Mat::eye(3, 3, CV_64FC1);
    K1.at<double>(0, 0) = Kright[0];
    K1.at<double>(1, 1) = Kright[1];
    K1.at<double>(0, 2) = Kright[2];
    K1.at<double>(1, 2) = Kright[3];


    cv::Mat T01(4, 4, CV_64FC1, c0_to_c1);

    cv::Mat D0(4, 1, CV_64FC1, dleft);
    cv::Mat D1(4, 1, CV_64FC1, dright);

    cv::Mat R0, R1, P0, P1, Q;

    cv::stereoRectify(K0, D0, K1, D1, imageSize,
                      T01.rowRange(0, 3).colRange(0, 3), T01.rowRange(0, 3).colRange(3, 4),
                      R0, R1, P0, P1, Q,
                      zero_disparity ? cv::CALIB_ZERO_DISPARITY : 0);

    std::cout << "R0" << std::endl << R0 << std::endl;
    std::cout << "R1" << std::endl << R1 << std::endl;
    std::cout << "P0" << std::endl << P0 << std::endl;
    std::cout << "P1" << std::endl << P1 << std::endl;
    std::cout << "Q" << std::endl << Q << std::endl;

    cv::Mat new_K0 = P0.rowRange(0, 3).colRange(0, 3);
    cv::Mat new_K1 = P1.rowRange(0, 3).colRange(0, 3);

    cout << "new_K0 = " << endl << new_K0 << endl;


    for(int id = 0; id < 2; id++)
    {

        vector<Mat> steroImage;
        steroImage = imageRead.getSteroImage(id);
        Mat imLeft = steroImage[0];
        Mat imRight = steroImage[1];

        Mat map00, map01, map10, map11;
        cv::initUndistortRectifyMap(K0, D0, R0, new_K0, imageSize, CV_32FC1, map00, map01);
        cv::initUndistortRectifyMap(K1, D1, R1, new_K1, imageSize, CV_32FC1, map10, map11);
        //----------------------------------------------------------------------------------------------------------------------
        Mat left,right;
        cv::remap(imLeft, left, map00, map01, CV_INTER_CUBIC);
        cv::remap(imRight, right, map10, map11, CV_INTER_CUBIC);

        cv::cvtColor(left,left,CV_BGR2GRAY);
        cv::cvtColor(right,right,CV_BGR2GRAY);

        if(id <= 9999 && id >= 1000)
        {
            sum_of_zero = "00";
        }
        else if(id <=999 && id >= 100)
        {
            sum_of_zero = "000";
        }
        else if(id <= 99 && id >= 10)
        {
            sum_of_zero ="0000";
        }
        else
        {
            sum_of_zero = "00000";
        }

        stringstream ss;
        string tmp;
        ss << id;
        ss >> tmp;
        string image_name;
        image_name = sum_of_zero + tmp + ".png";
        //cout << "write--- " << image_name << endl;

        string leftDir = caliLeftDir + image_name;
        string rightDir = caliRightDir + image_name;


        imwrite(leftDir,left);
        imwrite(rightDir,right);

        imshow("srcleft",imLeft);
        waitKey(30);
    }

    cout << BOLDBLUE"Congratulations! All Done" << endl;




    return 0;
}




