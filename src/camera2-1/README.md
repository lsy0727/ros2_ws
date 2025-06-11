# camera2-1

pub : jetson

sub : wsl

1) 수신한 영상을 그레이 -> 이진 영상으로 변환

2) 3가지 영상 모두 출력

## 빌드
```
cd ros2_ws
colcon build --symlink-install --packages-select camera2-1
. ros2_ws/install/local_setup.bash
```

## 실행
```
# jetson터미널
ros2 run camera2-1 pub
# wsl터미널
ros2 run camera2-1 sub_wsl
```

## ros2 명령어

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
