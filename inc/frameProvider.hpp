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

#include "BenchmarkDatasetReader.h"

#include "FrameData.hpp"
#include "definitions.hpp"

using namespace cv;
using namespace cv::xfeatures2d;
class FrameProvider
{
  public:
    FrameProvider(std::string folder);
    void getFrame(int frameIndex, FrameData& frame);

  private:
    DatasetReader* _reader;
    bool _rectify;
    bool _gamma;
    bool _vignette;
    bool _overExposure;
    double _timestamp;
};
#endif
