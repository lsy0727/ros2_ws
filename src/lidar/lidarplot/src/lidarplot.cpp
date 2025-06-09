#include "/home/linux/ros2_ws/src/lidarplot/include/lidarplot/lidar.hpp"
 
cv::Mat lidar::lidar_img(500, 500, CV_8UC3, cv::Scalar(255,255,255));
cv::VideoWriter lidar::output("lidar.mp4", cv::VideoWriter::fourcc('m', 'p', '4', 'v'), 6.5, cv::Size(500, 500));
//fps: 6 ($ ros2 topic hz <토픽명> (/scan))
 
void lidar::scanCb(sensor_msgs::msg::LaserScan::SharedPtr scan) {
    int count = scan->scan_time / scan->time_increment;
    
    printf("[SLLIDAR INFO]: I heard a laser scan %s[%d]:\n", scan->header.frame_id.c_str(), count);
    printf("[SLLIDAR INFO]: angle_range : [%f, %f]\n", RAD2DEG(scan->angle_min), RAD2DEG(scan->angle_max));
    for (int i = 0; i < count; i++) {
        float degree = RAD2DEG(scan->angle_min + scan->angle_increment * i); //RAD2DEG(x) (x * 180./M_PI)
        float distance = scan->ranges[i];
        printf("[SLLIDAR INFO]: angle-distance : [%f, %f]\n", degree, distance);
        

        float rad = DEG2RAD(degree); //DEG2RAD(x) (x * M_PI/180.)
        int xpixel = 250 + (sin(rad) * distance*50);
        int ypixel = 250 + (cos(rad) * distance*50);
        cv::rectangle(lidar_img, cv::Rect(xpixel, ypixel, 3, 3), cv::Scalar(0,0,255), -1); // lidar 기준 (x축: 세로방향, y축: 가로방향)
    }
    // 스캔영상 화면출력 및 동영상 저장
    cv::rectangle(lidar_img, cv::Rect(lidar_img.cols/2 - 1, lidar_img.rows/2 - 1, 5, 5), cv::Scalar(0,0,0), -1);
    output << lidar_img;
    cv::imshow("lidar", lidar_img);
    cv::waitKey(1);
 
    //화면 초기화
    lidar_img = cv::Scalar(255,255,255);
}
 
lidar::lidar() : Node("sllidar_client")
{
    lidar_info_sub = this->create_subscription<sensor_msgs::msg::LaserScan>("scan", 
        rclcpp::SensorDataQoS(), scanCb); //std::bind(&lidar::scanCb, this, _1) -> scanCb
}


int main(int argc, char **argv) {
  rclcpp::init(argc, argv);
  auto node = std::make_shared<lidar>();
  rclcpp::spin(node);
  rclcpp::shutdown();
  return 0;
}