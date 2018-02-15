#ifndef TRACKING
#define TRACKING

#include <iostream>

#include "opencv2/core.hpp"
#include "opencv2/features2d.hpp"
#include "opencv2/xfeatures2d.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include "Eigen/Core"

#include "definitions.hpp"
#include "Landmark.hpp"
#include "FrameData.hpp"

using namespace std;
using namespace cv;

class Tracking
{
  public:
    Tracking();
    Tracking(Ptr<DescriptorMatcher> matcher);
    Mat trackFrames(FrameData& frame1, FrameData& frame2);

  private:
    Ptr<DescriptorMatcher> _matcher;
    double _focal;
    Point2d _pp;


};


#endif
