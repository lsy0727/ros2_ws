# camera1-1

pub : jetson

sub : jetson

-----

1) pub에서 송신한 영상을 sub에서 수신

2) 컬러 영상 -> 그레이 영상 -> 이진 영상으로 변환

3) 이진영상을 PC로 전송하여 출력

### 패키지 설치
```
cd ~/ros2_ws/src
git clone https://github.com/2sungryul/camera.git
```

### build & 설정적용
```
cd ~/ros2_ws
colcon build --symlink-install --packages-select camera1-1
source ~/ros2_ws/install/local_setup.bash
```

### 실행

- jetson
```
# 터미널1
ros2 run camera1-1 pub
# 터미널2
ros2 run camera1-1 sub_jetson
```
- windows
```
gst-launch-1.0 -v udpsrc port=8001 ! ‘application/x-rtp,encodingname=(string)H264,payload=(int)96’ ! rtph264depay ! queue ! avdec_h264 ! videoconvert ! autovideosink
```

### 실행결과 (유튜브 업로드)




#  코드설명

- 이진화

https://github.com/lsy0727/ros2_ws/blob/e9cf40981740e87b71b4b84b4aabbb8f2ece4542/src/camera1-1/src/sub_jetson.cpp#L20-L22
