
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
#include "tracking.hpp"

using namespace cv;

int main( int argc, char** argv )
{
  setlocale(LC_ALL, "C");
  std::string dataset = argv[1];

  Ptr<ORB> orb = ORB::create();
  orb->setMaxFeatures(500);
  Ptr<SURF> surf = SURF::create();
  Ptr<AKAZE> akaze = AKAZE::create();
  FrameProvider* provider = new FrameProvider(dataset,akaze);
  FrameData frame1, frame2;

  //Ptr<DescriptorMatcher> matcher = DescriptorMatcher::create("BruteForce");
  //BFMatcher* matcher = new BFMatcher(NORM_L2,true);

  //FlannBasedMatcher* matcher;
  //Ptr<DescriptorMatcher> BF = DescriptorMatcher::create("BruteForce-Hamming");
  BFMatcher* BF = new BFMatcher(NORM_L2,true);
  Ptr<DescriptorMatcher> FLANN = DescriptorMatcher::create("FlannBased");
  LandmarksManager* landmarksManager = new LandmarksManager(BF);
  Tracking* tracking = new Tracking(BF);

  cv::Mat positionMap(Size(500,500),CV_8U);

  double posX = 250.0;
  double posY = 250.0;

  for (int i = 0; i < provider->nImages; i ++)
  {
    Mat t;
    Landmarks _landmarks;
    if (i != 0)
    {
      frame2 = frame1;
    }
    provider->getFrame(i,frame1);

    if (i != 0)
    {
      t = tracking->trackFrames(frame1,frame2);
      float tx = t.at<double>(0);
      float ty = t.at<double>(1);
      float tz = t.at<double>(2);

      //print("("<< tx << "," << ty << "," << ty << ")");
      posX += tx;
      posY += tz;
    }

    //positionMap.at<int>(int(posX),int(posY)) = 255;
    imshow("Map",positionMap);
    waitKey(1);

    //landmarksManager->createNewLandmarks(i,frame,_landmarks);
    //std::vector < int > found, notFound;
    //notFound = landmarksManager->compareLandmarks(_landmarks,found);
    /*

    keyPoints keyPointsFound, keyPointsNotFound;

    for(auto el:found)
    {
      keyPointsFound.push_back(frame.keyPoints[el]);
    }

    for(auto el:notFound)
    {
      keyPointsNotFound.push_back(frame.keyPoints[el]);
    }

    Mat _display;
    _display = frame.image * 255;
    _display.convertTo(_display,CV_8U);

    drawKeypoints(_display,keyPointsFound,_display,Scalar(0,255,0));
    drawKeypoints(_display,keyPointsNotFound,_display,Scalar(0,0,255));

    imshow("image",_display);
    waitKey(1);*/
  }
}

/*
  provider->getFrame(25,frame);
  provider->getFrame(26,frame2);
  landmarks _test,_test2;
  landmarksManager->createNewLandmarks(25,frame,_test);
  landmarksManager->createNewLandmarks(41,frame2,_test2);

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
*/
