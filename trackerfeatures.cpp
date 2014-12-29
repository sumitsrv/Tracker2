#include "trackerfeatures.h"

TrackerFeatures::TrackerFeatures()
{
}

//#ifdef ANDROID
//    ORB TrackerFeatures::featureDetector = ORB(500,1.2f, 8, 31, 0, 2, ORB::HARRIS_SCORE, 31 );
//#else
    SURF_GPU TrackerFeatures::featureDetector = SURF_GPU(600, 3, 2, true, false);
//#endif

void TrackerFeatures::detect(GpuMat image){
    GpuMat noArray;
    featureDetector.operator ()(image, noArray, this->keyPoints, this->descriptors, false);
}
