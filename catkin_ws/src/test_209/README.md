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
- 이에 대한 dijkstra 와의 효율 차이는 추후 실험을 통해 작성 예정

## Follow

_Node Name : pure_pursuit.py_

- 기존의 carrot follow 알고리즘은 바로 앞의 경로 방향 그대로 steering 값을 조절하여 비틀 거리는 문제점 발생
- pure pursuit 제어 알고리즘을 통해 유연한 로봇 이동을 구현

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
