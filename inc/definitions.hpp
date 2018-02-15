#ifndef DEFINITIONS
#define DEFINITIONS

#include "opencv2/core.hpp"
#include "opencv2/features2d.hpp"
#include "opencv2/xfeatures2d.hpp"
#include <vector>

#include "Landmark.hpp"
using namespace std;
using namespace cv;

#define print(x) cout << x << endl

typedef vector< KeyPoint> KeyPoints;
typedef vector< Landmark > Landmarks;
typedef vector< DMatch > Matches;
//std::vector<int> matches;


#endif
