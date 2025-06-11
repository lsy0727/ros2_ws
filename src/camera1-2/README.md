# camera1-2

pub : jetson

sub : jetson

-----

1) pub이 송신한 영상을 sub이 수신

2) 수신한 영상을 PC로 전송

3) ctrl+c 입력 시 현재까지 수신한 동영상 파일 저장

### build & 설정적용
```
colcon build --symlink-install --packages-select camera1-2
source ~/ros2_ws/install/local_setup.bash
```
### 실행

- jetson
```
# 터미널1
ros2 run camera1-2 sub
# 터미널2
ros2 run camera1-2 sub_jetson
```
- windows
```
gst-launch-1.0 -v udpsrc port=9007 ! ‘application/x-rtp,encodingname=(string)H264,payload=(int)96’ ! rtph264depay ! queue ! avdec_h264 ! videoconvert ! autovideosink
```
