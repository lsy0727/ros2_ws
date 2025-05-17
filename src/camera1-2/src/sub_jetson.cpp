#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/compressed_image.hpp"
#include "opencv2/opencv.hpp"
#include <memory>
#include <functional>
#include <iostream>
using std::placeholders::_1;

// Windows로 H.264 스트리밍 (테스트 명령어 기반)
std::string dst = "appsrc ! videoconvert ! video/x-raw,format=I420 ! queue ! x264enc tune=zerolatency bitrate=500 ! rtph264pay pt=96 ! udpsink host=192.168.0.61 port=8001 sync=false";

cv::VideoWriter writer, outputVideo;    //writer : 스트리밍용, outputVideo : 저장용용
volatile sig_atomic_t running = 1;

void keyboard_handler(int signum)
{
    (void)signum;
    running = 0;
    std::cout << "video save success" << std::endl;
}

void mysub_callback(rclcpp::Node::SharedPtr node, const sensor_msgs::msg::CompressedImage::SharedPtr msg)
{
    cv::Mat frame = cv::imdecode(cv::Mat(msg->data), cv::IMREAD_COLOR);
    if (frame.empty()) {
        RCLCPP_ERROR(node->get_logger(), "Failed to decode image!");
        return;
    }
    
    cv::Mat gray, thresh;
    cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);
    cv::threshold(gray, thresh, 0, 255, cv::THRESH_BINARY | cv::THRESH_OTSU);

    writer << thresh;
    outputVideo << thresh;
    RCLCPP_INFO(node->get_logger(), "Received Image: %s, %d, %d", msg->format.c_str(), frame.rows, frame.cols);
}

int main(int argc, char* argv[])
{
    signal(SIGINT, keyboard_handler);  // SIGINT 시그널 핸들러

    rclcpp::init(argc, argv);
    auto node = std::make_shared<rclcpp::Node>("camsub");

    writer.open(dst, 0, (double)30, cv::Size(640, 480), false);
    if (!writer.isOpened()) {
        RCLCPP_ERROR(node->get_logger(), "Writer open failed! Check GStreamer plugins: x264enc, rtph264pay.");
        rclcpp::shutdown();
        return -1;
    }

    // 영상 저장
    int fourcc = cv::VideoWriter::fourcc('m', 'p', '4', 'v');
    float fps = 30;
    outputVideo.open("output_video.mp4", fourcc, fps, cv::Size(640, 480), false);

    auto qos_profile = rclcpp::QoS(rclcpp::KeepLast(10)).best_effort();
    std::function<void(const sensor_msgs::msg::CompressedImage::SharedPtr msg)> fn;
    fn = std::bind(mysub_callback, node, _1);
    auto mysub = node->create_subscription<sensor_msgs::msg::CompressedImage>("image/compressed", qos_profile, fn);

    while (rclcpp::ok() && running) {
        rclcpp::spin(node);
    }
    writer.release();
    outputVideo.release();
    rclcpp::shutdown();
    return 0;
}