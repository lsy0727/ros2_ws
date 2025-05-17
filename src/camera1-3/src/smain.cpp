#include "camera1-3/sub.hpp"
#include <memory>

int main(int argc, char * argv[]) {
    rclcpp::init(argc, argv);
    // Use command line argument to determine WSL display mode
    bool use_wsl_display = (argc > 1 && std::string(argv[1]) == "--wsl");
    auto node = std::make_shared<CameraSubscriber>(use_wsl_display);
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}