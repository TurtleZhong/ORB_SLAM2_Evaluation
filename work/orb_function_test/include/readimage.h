#ifndef READIMAGE_H
#define READIMAGE_H
#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>
#include <string>
#include <fstream>

using namespace std;
using namespace cv;


class ReadSteroImage
{
public:
    ReadSteroImage();


    vector<Mat> getSteroImage(int imageID);
    void loadSteroImages();

public:
    vector <cv::Mat> steroImages; //here we save the poses of the sequence. default: sequence00
    string sequenceDir;
    string timeStampDir;



};
#endif // READIMAGE_H
