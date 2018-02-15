#ifndef VISUALODOMETRY
#define VISUALODOMETRY


#include "opencv2/core.hpp"
#include "opencv2/features2d.hpp"
#include "opencv2/xfeatures2d.hpp"
#include "Eigen/Core"

#include "definitions.hpp"
#include <iostream>

using namespace cv;

class VisualOdometry
{
  public:
      VisualOdometry(Eigen::Matrix3f K);
      void getNewPose(keyPoints& points1,keyPoints& points2, Matches& matches);
  private:

};

#endif
