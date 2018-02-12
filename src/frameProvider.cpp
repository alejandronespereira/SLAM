#include "../inc/frameProvider.hpp"

FrameProvider::FrameProvider(std::string folder)
{
  _reader = new DatasetReader(folder);
  int nImages =  _reader->getNumImages();
  _rectify = true;
  _gamma = true;
  _vignette = false;
  _overExposure = false;

}

void FrameProvider::getFrame(int frameIndex, FrameData& frame)
{
  ExposureImage* exposureImage;
  exposureImage = _reader->getImage(frameIndex, _rectify,_gamma,_vignette,_overExposure);
  Mat image = cv::Mat(exposureImage->h, exposureImage->w, CV_32F, exposureImage->image) * (1/255.0f);
  Mat temp[] = {image,image,image};
  merge(temp,3,image);

  Mat1f desc;

  Mat gray;
  keyPoints kp;
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
