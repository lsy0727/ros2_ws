#include "camera1-3/sub.hpp"
#include <functional>

CameraSubscriber::CameraSubscriber(bool use_wsl_display) 
    : Node(use_wsl_display ? "camsub_wsl" : "camsub"), 
      use_wsl_display_(use_wsl_display) {
    auto qos_profile = rclcpp::QoS(rclcpp::KeepLast(10)).best_effort();
    subscription_ = create_subscription<sensor_msgs::msg::CompressedImage>(
        "image/compressed", 
        qos_profile,
        std::bind(&CameraSubscriber::image_callback, this, std::placeholders::_1)
    );
    
    if (!use_wsl_display_) {
        writer_.open(dst_, 0, 30.0, cv::Size(640, 480), false);
        if (!writer_.isOpened()) {
            RCLCPP_ERROR(get_logger(), "Writer open failed! Check GStreamer plugins: x264enc, rtph264pay.");
            rclcpp::shutdown();
        }
    }
}

void CameraSubscriber::image_callback(const sensor_msgs::msg::CompressedImage::SharedPtr msg) {
    cv::Mat frame = cv::imdecode(cv::Mat(msg->data), cv::IMREAD_COLOR);
    if (frame.empty()) {
        RCLCPP_ERROR(get_logger(), "Failed to decode image!");
        return;
    }
    
    if (use_wsl_display_) {
        cv::imshow("wsl", frame);
        cv::waitKey(1);
    } else {
        cv::Mat gray, thresh;
        cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);
        cv::threshold(gray, thresh, 0, 255, cv::THRESH_BINARY | cv::THRESH_OTSU);
        writer_ << thresh;
    }
    
    RCLCPP_INFO(get_logger(), "Received Image: %s, %d, %d", 
                msg->format.c_str(), frame.rows, frame.cols);
}