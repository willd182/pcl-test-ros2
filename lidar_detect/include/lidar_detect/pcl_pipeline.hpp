#pragma once

#include <vector>

#include <Eigen/Core>
#include <Eigen/Geometry>

#include <pcl/point_cloud.h>
#include <pcl/point_types.h>

namespace pcl_pipeline
{

class PCLPipeline
{
public:
  using PointT = pcl::PointXYZ;
  using CloudT = pcl::PointCloud<PointT>;
  using CloudPtr = CloudT::Ptr;
  using CloudConstPtr = CloudT::ConstPtr;

  struct Config
  {
    Eigen::Vector4f crop_min{0.0f, -30.0f, -2.0f, 1.0f};
    Eigen::Vector4f crop_max{30.0f, 30.0f, 5.0f, 1.0f};
  };

  struct Detection
  {
    Eigen::Vector3f position;
    Eigen::Quaternionf orientation;
    Eigen::Vector3f size;
  };

  std::vector<Detection> process(const CloudConstPtr & input_cloud);

private:
  Config config_;
  CloudPtr crop(const CloudConstPtr & input_cloud);
};
} // namespace pcl_pipeline
