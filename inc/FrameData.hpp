#ifndef FRAMEDATA
#define FRAMEDATA

#include "opencv2/core.hpp"
#include "opencv2/features2d.hpp"
#include "opencv2/xfeatures2d.hpp"
#include <vector>

using namespace cv;

struct FrameData
{
  int frameID;
  std::vector<KeyPoint> keyPoints;
  Mat descriptors;
  Mat image;
  double timestamp;
  Matx33d K;
  std::vector< int > validKeyPoints;
};

#endif
