#include <pcl_pipeline.hpp>

#include <pcl/filters/crop_box.h>

namespace pcl_pipeline
{

std::vector<PCLPipeline::Detection>
PCLPipeline::process(const CloudConstPtr & input_cloud)
{
  auto cloud = crop(input_cloud);

  return {};
}

PCLPipeline::CloudPtr
PCLPipeline::crop(const CloudConstPtr & input_cloud)
{
  auto output_cloud = std::make_shared<CloudT>();

  pcl::CropBox<PointT> crop_box;
  crop_box.setInputCloud(input_cloud);
  crop_box.setMin(config_.crop_min);
  crop_box.setMax(config_.crop_max);
  crop_box.filter(*output_cloud);

  return output_cloud;
}
}
