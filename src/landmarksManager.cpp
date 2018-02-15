#include "landmarksManager.hpp"

LandmarksManager::LandmarksManager(Ptr<DescriptorMatcher> matcher): _matcher(matcher)//, Eigen::Matrix3f K) : _matcher(matcher)
{
  /*_focal = K(0,0);
  pp.x = K(0,2);
  pp.y = K(1,2);*/
}
LandmarksManager::LandmarksManager()
{
}

std::vector<int> LandmarksManager::compareLandmarks(Landmarks& newLandmarks, std::vector<int>& found)
{
  std::vector<int> allIds(newLandmarks.size());
  std::iota ( std::begin(allIds),std::end(allIds),0);
  if(_landmarks.size() == 0)
  {
    _landmarks = newLandmarks;
    computeDescriptors(newLandmarks,_descriptors);
    return allIds;
  }

  Mat newDescriptors;
  computeDescriptors(newLandmarks,newDescriptors);
  std::vector<DMatch> matches;

  _matcher->match(newDescriptors,_descriptors, matches);

  int currentFrame = newLandmarks[0].framesPresent[0];
  int t = 0;
  // Update landmarks
  for(int m = 0; m < matches.size(); m++)
  {
    if (_landmarks[matches[m].trainIdx].framesPresent[_landmarks[matches[m].trainIdx].framesPresent.size() -1 ] != currentFrame)
    {
      t++;
      print(_landmarks[matches[m].trainIdx].framesPresent[_landmarks[matches[m].trainIdx].framesPresent.size() -1 ] << "|" << currentFrame);
      continue;
    }
    found.push_back(matches[m].queryIdx);


    // newlandmark[m.queryIdx] goes with landmarks[m.trainIdx]
    _landmarks[matches[m].trainIdx].framesPresent.push_back(newLandmarks[matches[m].queryIdx].framesPresent[0]);
    _landmarks[matches[m].trainIdx].count++;
    _landmarks[matches[m].trainIdx].positions.push_back(newLandmarks[matches[m].queryIdx].positions[0]);
  }
  print(t << "/" << matches.size());
  // Add new landmarks
  std::vector<int> notFound;
  std::remove_copy_if(allIds.begin(), allIds.end(), std::back_inserter(notFound),
     [&found](const int& arg)
     { return (std::find(found.begin(), found.end(), arg) != found.end());});


  Landmarks landmarksToAdd;
  for(auto el : notFound)
  {
    _landmarks.push_back(newLandmarks[el]);
    vconcat(newLandmarks[el].descriptor, _descriptors, _descriptors);
  }
  print("Frame " << newLandmarks[0].framesPresent[0] << ": " <<  found.size() << "/" << newLandmarks.size() << "/" << _landmarks.size() << "(+" << notFound.size() << ")");

  return notFound;
}

void LandmarksManager::createNewLandmarks(int frameID, FrameData& frame,  Landmarks& newLandmarks)
{
  for(int i = 0; i < frame.keyPoints.size(); i++)
  {
    Landmark tempLandMark;
    tempLandMark.framesPresent.push_back(frameID);
    tempLandMark.positions.push_back(frame.keyPoints[i].pt);
    frame.descriptors.row(i).copyTo(tempLandMark.descriptor);
    newLandmarks.push_back(tempLandMark);
  }
}

void LandmarksManager::computeDescriptors(Landmarks& landmarksToCompute, Mat& descriptors)
{
  int size = landmarksToCompute.size();
  for(int i = 0; i < size;i ++)
  {
    if (descriptors.size().width == 0)
    {
        descriptors = landmarksToCompute[i].descriptor.clone();
    }
    else
    {
      vconcat(landmarksToCompute[i].descriptor, descriptors, descriptors);
    }
  }
}
