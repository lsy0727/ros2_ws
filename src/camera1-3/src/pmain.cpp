#include "camera1-3/pub.hpp"
#include <memory>

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<CameraPublisher>();
    rclcpp::spin(node);
    
    rclcpp::shutdown();
    return 0;
}