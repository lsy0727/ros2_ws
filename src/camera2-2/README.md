# camera2-2

pub : jetson

sub : wsl

1) 수신한 영상을 화면에 출력

2) 송신 종료 시 동영상파일로 저장

### 패키지 설치
```
cd ~/ros2_ws/src
git clone https://github.com/2sungryul/camera.git
```

### 빌드
```
cd ~/ros2_ws
colcon build --symlink-install --packages-select camera2-1
. ros2_ws/install/local_setup.bash
```

### 실행
```
# jetson터미널
ros2 run camera2-1 pub
# wsl터미널
ros2 run camera2-1 sub_wsl
```

### 실행결과 (유튜브, mp4업로드)

### ros2 명령어

- 토픽 확인
```
# 패키지 목록
ros2 pkg list
# 실행중인 노드 목록
ros2 node list
# 토픽 리스트 출력 ( -t 옵션 : 메시지 타입 출력)
ros2 topic list -t
# 전송되는 토픽 값
ros2 topic echo /image/compressed
# 토픽 주기
ros2 topic hz /image/compressed
# 토픽 메시지 크기
ros2 topic bw /image/compressed
# 토픽 정보 (DDS 통신시 QoS 설정을 확인하는 명령어, pub과 sub의 설정이 동일해야함)
ros2 topic info /image/compressed -v
```
