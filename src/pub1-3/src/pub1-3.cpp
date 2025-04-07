#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include <memory>
#include <chrono>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

bool kbhit(void)    // 키보드 입력을 확인하기 위한 함수
{
    struct termios oldt, newt;
    int ch;
    int oldf;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);
    if (ch != EOF)
    {
        ungetc(ch, stdin);
        return true;
    }
    return false;
}

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<rclcpp::Node>("node_pub1");
    auto qos_profile = rclcpp::QoS(rclcpp::KeepLast(10));
    auto mypub = node->create_publisher<geometry_msgs::msg::Twist>("turtle1/cmd_vel", qos_profile);
    geometry_msgs::msg::Twist message;

    rclcpp::WallRate loop_rate(10.0); //반복주파수를 저장하는 객체(단위 Hz)
    while(rclcpp::ok())
    {
        if (kbhit())
        {
            int c = getchar();
            switch(c)
            {
                case 'f':
                    message.linear.x = 2.0;
                    message.angular.z = 0.0;
                    break;
                case 'b':
                    message.linear.x = -2.0;
                    message.angular.z = 0.0;
                    break;
                case 'l':
                    message.linear.x = 0.0;
                    message.angular.z = 2.0;
                    break;
                case 'r':
                    message.linear.x = 0.0;
                    message.angular.z = -2.0;
                    break;
                default:
                    message.linear.x = 0.0;
                    message.angular.z = 0.0;
                    break;
            }
            RCLCPP_INFO(node->get_logger(),
                "\nlinear:\n\tx: %.3f\n\ty: %.3f\n\tz: %.3f\nangular:\n\tx: %.3f\n\ty: %.3f\n\tz: %.3f\n---",
                message.linear.x, message.linear.y, message.linear.z, message.angular.x, message.angular.y, message.angular.z);
            mypub->publish(message);
        }
        //rclcpp::spin_some(node);
        loop_rate.sleep(); //반복주파수에서 남은 시간 만큼 sleep
    }
    rclcpp::shutdown();
    return 0;
}