#ifndef PUB_HPP
#define PUB_HPP

#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/compressed_image.hpp"
#include "cv_bridge/cv_bridge.h"
#include "opencv2/opencv.hpp"

class CameraPublisher : public rclcpp::Node {
public:
    CameraPublisher();

private:
    void publish_image();
    
    // GStreamer pipeline for TurtleBot3 CSI camera
    std::string src_ = "v4l2src device=/dev/video0 ! video/x-raw,width=640,height=480,framerate=30/1 ! videoconvert ! video/x-raw,format=BGR ! appsink";
    
    rclcpp::Publisher<sensor_msgs::msg::CompressedImage>::SharedPtr publisher_;
    rclcpp::TimerBase::SharedPtr timer_;
    cv::VideoCapture cap_;
    cv::Mat frame_;
    std_msgs::msg::Header header_;
};

#endif // PUB_HPP