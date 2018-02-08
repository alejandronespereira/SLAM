#ifndef LANDMARKSMANAGER
#define LANDMARKSMANAGER

#include <sstream>
#include <fstream>
#include <dirent.h>
#include <algorithm>
#include <iostream>
#include <vector>

#include "opencv2/core.hpp"
#include "opencv2/features2d.hpp"
#include "opencv2/xfeatures2d.hpp"

using namespace cv;
using namespace cv::xfeatures2d;

class LandmarksManager
{
  public:
    LandmarksManager(Ptr<DescriptorMatcher> matcher);
    void addLandmarks(landmarks newLandmarks);
    void compareLandmarks(landmarks newLandmarks, landmarks& matchingLandmarks);
  private:
    landmarks _landmarks;
    Ptr<DescriptorMatcher> _matcher;
    Mat _descriptors;

};
#endif
