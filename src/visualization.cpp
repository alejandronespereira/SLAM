#include "visualization.hpp"

Visualization::Visualization(std::string windowName, Eigen::Matrix3f K)
{
  viz::Viz3d myWindow(windowName);
  for(int i = 0; i < 3; i ++)
  {
    for(int j = 0; j < 3; j ++)
    {
      _K(i,j) = K(i,j);
    }
  }

  /// Let's assume camera has the following properties
  Point3f cam_pos(3.0f,3.0f,3.0f);
  Point3f cam_focal_point(3.0f,3.0f,2.0f);
  Point3f cam_y_dir(-1.0f,0.0f,0.0f);
  /// We can get the pose of the cam using makeCameraPose
  Affine3f cam_pose = viz::makeCameraPose(cam_pos, cam_focal_point, cam_y_dir);

  viz::WCameraPosition* camera = new viz::WCameraPosition(_K,1.0,viz::Color::white());
  myWindow.showWidget("Coordinate Widget", viz::WCoordinateSystem(), cam_pose);
  myWindow.showWidget("Coordinate Widget", camera, cam_pose);
  myWindow.spin();
}
