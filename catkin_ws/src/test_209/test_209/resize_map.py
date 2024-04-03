import rclpy, requests, json
import numpy as np
from rclpy.node import Node

import os
from geometry_msgs.msg import Pose
from squaternion import Quaternion
from nav_msgs.msg import Odometry,OccupancyGrid,MapMetaData
from math import pi

# load_map 노드는 맵 데이터를 읽어서, 맵 상에서 점유영역(장애물) 근처에 로봇이 움직일 수 없는 영역을 설정하고 맵 데이터로 publish 해주는 노드입니다.
# 추 후 a_star 알고리즘에서 맵 데이터를 subscribe 해서 사용합니다.

# 노드 로직 순서
# 1. 맵 파라미터 설정
# 2. 맵 데이터 읽고, 2차원 행렬로 변환
# 3. 점유영역 근처 필터처리

class resize(Node):

    def __init__(self, map_data):

        self.map_msg = OccupancyGrid()
        self.map_msg = map_data
        self.map_size_x=700 
        self.map_size_y=700
        self.map_resolution=0.05
        # self.map_offset_x = -8 - (self.map_size_x * self.map_resolution) / 2
        # self.map_offset_y = -4 - (self.map_size_y * self.map_resolution) / 2
        
        self.range = [[0, 700], [0, 700]]
        self.homeId = '2'

        grid = np.array(self.map_msg.data)
        grid = np.reshape(grid,(self.map_size_x, self.map_size_y))

        new_grid = self.resize_map(grid)
        self.save_map(new_grid)

    def resize_map(self, grid):
        x_range = [self.map_size_x, 0]
        y_range = [self.map_size_y, 0]

        for i in range(self.map_size_x):
            for j in range(self.map_size_y):
                if grid[i, j] == 0 or grid[i, j] == 100:
                    x_range = [min(x_range[0], i), max(x_range[1], i)]
                    y_range = [min(y_range[0], j), max(y_range[1], j)]
        
        if x_range[0]-5 < 0 or x_range[1]+6 > 700 or y_range[0]-5 < 0 or y_range[1]+6 > 700:
            x_range = [max(x_range[0], 5), min(x_range[1], 694)]
            y_range = [max(y_range[0], 5), min(y_range[1], 694)]

        self.map_size_x = x_range[1] - x_range[0] + 11
        self.map_size_y = y_range[1] - y_range[0] + 11

        self.range = [[x_range[0], x_range[1]], [y_range[0], y_range[1]]]

        return grid[x_range[0]-5:x_range[1]+6, y_range[0]-5:y_range[1]+6]

    def save_map(self, map_data):
        data=''
        data += '{0} {1}\n'.format(self.map_size_x, self.map_size_y)
        for x in range(self.map_size_x):
            for y in range(self.map_size_y):
                data+='{0} '.format(map_data[x][y])

        # for pixel in map_data:
        #     data+='{0} '.format(pixel)

        full_path = 'C:\\Users\\SSAFY\\Desktop\\\S10P22A209\\catkin_ws\\src\\test_209\\map\\new_map.txt'

        url = "https://j10a209.p.ssafy.io/api/v1/maps"
        body = {
            'homeId': self.homeId,
            'data': data,
            'startGrid': {
                'x': self.range[1][0],
                'y': self.range[0][0],
            }
        }
        response = requests.post(url, json=body)
        # print(response)
        data = ''
        data += '{0} {1}\n{2} {3}'.format(self.range[1][0], self.range[0][0], self.range[1][1], self.range[0][1])
        f=open(full_path,'w')
        
        #data += '\n{0} {1}'.format(node.map_msg.info.origin.position.x, node.map_msg.info.origin.position.y)
        f.write(data)
        f.close()

    # def read_txt(self):
    #     full_path = 'C:\\Users\\SSAFY\\Desktop\\\S10P22A209\\catkin_ws\\src\\test_209\\map\\map.txt'
    #     self.f = open(full_path, 'r')
        
    #     lines = self.f.readlines()
    #     line_data = lines[0].split()
    #     offset = lines[1].split()
    #     offset_x, offset_y = float(offset[0]), float(offset[1])
        
    #     for num,data in enumerate(line_data) :
    #         self.map_data[num] = int(data)

    #     self.f.close()

    #     grid = np.array(self.map_data)
    #     grid = np.reshape(grid,(self.map_size_x, self.map_size_y))

    #     new_grid = self.resize_map(grid)
        
    #     np_map_data=new_grid.reshape(1,self.map_size_x*self.map_size_y)
    #     list_map_data=np_map_data.tolist()

    #     ## 로직2를 완성하고 주석을 해제 시켜주세요.

    #     self.map_msg.info.width = self.map_size_y
    #     self.map_msg.info.height = self.map_size_x

    #     self.map_msg.data=list_map_data[0]
    #     self.map_msg.info.origin.position.x = offset_x + (self.range[1][0] - 5)*self.map_resolution
    #     self.map_msg.info.origin.position.y = offset_y + (self.range[0][0] - 5)*self.map_resolution
