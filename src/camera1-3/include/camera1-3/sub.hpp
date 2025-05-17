#ifndef SUB_HPP
#define SUB_HPP

#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/compressed_image.hpp"
#include "opencv2/opencv.hpp"

class CameraSubscriber : public rclcpp::Node {
public:
    CameraSubscriber(bool use_wsl_display = false);

private:
    void image_callback(const sensor_msgs::msg::CompressedImage::SharedPtr msg);
    
    // GStreamer pipeline for H.264 streaming
    std::string dst = "appsrc ! videoconvert ! video/x-raw, format=BGRx ! \
	nvvidconv ! nvv4l2h264enc insert-sps-pps=true ! \
	h264parse ! rtph264pay pt=96 ! \
	udpsink host = 192.168.0.xx port = 9007 sync=false";
    
    rclcpp::Subscription<sensor_msgs::msg::CompressedImage>::SharedPtr subscription_;
    cv::VideoWriter writer_;
    bool use_wsl_display_;
};

#endif // SUB_HPP
