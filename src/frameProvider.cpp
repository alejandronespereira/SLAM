#include "../inc/frameProvider.hpp"

FrameProvider::FrameProvider(std::string folder,Ptr<Feature2D> detector)
{
  _reader = new DatasetReader(folder);
  K = _reader->getUndistorter()->getK_rect();
  nImages =  _reader->getNumImages();
  _rectify = true;
  _gamma = true;
  _vignette = false;
  _overExposure = false;
  _detector = detector;
}

void FrameProvider::getFrame(int frameID, FrameData& frame)
{
  ExposureImage* exposureImage;
  exposureImage = _reader->getImage(frameID, _rectify,_gamma,_vignette,_overExposure);
  Eigen::Matrix3f intrinsics;

  Mat image = cv::Mat(exposureImage->h, exposureImage->w, CV_32F, exposureImage->image) * (1/255.0f);
  intrinsics = _reader->getUndistorter()->getK_rect();
  Matx33d K;
  for(int i = 0; i < 3; i++)
  {
    for(int j = 0; j < 3; j++)
    {
      K(i,j) = intrinsics(i,j);
    }
  }
  Mat temp[] = {image,image,image};
  merge(temp,3,image);

  Mat1f desc;

  Mat gray;
  KeyPoints kp;

  Mat _temp;
  _temp = image * 255;
  _temp.convertTo(gray,CV_8U);
  _detector->detectAndCompute( gray, noArray(),kp,desc);

  frame.frameID = frameID;
  frame.image = image;
  frame.keyPoints = kp;
  frame.descriptors = desc;
  frame.timestamp = exposureImage->timestamp;
  frame.K = K;
}
