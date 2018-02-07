#include "../inc/frameProvider.hpp"

FrameProvider::FrameProvider(std::string folder)
{
  DatasetReader* reader = new DatasetReader(folder);

  int nImages =  reader->getNumImages();
  ExposureImage* image;
  for (int i = 0; i < nImages; i ++)
  {
    image = reader->getImage(i, true,false,false,false);
    imshow("Image", cv::Mat(image->h, image->w, CV_32F, image->image) * (1/255.0f));
    waitKey(0);
  }
}
