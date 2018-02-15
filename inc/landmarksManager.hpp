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
#include "Eigen/Core"
#include "FrameData.hpp"
#include "definitions.hpp"
#include "debugging.hpp"

using namespace cv;
using namespace cv::xfeatures2d;

class LandmarksManager
{
  public:
    LandmarksManager();
    LandmarksManager(Ptr<DescriptorMatcher> matcher);
    std::vector<int> compareLandmarks(Landmarks& newLandmarks, std::vector<int>& found);
    void createNewLandmarks(int frameID, FrameData& frame, Landmarks& newLandmarks);

  private:
    Landmarks _landmarks;
    Ptr<DescriptorMatcher> _matcher;
    Mat _descriptors;
    double _focal;
    Point2d pp;
    void computeDescriptors(Landmarks& landmarksToCompute, Mat& descriptors);

};
#endif
