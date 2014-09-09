#ifndef FEATURESMATCHER_H
#define FEATURESMATCHER_H

#include "trackerfeatures.h"

using namespace cv;
using namespace std;

class FeaturesMatcher
{
public:
    FeaturesMatcher();

    void prepMatcher(TrackerFeatures);
    Mat getMatch(Mat);

    TrackerFeatures sceneFeatures;

private:
    FlannBasedMatcher matcher;
    vector<vector<DMatch> > matches;
    vector<Mat> mask;
    int k;
    TrackerFeatures objectFeatures;
};

#endif // FEATURESMATCHER_H
