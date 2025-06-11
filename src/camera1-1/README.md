# camera1-1

### build & 설정적용

colcon build --symlink-install --packages-select camera1-1

source ~/ros2_ws/install/local_setup.bash

### 실행

- jetson

ros2 run camera1-1 pub

ros2 run camera1-1 sub_jetson


#  코드설명

- 이진화

https://github.com/lsy0727/ros2_ws/blob/e9cf40981740e87b71b4b84b4aabbb8f2ece4542/src/camera1-1/src/sub_jetson.cpp#L20-L22
