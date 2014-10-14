#include "featuresmatcher.h"

FeaturesMatcher::FeaturesMatcher()
{
//#ifdef ANDROID
//    matcher = FlannBasedMatcher (new flann::LshIndexParams(12, 12, 1), new flann::SearchParams(32));
//#else
    matcher = new FlannBasedMatcher (new flann::CompositeIndexParams(5, 32, 11, cvflann::FLANN_CENTERS_RANDOM, 0.2), new flann::SearchParams(32));
//#endif
    k = 2;
}

void FeaturesMatcher::prepMatcher(TrackerFeatures *objectFeatures)
{
    matcher->clear();
    vector<Mat> descriptorVector;
    descriptorVector.push_back(objectFeatures->descriptors);
    matcher->add(descriptorVector);
    matcher->train();
    this->objectFeatures = objectFeatures;
}

Mat FeaturesMatcher::getMatch(Mat scene_img)
{
    matcher->knnMatch(sceneFeatures->descriptors, matches, k, mask, false);

    double max_dist = 0; double min_dist = 100;

    for( int i = 0; i < sceneFeatures->descriptors.rows; i++ )
    {
        vector<DMatch> match = matches[i];
        for(int j = 0; j< k; j++){
            double dist = match[j].distance;
            if( dist < min_dist ) min_dist = dist;
            if( dist > max_dist ) max_dist = dist;
        }
    }

    vector<DMatch> good_matches;

    for( int i = 0; i < sceneFeatures->descriptors.rows; i++ )
    {
        vector<DMatch> match = matches[i];
        for(int j=0; j<k; j++){
            if( match[j].distance <= max(2*min_dist, 0.02))
            {
                good_matches.push_back(match[j]);
            }
        }
    }

    Mat img_matches = scene_img.clone();

    vector<Point2f> obj;
    vector<Point2f> scene;

    for( unsigned int i = 0; i < good_matches.size(); i++ )
    {
        obj.push_back( objectFeatures->keyPoints[ good_matches[i].trainIdx ].pt );
        scene.push_back( sceneFeatures->keyPoints[ good_matches[i].queryIdx ].pt );
    }

    std::vector<uchar> outlier_mask;

    unsigned int min_matches = 8;

    if(obj.size() >= min_matches && scene.size() >= min_matches){
        Mat H = findHomography( obj, scene, CV_RANSAC, 1.0, outlier_mask );

        //-- Get the corners from the image_1 ( the object to be "detected" )
        std::vector<Point2f> obj_corners(4);
        obj_corners[0] = cvPoint(0,0);
        obj_corners[1] = cvPoint( Mat(objectFeatures->image).cols, 0 );
        obj_corners[2] = cvPoint( Mat(objectFeatures->image).cols, Mat(objectFeatures->image).rows );
        obj_corners[3] = cvPoint( 0, Mat(objectFeatures->image).rows );
        std::vector<Point2f> scene_corners(4);

        perspectiveTransform(obj_corners, scene_corners, H);

        line( img_matches, scene_corners[0], scene_corners[1], Scalar(0, 255, 0), 4 );
        line( img_matches, scene_corners[1], scene_corners[2], Scalar( 0, 255, 0), 4 );
        line( img_matches, scene_corners[2], scene_corners[3], Scalar( 0, 255, 0), 4 );
        line( img_matches, scene_corners[3], scene_corners[0], Scalar( 0, 255, 0), 4 );
    }

    return img_matches;
}


