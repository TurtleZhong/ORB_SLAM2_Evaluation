#include "readimage.h"



ReadSteroImage::ReadSteroImage()
{
    this->loadSteroImages();
}


void ReadSteroImage::loadSteroImages()
{
    this->sequenceDir = "/home/m/KITTI/dataset/sequences/0815";
    this->timeStampDir = this->sequenceDir + "/timestamp.txt";

//    cout << "sequenceDir = " << sequenceDir << endl;
//    cout << "timeStampDir = " << timeStampDir << endl;


}

vector<Mat> ReadSteroImage::getSteroImage(int imageID)
{
    fstream inFile;
    vector<Mat> steroimage;
    inFile.open(timeStampDir);

    for(int i = 0; i < imageID; i++)
    {
        string tmp;
        inFile>>tmp;
        inFile.get();
    }

    Mat imLeft,imRight;
    string tmp;
    string imLeftDir, imRightDir;

    inFile >> tmp;
    imLeftDir = sequenceDir + "/cam0/data/" + tmp;
    imRightDir = sequenceDir + "/cam1/data/" +tmp;

    //cout << "imLeftDir = " << imLeftDir << endl;

    imLeft = imread(imLeftDir);

    imRight = imread(imRightDir);


    steroimage.push_back(imLeft);
    steroimage.push_back(imRight);

    return steroimage;
}
