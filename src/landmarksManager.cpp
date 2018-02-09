#include "landmarksManager.hpp"

LandmarksManager::LandmarksManager(Ptr<DescriptorMatcher> matcher) : _matcher(matcher)
{
}
LandmarksManager::LandmarksManager()
{
}


void LandmarksManager::addLandmarks(landmarks& newLandmarks)
{
  _landmarks.insert( _landmarks.end(), newLandmarks.begin(), newLandmarks.end() );
  for (int i = 0; i < newLandmarks.size(); i++)
  {
    //hconcat(_descriptors, newLandmarks[i].descptor H);
  }
}

void LandmarksManager::compareLandmarks(landmarks& newLandmarks, landmarks& matchingLandmarks)
{

}

void LandmarksManager::createNewLandmarks(int frameID, FrameData& frame,  landmarks& newLandmarks)
{
  for(int i = 0; i < frame.keyPoints.size(); i++)
  {
    Landmark tempLandMark;
    tempLandMark.framesPresent.push_back(frameID);
    tempLandMark.positions.push_back(frame.keyPoints[i].pt);
    frame.descriptors.row(i).copyTo(tempLandMark.descriptor);
    newLandmarks.push_back(tempLandMark);
  }
  print("HELLO");
}
