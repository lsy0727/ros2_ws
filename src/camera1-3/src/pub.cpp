#include "camera1-3/pub.hpp"
#include <chrono>

CameraPublisher::CameraPublisher() : Node("campub"), cap_(src_, cv::CAP_GSTREAMER) {
    auto qos_profile = rclcpp::QoS(rclcpp::KeepLast(10)).best_effort();
    publisher_ = create_publisher<sensor_msgs::msg::CompressedImage>("image/compressed", qos_profile);
    
    if (!cap_.isOpened()) {
        RCLCPP_ERROR(get_logger(), "Could not open video! Check if /dev/video0 exists and GStreamer plugins are installed.");
        rclcpp::shutdown();
        return;
    }
    
    // Create timer to publish at 40 Hz
    timer_ = create_wall_timer(
        std::chrono::milliseconds(25),
        std::bind(&CameraPublisher::publish_image, this)
    );
}

void CameraPublisher::publish_image() {
    cap_ >> frame_;
    if (frame_.empty()) {
        RCLCPP_ERROR(get_logger(), "Frame empty!");
        return;
    }
    
    auto msg = cv_bridge::CvImage(header_, "bgr8", frame_).toCompressedImageMsg();
    publisher_->publish(*msg);
    RCLCPP_INFO(get_logger(), "Published image: %dx%d", frame_.cols, frame_.rows);
}