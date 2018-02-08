
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
  FrameData frame;
  provider->getFrame(25,frame);
  std::cout << frame.descriptors.size() << std::endl;
  Mat _temp;
  _temp = frame.image * 255;
  _temp.convertTo(_temp,CV_8U);
  drawKeypoints(_temp,frame.keyPoints,_temp,Scalar(0,255,0));
  imshow("Image",_temp);
  waitKey(0);



}
