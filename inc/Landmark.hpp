#ifndef LANDMARK
#define LANDMARK

#include "opencv2/core.hpp"
#include "opencv2/features2d.hpp"
#include "opencv2/xfeatures2d.hpp"
#include <vector>

using namespace cv;

struct Landmark
{
  std::vector < int > framesPresent;
  std::vector < Point > positions;
  int count;
  //Point3 worldCoordinates;
};

#endif
