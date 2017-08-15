/*
 *
 * This file just use to test function of opencv
 *
 *
 */


#include <iostream>
#include <opencv2/opencv.hpp>
#include <cmath>
#include <GroundTruth.h>

using namespace std;
using namespace cv;
using namespace ORB_SLAM2;

int main(int argc, char *argv[])
{
    Mat mOw(3,3,CV_32F); //remember to init
    mOw.at<float>(0,0) = 3;
    mOw.at<float>(1,0) = 4;
    mOw.at<float>(2,0) = 5;

    mOw.at<float>(0,1) = 1;
    mOw.at<float>(1,1) = 2;
    mOw.at<float>(2,1) = 3;

    mOw.at<float>(0,2) = 1;
    mOw.at<float>(1,2) = 4;
    mOw.at<float>(2,2) = 4;

//    Mat P(3,1,CV_32F); //remember to init
//    P.at<float>(0) = 1;
//    P.at<float>(1) = 4;
//    P.at<float>(2) = 1;

//    Mat PO = P - mOw;
//    cout << "PO = " << PO << endl;
//    float dist = norm(PO);
//    cout << "dist = " << dist << endl;
//    cout << "2*sqrt(5) = " << 2*sqrt(5) << endl;
//    cout << "1240/48 = " << 1240/48 << " 376/48 = " << 376/48 << endl;

    //rowrange test
    Mat IL = mOw.rowRange(1,3).colRange(1,3);
    cout << "Mat size" << IL << endl;

    vector<int> origin;
    origin.reserve(3);
    origin.push_back(2);
    origin.push_back(4);
    origin.push_back(6);

    vector<int> test(origin.begin(),origin.end());
    for (size_t i = 0; i < 3; i++)
    {
        cout << "test[" << i << "] = " << test[i] << endl;
    }



    cout << "mOw = " << mOw << endl;
    cout << mOw.at<float>(0,0) << endl;


    GroundTruth gd;


    Mat pose4 = gd.getFrameTwc(4);
    cout << "pose4 = " << endl <<  pose4 << endl;
    cout << gd.getFrameRwc(4) << endl << gd.getFrametwc(4) << endl;

    return 0;
}

