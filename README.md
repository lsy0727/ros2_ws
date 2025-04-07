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


### subscribe

$ ros2 topic echo /<토픽이름>

$ ros2 topic hz /<토픽이름>

$ ros2 topic bw /<토픽이름>



### 소스코드

ros2_ws/src/


### 실행파일

ros2_ws/install/<패키지 이름>/lib/<프로젝트 이름>/

