#ifndef TRACKERFEATURES_H
#define TRACKERFEATURES_H

#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/core/core.hpp>
#include<opencv2/features2d/features2d.hpp>
#include<opencv2/highgui/highgui.hpp>
#include <opencv2/calib3d/calib3d.hpp>
//#ifndef ANDROID
#include "opencv2/nonfree/nonfree.hpp"
//#endif
#include <opencv2/ml/ml.hpp>

using namespace cv;
using namespace std;

class TrackerFeatures
{
public:
    TrackerFeatures();
    void detect(Mat);

    vector<KeyPoint> keyPoints;
    Mat descriptors;
    Mat image;

private:
//#ifdef ANDROID
//    static ORB featureDetector;
//#else
    static SURF featureDetector;
//#endif

};

#endif // TRACKERFEATURES_H
