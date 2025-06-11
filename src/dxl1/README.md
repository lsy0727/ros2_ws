# dxl1

## 빌드
```
cd ros2_ws/
colcon build --symlink-install --packages-select dxl_wsl
. ros2_ws/install/local_setup.bash
```

## 실행

- jetson
```
ros2 run dxl_wsl sub
```

- wsl
```
ros2 run dxl_wsl pub_wsl
```

## 패키지 빌드 전 확인

- dynamixel을 제어하려면 U2D2를 인식할 수 있도록 설정을 변경해야함

![image](https://github.com/user-attachments/assets/9adac14b-bb45-4714-95ad-3b283459d9f4)

-----

- U2D2에 대한 권한 부여

![image](https://github.com/user-attachments/assets/8803ae76-f058-489c-a837-b27d8a6e1316)
