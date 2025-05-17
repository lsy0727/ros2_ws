# camera1-1

### build & 설정적용

colcon build --symlink-install --packages-select camera1-1

source ~/ros2_ws/install/local_setup.bash

### 실행

- jetson

ros2 run camera1-1 sub

ros2 run camera1-1 sub_jetson

- windows

gst-launch-1.0 -v udpsrc port=8001 ! ‘application/x-rtp,encodingname=(string)H264,payload=(int)96’ ! rtph264depay ! queue ! avdec_h264 ! videoconvert ! autovideosink
