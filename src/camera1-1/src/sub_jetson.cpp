#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/compressed_image.hpp"
#include "opencv2/opencv.hpp"
#include <memory>
#include <functional>
#include <iostream>
using std::placeholders::_1;
using namespace cv;

// Windows로 H.264 스트리밍 (테스트 명령어 기반)
std::string dst = "appsrc ! videoconvert ! video/x-raw, format=BGRx ! \
	nvvidconv ! nvv4l2h264enc insert-sps-pps=true ! \
	h264parse ! rtph264pay pt=96 ! \
	udpsink host = 203.234.58.121 port = 8001 sync=false";

cv::VideoWriter writer;

void mysub_callback(rclcpp::Node::SharedPtr node, const sensor_msgs::msg::CompressedImage::SharedPtr msg)
{
    cv::Mat frame = cv::imdecode(cv::Mat(msg->data), cv::IMREAD_COLOR);
    if (frame.empty()) {
        RCLCPP_ERROR(node->get_logger(), "Failed to decode image!");
        return;
    }
    
    Mat gray, thresh;
    cvtColor(frame, gray, COLOR_BGR2GRAY);
    threshold(gray, thresh, 0, 255, THRESH_BINARY | THRESH_OTSU);
    writer << thresh;
    RCLCPP_INFO(node->get_logger(), "Received Image: %s, %d, %d", msg->format.c_str(), frame.rows, frame.cols);
}

int main(int argc, char* argv[])
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<rclcpp::Node>("camsub");

    writer.open(dst, 0, (double)30, cv::Size(640, 480), false);
    if (!writer.isOpened()) {
        RCLCPP_ERROR(node->get_logger(), "Writer open failed! Check GStreamer plugins: x264enc, rtph264pay.");
        rclcpp::shutdown();
        return -1;
    }
    auto qos_profile = rclcpp::QoS(rclcpp::KeepLast(10)).best_effort();
    std::function<void(const sensor_msgs::msg::CompressedImage::SharedPtr msg)> fn;
    fn = std::bind(mysub_callback, node, _1);
    auto mysub = node->create_subscription<sensor_msgs::msg::CompressedImage>("image/compressed", qos_profile, fn);
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
