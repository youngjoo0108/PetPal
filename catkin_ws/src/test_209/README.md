# Week1

## Odometry

_Node Name : odom_node.py_

- IMU 센서를 활용해 처음 offset 설정
- linear_x / angular_z 값으로 터틀봇의 위치 계산

## Path

_Node Name : path_tracking.py_

- publish 된 local_path 데이터를 subscribe하여 경로 추종
- 현재 위치와 경로 간의 오차를 계산하여 전방 주시 거리 설정 후 이동

_Node Name : a_star.py_

- A star 알고리즘을 사용하여 현지 위치부터 목적지까지의 최적 경로 생성
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

## Patch

- Map : 집 종류마다 다른 좌표값을 가지기 떄문에 Map Scale 밖을 벗어나는 문제 발생

  - 현재 터틀봇의 좌표값을 중심으로 Map 전개하도록 변경
  - Map Scale [350,350]에서 [700,700]으로 증가시켜 해결

- Path : a_star에서 최적 경로를 생성할 때, 장매물과 너무 인접한 경로 생성 문제

  - 벽 근처의 [5,5] 그리드에 가중치를 두어 해결

---
