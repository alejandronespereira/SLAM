#ifndef FRAMEDATA
#define FRAMEDATA

#include "opencv2/core.hpp"
#include "opencv2/features2d.hpp"
#include "opencv2/xfeatures2d.hpp"
#include <vector>

using namespace cv;

struct FrameData
{
  std::vector<KeyPoint> keyPoints;
  Mat descriptors;
  Mat image;
  double timestamp;
};

#endif
