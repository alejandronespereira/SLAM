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

#include "FrameData.hpp"
#include "definitions.hpp"
#include "debugging.hpp"

using namespace cv;
using namespace cv::xfeatures2d;

class LandmarksManager
{
  public:
    LandmarksManager(Ptr<DescriptorMatcher> matcher);
    LandmarksManager();
    void addLandmarks(landmarks& newLandmarks);
    std::vector<int> compareLandmarks(landmarks& newLandmarks, std::vector<int>& found);
    void createNewLandmarks(int frameID, FrameData& frame, landmarks& newLandmarks);

  private:
    landmarks _landmarks;
    Ptr<DescriptorMatcher> _matcher;
    Mat _descriptors;

    void computeDescriptors(landmarks& landmarksToCompute, Mat& descriptors);

};
#endif
