#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include <memory>
#include <chrono>
#include <functional>
//#include <string>
using namespace std::chrono_literals;
void callback(rclcpp::Node::SharedPtr node,
rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr pub)
{
    auto message = geometry_msgs::msg::Twist();
    message.linear.x = 1.0;
    message.angular.z = 1.0;
    RCLCPP_INFO(node->get_logger(),
        "\nlinear:\n\tx: %.1f\n\ty: %.1f\n\tz: %.1f\nangular:\n\tx: %.1f\n\ty: %.1f\n\tz: %.1f\n---",
        message.linear.x, message.linear.y, message.linear.z, message.angular.x, message.angular.y, message.angular.z);
    pub->publish(message);
}
int main(int argc, char* argv[])
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<rclcpp::Node>("turtlesim");
    auto qos_profile = rclcpp::QoS(rclcpp::KeepLast(10));
    auto pub = node->create_publisher<geometry_msgs::msg::Twist>("turtle1/cmd_vel", qos_profile);
    std::function<void()> fn = std::bind(callback, node, pub);
    auto timer = node->create_wall_timer(100ms, fn);
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}