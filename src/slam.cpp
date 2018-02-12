
#include <iostream>

#include <locale.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>


#include "opencv2/opencv.hpp"
#include "frameProvider.hpp"
#include "FrameData.hpp"
#include "landmarksManager.hpp"

using namespace cv;

int main( int argc, char** argv )
{
  setlocale(LC_ALL, "C");
  std::string dataset = argv[1];

  FrameProvider* provider = new FrameProvider(dataset);
  FrameData frame,frame2;
  //Ptr<DescriptorMatcher> matcher = DescriptorMatcher::create("BruteForce");
  BFMatcher* matcher = new BFMatcher(NORM_L2,true);
  LandmarksManager* landmarksManager = new LandmarksManager(matcher);

  provider->getFrame(25,frame);
  provider->getFrame(26,frame2);
  landmarks _test,_test2;
  landmarksManager->createNewLandmarks(25,frame,_test);
  landmarksManager->createNewLandmarks(41,frame2,_test2);
  std::vector < int > found, notFound;
  notFound = landmarksManager->compareLandmarks(_test,found);
  notFound = landmarksManager->compareLandmarks(_test2,found);
  Mat _temp, _temp2;
  _temp = frame.image * 255;
  _temp.convertTo(_temp,CV_8U);
  drawKeypoints(_temp,frame.keyPoints,_temp,Scalar(0,255,0));

  imshow("Image",_temp);
  waitKey(0);


  _temp2 = frame2.image *255;
  _temp2.convertTo(_temp2,CV_8U);
  keyPoints keyPointsFound, keyPointsNotFound;

  for(auto el:found)
  {
    keyPointsFound.push_back(frame2.keyPoints[el]);
  }

  for(auto el:notFound)
  {
    keyPointsNotFound.push_back(frame2.keyPoints[el]);
  }
  print(keyPointsFound.size());
  print(keyPointsNotFound.size());
  drawKeypoints(_temp2,keyPointsFound,_temp2,Scalar(0,255,0));
  drawKeypoints(_temp2,keyPointsNotFound,_temp2,Scalar(255,0,0));
  imshow("second frame",_temp2);
  waitKey(0);
}
