#ifndef FRAMEPROVIDER
#define FRAMEPROVIDER

#include <sstream>
#include <fstream>
#include <dirent.h>
#include <algorithm>
#include <iostream>

#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>


#include "BenchmarkDatasetReader.h"
using namespace cv;

class FrameProvider
{
  public:
    FrameProvider(std::string folder);
};
#endif
