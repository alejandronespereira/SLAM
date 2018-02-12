#ifndef DEFINITIONS
#define DEFINITIONS

#include "opencv2/core.hpp"
#include "opencv2/features2d.hpp"
#include "opencv2/xfeatures2d.hpp"
#include <vector>

#include "Landmark.hpp"

#define print(x) std::cout << x << std::endl

typedef std::vector< cv::KeyPoint> keyPoints;
typedef std::vector< Landmark > landmarks;
//std::vector<int> matches;


#endif
