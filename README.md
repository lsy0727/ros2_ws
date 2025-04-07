# ros2_ws

### build (패키지 빌드)

$ cd ~/ros2_ws/

$ colcon build --symlink-install --packages-select pub1-1

$ colcon build --symlink-install --packages-select pub1-2

$ colcon build --symlink-install --packages-select pub1-3

### 설정 적용 (경로 업데이트)

$ source install/local_setup.bash


### 실행 (경로 설정이 되어있어 아무데서나 가능)

$ ros2 run pub1-3 pub1-1

$ ros2 run pub1-3 pub1-2

$ ros2 run pub1-3 pub1-3
