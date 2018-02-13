#ifndef VISUALIZATION
#define VISUALIZATION

#include <iostream>

#include "Eigen/Core"

#include "opencv2/opencv.hpp"
#include "opencv2/core.hpp"
#include "opencv2/viz.hpp"
#include "definitions.hpp"

using namespace cv;
using namespace std;

class Visualization
{
  public:
    Visualization(std::string windowName, Eigen::Matrix3f K);
  private:
    Matx33d _K;

};
#endif
