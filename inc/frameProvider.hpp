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

using namespace cv;
using namespace cv::xfeatures2d;
class FrameProvider
{
  public:
    FrameProvider(std::string folder);
    void getFrame(int frameIndex, FrameData& frame);

  private:
    DatasetReader* reader;
    bool rectify;
    bool gamma;
    bool vignette;
    bool overExposure;
    double timestamp;
};
#endif
