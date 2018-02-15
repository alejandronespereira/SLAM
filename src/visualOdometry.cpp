#include "visualOdometry.hpp"

VisualOdometry::VisualOdometry(Eigen::Matrix3f K)
{
    _focal = K(0,0);
    _pp.x = K(0,2);
    _pp.y = K(1,2);
}


VisualOdometry::getPoseFromNewFrame()
{

}
