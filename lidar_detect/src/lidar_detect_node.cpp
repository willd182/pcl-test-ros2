#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/point_cloud2.hpp"

#include <pcl_conversions/pcl_conversions.h>
#include "lidar_detect/pcl_pipeline.hpp"

class PCLNode : public rclcpp::Node
{
public:
  PCLNode()
  : rclcpp::Node("pcl_node")
  {
    subscription_ = create_subscription<sensor_msgs::msg::PointCloud2>(
                "/points",
                rclcpp::SensorDataQoS(),
                std::bind(
                        &PCLNode::pointcloud_callback,
                        this,
                        std::placeholders::_1)
    );
  }

private:
  void pointcloud_callback(const sensor_msgs::msg::PointCloud2::SharedPtr msg)
  {
    auto cloud = std::make_shared<pcl_pipeline::PCLPipeline::CloudT>();

    pcl::fromROSMsg(*msg, *cloud);

    auto detections = pipeline_.process(cloud);

    RCLCPP_INFO(
                get_logger(),
                "Received %zu detections",
                detections.size()
    );
  }

  pcl_pipeline::PCLPipeline pipeline_;

  rclcpp::Subscription<sensor_msgs::msg::PointCloud2>::SharedPtr
    subscription_;

};


int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);

  auto node = std::make_shared<PCLNode>();

  rclcpp::spin(node);

  rclcpp::shutdown();

  return 0;
}