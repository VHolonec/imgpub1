#include "cv_bridge/cv_bridge.h"
#include "opencv2/core/mat.hpp"
#include "opencv2/imgcodecs.hpp"
#include "rclcpp/rclcpp.hpp"
#include "rclcpp/publisher.hpp"
#include <vector>
#include <string>

int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);
  rclcpp::NodeOptions options;
  rclcpp::Node::SharedPtr node = rclcpp::Node::make_shared("image_publisher", options);

  rclcpp::Publisher<sensor_msgs::msg::Image>::SharedPtr  pub = node->create_publisher<sensor_msgs::msg::Image>("topic_image", 10);

  std::vector<sensor_msgs::msg::Image::SharedPtr> ubuntu_img;

  for(int i=1;i<=8;i++)
  {
    std::string folder(argv[1]);
    cv::Mat image = cv::imread(folder + "/" + std::to_string(i)+".jpg", cv::IMREAD_COLOR);
    std_msgs::msg::Header hdr;
    sensor_msgs::msg::Image::SharedPtr msg = cv_bridge::CvImage(hdr, "bgr8", image).toImageMsg();
    ubuntu_img.push_back(msg);
  }

  rclcpp::WallRate loop_rate(55);

  while (rclcpp::ok()) {
    for(int i=0;i<8;i++){
      pub->publish(*ubuntu_img.at(i).get());
      rclcpp::spin_some(node);
      //loop_rate.sleep();
    }
  }
  return 0;
}

