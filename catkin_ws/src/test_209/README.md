# Week1

## Odometry

_Node Name : odom_node.py_

- IMU 센서를 활용해 처음 offset 설정
- linear_x / angular_z 값으로 터틀봇의 위치 계산

## Path

_Node Name : path_tracking.py_

- publish 된 local_path 데이터를 subscribe하여 경로 추종
- 현재 위치와 경로 간의 오차를 계산하여 전방 주시 거리 설정 후 이동

_Node Name : dijkstra.py_

- dijkstra 알고리즘을 사용하여 현지 위치부터 목적지까지의 최적 경로 생성
- global_path로 데이터를 publish

_Node Name : a_star_local.py_

- global_path &rarr; local_path

## Map

_Node Name : make_map.py_

- SLAM(Simultaneous Localization And Mapping) 기술 사용
- lidar의 Laser Scan 데이터를 활용하여 실시간으로 mapping과 위치 추정
- Map 데이터로 publish
- 노드 종료시 map.txt로 맵 데이터 저장

_Node Name : load_map.py_

- 저장된 map.txt를 불러와서 Map 데이터로 publish

---

# Week2

## Map Setting

_Node Name : map_setting.py_

- Frontier 기반 탐색 사용
- 가장 근접한 미탐색 지역 계산 후 목적지 publish

## Path

_Node Name : a_star.py_

- A\* 알고리즘을 사용하여 현지 위치부터 목적지까지의 최적 경로 생성
- heuristic 함수는 8방향을 고려한 cost 값 계산을 통해 설정
- 이에 대한 dijkstra 와의 효율 차이 (A* 알고리즘이 30 ~ 50% 정도의 시간 효율성을 갖는다)

|            |        1         |        2         |        3         |        4         |         5        |         6        |
|------------|------------------|------------------|------------------|------------------|------------------|------------------|
|            |![1](https://lab.ssafy.com/s10-mobility-smarthome-sub2/S10P22A209/-/raw/da7d64e7641677ca47469144c8be156eeb19bedf/catkin_ws/src/test_209/test_209/image/image.png)|![2](https://lab.ssafy.com/s10-mobility-smarthome-sub2/S10P22A209/-/raw/da7d64e7641677ca47469144c8be156eeb19bedf/catkin_ws/src/test_209/test_209/image/image-2.png)|![3](https://lab.ssafy.com/s10-mobility-smarthome-sub2/S10P22A209/-/raw/da7d64e7641677ca47469144c8be156eeb19bedf/catkin_ws/src/test_209/test_209/image/image-4.png)|![4](https://lab.ssafy.com/s10-mobility-smarthome-sub2/S10P22A209/-/raw/da7d64e7641677ca47469144c8be156eeb19bedf/catkin_ws/src/test_209/test_209/image/image-6.png)|![5](https://lab.ssafy.com/s10-mobility-smarthome-sub2/S10P22A209/-/raw/da7d64e7641677ca47469144c8be156eeb19bedf/catkin_ws/src/test_209/test_209/image/image-8.png)|![6](https://lab.ssafy.com/s10-mobility-smarthome-sub2/S10P22A209/-/raw/da7d64e7641677ca47469144c8be156eeb19bedf/catkin_ws/src/test_209/test_209/image/image-10.png)|
| Dijkstra(s)   |2.425417423248291 |2.2658658027648926|2.507333755493164 |2.205069065093994 |2.4135243892669678|2.5657551288604736|
| A*(s)         |1.1773033142089844|1.4452247619628906|1.6590280532836914|1.3965215682983398|1.715087652206421 |1.5892083644866943|



## Follow

_Node Name : pure_pursuit.py_

- 기존의 carrot follow 알고리즘은 바로 앞의 경로 방향 그대로 steering 값을 조절하여 비틀 거리는 문제점 발생
- pure pursuit 제어 알고리즘을 통해 유연한 로봇 이동을 구현
- Error
  - 각속도가 커 원하는 반경보다 크게 이동하여 충돌 발생 및 효율적인 주행 구현이 안됨
- Solve
  - 목표 지점의 theta 값이 작을 경우는 직선 주행에 가깝도록 선속도를 높이고 각속도를 theta 값의 1/5로 설정

  - 반대로 theta 값이 클 경우에는 선속도를 줄이고 theta 값을 높여 빠르게 회전하지만 회전반경을 줄여 부드럽고 충돌이 발생하지 않도록 주행 로직을 재구현

## IoT

_Node Name : iot_control.py_

- map1의 iot기기 좌표 정보를 저장 후 index 값과 동작 명령어( ex> (1, 2) = 1번(방1 전등)기기를 off(2) 한다.)를 통해 경로 생성 및 iot 기기 전원 관리

- 터틀봇 상태, 기기 상태 등을 구독하고 명령이 다수 발생하면 순차적으로 수행. 이 과정에서 터틀봇과 기기 상태의 변화에 따라 goal 변경과 경로의 변경 등 다양한 로직을 timer 를 통해 3초 간격으로 수행

## Patch

- Map : 집 종류마다 다른 좌표값을 가지기 떄문에 Map Scale 밖을 벗어나는 문제 발생

  - 현재 터틀봇의 좌표값을 중심으로 Map 전개하도록 변경
  - Map Scale [350,350]에서 [700,700]으로 증가시켜 해결

- Path : a_star에서 최적 경로를 생성할 때, 장매물과 너무 인접한 경로 생성 문제

  - 벽 근처의 [5,5] 그리드에 가중치를 두어 해결

---

# Week3

## Patch

- Map Setting : 예외 발생할 경우 error_type 인지/판단 후 경우를 나누어 제어

  - error 1 : 목적지가 현재 위치와 너무 가깝거나/목적지 계산 에러
    &rarr; 제자리 회전 하면서 lidar 센서 데이터 업데이트 하면서 목적지 다시 계산하여 해결

  - error 2 : 출발 위치가 장애물과 너무 인접하여 구분이 하기 힘든 에러
    &rarr; lidar 데이터로 전진/후진 판단 후 장애물에서 이동하여 해결

  - error 3 : 너무 오랜 시간 한 자리에 머무른 채 상태 변화 X
    &rarr; 초기 시작 지점을 목적지로 설정하여 자리 이동하여 해결

## Tracking
_Node Name : tracking.py_
- 카메라 픽셀 이미지로 강아지의 위치 추정

- 정확한 위치를 파악하여 추후에 장애물 처리 및 회피 로직에 활용할 수 있도록 목표 설정
### 1. 각도 측정
  - 카메라 화면 중앙 아래 부분과 강아지를 나타내는 박스의 중앙점 사이 거리 측정
  - Error
    - Fov 값이 60인데 측정한 값은 대략 90도 정도 범위가 나옴
    - 측정한 각도값의 레이더 정보를 받아 왔을 때, 장애물이 없다고 판단되는 오류 발생
  - Solve
    - 320 * 240 픽셀임을 이용하여 거리 비율을 4: 3으로 맞춰 각도 추정

  - 테스트 결과 화면 양 끝까지의 각도 값이 30, Fov 값이 60임을 고려해 각도 측정에 오차가 거의 없음을 확인

### 2. 거리 측정
  - Error
    - 이미지 상 가로 길이는 강아지의 앞, 옆 부분에 따라 오차가 크게 발생
  - Solve
    - 상대적으로 일정하게 측정되는 높이를 기준으로 측정하기로 결정

  - 시뮬레이터 상의 가로, 세로 길이 측정 값과 카메라에 측정된 값을 비교하여 높이가 대략 1임을 추정

  - 이미지 높이와 각도를 기준으로 실제 높이와의 비율을 측정해 강아지 까지의 거리 측정
  
### 3. 골 지점 설정

- 측정한 각도와 거리, IMU 값(터틀봇의 현재 위치 및 각도)를 통해 강아지 위치 추정

- Error
  
  - 강아지가 벽에 붙어 있는 경우 골 지점이 장애물로 판단 되어 경로 생성을 못하는 경우가 발생
  
  - 가까이 있어 높이가 화면의 일정 부분 이상 차지하면 위치 파악 오류 및 충돌 발생

  - 목표 지점에 도착하거나 멈췄을 때, 카메라 한쪽에 치우쳐 위치하면 이후 이동 했을 때 tracking 에 어려움 발생

- Solve

  - 카메라에 강아지가 찍히는 경우는 강아지까지의 직선거리에 벽이 없다고 판단하여 강아지보다 앞 부분에 골 지점을 설정하여 경로 생성

  - 기존 A* 코드를 사용해 (강아지까지 거리 - 1) 위치를 골 지점으로 해 경로 생성

  - 거리 측정 값이 2.0 이하일때 멈추는 명령을 내려 대략 1.5 앞부분에서 멈추게 함

  - 터틀봇 정지 후 이미지 상 중심 위치가 카메라의 중앙 부분에 위치하도록 터틀봇 각도 제어
  


