# camera1-3

### build & 설정적용

colcon build --symlink-install --packages-select camera1-3

source ~/ros2_ws/install/local_setup.bash

### 실행

- jetson

ros2 run camera1-3 sub

ros2 run camera1-3 sub

- windows

gst-launch-1.0 -v udpsrc port=9007 ! ‘application/x-rtp,encodingname=(string)H264,payload=(int)96’ ! rtph264depay ! queue ! avdec_h264 ! videoconvert ! autovideosink
