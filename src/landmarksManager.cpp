#include "LandmarksManager.hpp"

LandmarksManager::LandmarksManager(Ptr<DescriptorMatcher> matcher) : _matcher(matcher)
{

}


void addLandmarks(landmarks& newLandmarks)
{
  _landmarks.insert( _landmarks.end(), newLandmarks.begin(), newLandmarks.end() );
  for (int i = 0; i < newLandmarks.size(); i++)
  {
    //hconcat(_descriptors, newLandmarks[i].descptor H);
  }
}

void compareLandmarks(keyPoints newLandmarks, landmarks& matchingLandmarks)
{

}
