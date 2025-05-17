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
    std::string dst_ = "appsrc ! videoconvert ! video/x-raw,format=I420 ! queue ! x264enc tune=zerolatency bitrate=500 ! rtph264pay pt=96 ! udpsink host=192.168.0.61 port=8001 sync=false";
    
    rclcpp::Subscription<sensor_msgs::msg::CompressedImage>::SharedPtr subscription_;
    cv::VideoWriter writer_;
    bool use_wsl_display_;
};

#endif // SUB_HPP