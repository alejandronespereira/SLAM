#ifndef FRAMEPROVIDER
#define FRAMEPROVIDER

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

#include "BenchmarkDatasetReader.h"

#include "FrameData.hpp"
#include "definitions.hpp"
#include "debugging.hpp"

using namespace cv;
using namespace cv::xfeatures2d;
class FrameProvider
{
  public:
    FrameProvider(std::string folder);
    FrameProvider(std::string folder,Ptr<Feature2D> _detector);
    void getFrame(int frameID, FrameData& frame);
    int nImages;
    Eigen::Matrix3f K;
  private:
    DatasetReader* _reader;
    Ptr<Feature2D> _detector;
    bool _rectify;
    bool _gamma;
    bool _vignette;
    bool _overExposure;
    double _timestamp;
};
#endif
