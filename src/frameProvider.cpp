#include "../inc/frameProvider.hpp"

FrameProvider::FrameProvider(std::string folder)
{
  reader = new DatasetReader(folder);
  int nImages =  reader->getNumImages();
  rectify = true;
  gamma = true;
  vignette = true;
  overExposure = true;

  /*
  ExposureImage* exposureImage;
  for (int i = 0; i < nImages; i ++)
  {
    exposureImage = reader->getImage(i, true,true,false,false);
    Mat image = cv::Mat(exposureImage->h, exposureImage->w, CV_32F, exposureImage->image) * (1/255.0f);
    Mat temp[] = {image,image,image};
    merge(temp,3,image);

    Mat desc,gray;
    std::vector<KeyPoint> kp;
    int minHessian = 400;

    Ptr<SURF> detector = SURF::create( minHessian );
    Mat _temp;
    _temp = image * 255;
    _temp.convertTo(gray,CV_8U);
    //detector->detect( gray, kp);
    detector->detectAndCompute( gray, noArray(),kp,desc);

    Mat keyPointsImage;

    drawKeypoints(gray,kp,keyPointsImage,Scalar::all(-1));
    imshow("Image",keyPointsImage);

    waitKey(1);
    frameData frame;
    frame.image = image;
    frame.keyPoints = kp;
    frame.descriptors = desc;
  }
  */
}

void FrameProvider::getFrame(int frameIndex, FrameData& frame)
{
  ExposureImage* exposureImage;
  exposureImage = reader->getImage(frameIndex, rectify,gamma,vignette,overExposure);
  Mat image = cv::Mat(exposureImage->h, exposureImage->w, CV_32F, exposureImage->image) * (1/255.0f);
  Mat temp[] = {image,image,image};
  merge(temp,3,image);

  Mat desc,gray;
  std::vector<KeyPoint> kp;
  int minHessian = 400;

  Ptr<SURF> detector = SURF::create( minHessian );
  Mat _temp;
  _temp = image * 255;
  _temp.convertTo(gray,CV_8U);

  detector->detectAndCompute( gray, noArray(),kp,desc);
  frame.image = image;
  frame.keyPoints = kp;
  frame.descriptors = desc;
  frame.timestamp = exposureImage->timestamp;

}
