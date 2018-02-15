#include "tracking.hpp"

Tracking::Tracking()
{

}

Tracking::Tracking(Ptr<DescriptorMatcher> matcher) : _matcher(matcher)
{

}

Mat Tracking::trackFrames(FrameData& frame1, FrameData& frame2)
{
  KeyPoints kp1,kp2;
  Mat desc1,desc2;
  kp1 = frame1.keyPoints;
  kp2 = frame2.keyPoints;
  desc1 = frame1.descriptors;
  desc2 = frame2.descriptors;
  std::vector<DMatch> matches;

  _matcher->match(desc1,desc2, matches);

  std::vector<Point2d> pts1,pts2;
  for(auto match: matches)
  {
      pts1.push_back(kp1[match.queryIdx].pt);
      pts2.push_back(kp1[match.trainIdx].pt);
  }

  Mat E,R,t,mask;
  double focal = frame1.K(0,0);
  Point2d pp = Point2d(frame1.K(0,2),frame1.K(1,2));

  E = findEssentialMat(pts1,pts2,frame1.K);
  recoverPose(E,pts1,pts2,R,t,focal,pp,mask);
  return t;
}
