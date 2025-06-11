# ros2_ws

## 패키지 생성

$ cd ~/ros2_ws/src

$ ros2 pkg create <패키지명> --build-type ament_cmake --dependencies rclcpp geometry_msgs

## build (패키지 빌드)

$ cd ~/ros2_ws/

$ colcon build --symlink-install --packages-select <패키지명>


## 설정 적용 (경로 업데이트)

$ source install/local_setup.bash


## 실행 (경로 설정이 되어있어 아무데서나 가능)

$ ros2 run <패키지명> <실행파일명>


## 각종 정보

$ ros2 topic echo /<토픽이름>

$ ros2 topic hz /<토픽이름>

$ ros2 topic bw /<토픽이름>



## 실행파일

ros2_ws/install/<패키지 이름>/lib/<프로젝트 이름>/

