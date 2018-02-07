#include "../inc/frameProvider.hpp"

FrameProvider::FrameProvider(std::string folder)
{
  DatasetReader* reader = new DatasetReader(folder);

  int nImages =  reader->getNumImages();

  for (int i = 0, i < nImages, i ++)
  {
    
  }
}
