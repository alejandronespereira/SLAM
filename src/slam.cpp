
#include <iostream>

#include <locale.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <ctime>

#include "opencv2/opencv.hpp"
#include "frameProvider.hpp"
#include "FrameData.hpp"
#include "landmarksManager.hpp"
#include "tracking.hpp"

using namespace cv;
using namespace std;

int main( int argc, char** argv )
{
  setlocale(LC_ALL, "C");
  string dataset = argv[1];

  Ptr<ORB> orb = ORB::create();
  orb->setMaxFeatures(500);
  Ptr<SURF> surf = SURF::create();
  Ptr<AKAZE> akaze = AKAZE::create();
  FrameProvider* provider = new FrameProvider(dataset,orb);
  FrameData frame1, frame2;

  //Ptr<DescriptorMatcher> matcher = DescriptorMatcher::create("BruteForce");
  //BFMatcher* matcher = new BFMatcher(NORM_L2,true);

  //FlannBasedMatcher* matcher;
  //Ptr<DescriptorMatcher> BF = DescriptorMatcher::create("BruteForce-Hamming");
  BFMatcher* BF = new BFMatcher(NORM_L2,true);
  //Ptr<DescriptorMatcher> FLANN = DescriptorMatcher::create("FlannBased");

  flann::LshIndexParams* params = new flann::LshIndexParams(20, 10, 2);
  FlannBasedMatcher* FLANN = new FlannBasedMatcher(params);

  LandmarksManager* landmarksManager = new LandmarksManager(BF);
  Tracking* tracking = new Tracking(BF);

  Mat positionMap;
  positionMap = Mat::zeros(Size(500,500),CV_8UC3);

  double posX_xz = 250.0;
  double posY_xz = 250.0;

  double posX_xy = 250.0;
  double posY_xy = 250.0;

  double posX_yz = 250.0;
  double posY_yz = 250.0;

  Vec3b colorXZ = Vec3b(255,0,0);
  Vec3b colorXY = Vec3b(0,255,0);
  Vec3b colorYZ = Vec3b(0,0,255);
  clock_t begin = clock();
  clock_t end;
  double elapsed_secs;

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
      /*posX_xz += tx;
      posY_xz += tz;

      posX_xy += tx;
      posY_xy += ty;

      posX_yz += ty;
      posY_yz += tz;
      */
    }
    /*
    positionMap.at<Vec3b>(Point(int(posX_xz),int(posY_xz))) = colorXZ;
    positionMap.at<Vec3b>(Point(int(posX_xy),int(posY_xy))) = colorXY;
    positionMap.at<Vec3b>(Point(int(posX_yz),int(posY_yz))) = colorYZ;

    */
    if(i%10 == 0 && i != 0)
    {
      end = clock();
      elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
      begin = clock();
      print("FPS:" << elapsed_secs / 10);
    }

    /*

    if (i%100 == 0)
    {
      print(i << "/" << provider->nImages);
      imshow("Map",positionMap);
      waitKey(1);
    }*/

    //landmarksManager->createNewLandmarks(i,frame,_landmarks);
    //vector < int > found, notFound;
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
  waitKey(0);
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
