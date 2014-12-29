#ifndef FEATURESMATCHER_H
#define FEATURESMATCHER_H

#include "trackerfeatures.h"

using namespace cv;
using namespace std;
using namespace cv::gpu;

class FeaturesMatcher
{
public:
    FeaturesMatcher();

    void prepMatcher(TrackerFeatures*);
    Mat getMatch(Mat);

    TrackerFeatures *sceneFeatures;

private:
//    FlannBasedMatcher *matcher;
    BFMatcher_GPU *matcher;
    vector<vector<DMatch> > matches;
    vector<GpuMat> mask;
    int k;
    TrackerFeatures *objectFeatures;
};

#endif // FEATURESMATCHER_H
