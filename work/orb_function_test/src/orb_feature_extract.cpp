#include <iostream>
#include <vector>
#include <cmath>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int nlevels = 8;
float scaleFactor = 1.2;
int nfeatures = 1200;


int main ()
{

	float factor = 1.0f / scaleFactor;
	float nDesiredFeaturesPerScale = nfeatures*(1 - factor)/(1 - (float)pow((double)factor, (double)nlevels));
	cout << "nDesiredFeaturesPerScale = " << nDesiredFeaturesPerScale << endl;
	// int sumFeatures = 0;
	// std::vector<int> mnFeaturesPerLevel;
 //    for( int level = 0; level < nlevels-1; level++ )
 //    {
 //        mnFeaturesPerLevel[level] = cvRound(nDesiredFeaturesPerScale);
 //        sumFeatures += mnFeaturesPerLevel[level];
 //        nDesiredFeaturesPerScale *= factor;
 //    }
 //    cout << "sumFeatures = " << sumFeatures << endl;



    return 0;

}
