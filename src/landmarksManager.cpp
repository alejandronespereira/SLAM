#include "landmarksManager.hpp"

LandmarksManager::LandmarksManager(Ptr<DescriptorMatcher> matcher) : _matcher(matcher)
{

}
LandmarksManager::LandmarksManager()
{
}

std::vector<int> LandmarksManager::compareLandmarks(landmarks& newLandmarks, std::vector<int>& found)
{
  if(_landmarks.size() == 0)
  {
    _landmarks = newLandmarks;
    computeDescriptors(newLandmarks,_descriptors);
    std::vector<int> v(newLandmarks.size());
    std::iota ( std::begin(v),std::end(v),0);
    return v;
  }

  Mat newDescriptors;
  computeDescriptors(newLandmarks,newDescriptors);
  std::vector<DMatch> matches;

  _matcher->match(newDescriptors,_descriptors, matches);

  // Update landmarks
  for(int m = 0; m < matches.size(); m++)
  {
    found.push_back(matches[m].queryIdx);
    // newlandmark[m.queryIdx] goes with landmarks[m.trainIdx]
    _landmarks[matches[m].trainIdx].framesPresent.push_back(newLandmarks[matches[m].queryIdx].framesPresent[0]);
    _landmarks[matches[m].trainIdx].count++;
    _landmarks[matches[m].trainIdx].positions.push_back(newLandmarks[matches[m].queryIdx].positions[0]);
  }
  print(found.size() << "/" << _landmarks.size());
  // Add new landmarks
  std::vector<int> notFound;
  std::remove_copy_if(found.begin(), found.end(), std::back_inserter(notFound),
     [&found](const int& arg)
     { return (std::find(found.begin(), found.end(), arg) != found.end());});
  landmarks landmarksToAdd;
  for(auto el : notFound)
  {
    print("Adding a landmark???");
    _landmarks.push_back(newLandmarks[el]);
    vconcat(newLandmarks[el].descriptor, _descriptors, _descriptors);
  }

  return notFound;
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
}

void LandmarksManager::computeDescriptors(landmarks& landmarksToCompute, Mat& descriptors)
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
