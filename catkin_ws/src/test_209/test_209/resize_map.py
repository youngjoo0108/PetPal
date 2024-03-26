import rclpy
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

class loadMap(Node):

    def __init__(self):
        super().__init__('load_map')
        self.odom_sub = self.create_subscription(Odometry,'odom',self.odom_callback,1)
        self.map_pub = self.create_publisher(OccupancyGrid, 'map', 1)
        
        self.timer = self.create_timer(1, self.timer_callback)
        self.is_odom = False

        self.map_msg=OccupancyGrid()
        self.map_size_x=700 
        self.map_size_y=700
        self.map_resolution=0.05
        # self.map_offset_x = -8 - (self.map_size_x * self.map_resolution) / 2
        # self.map_offset_y = -4 - (self.map_size_y * self.map_resolution) / 2
        self.map_data = [0 for i in range(self.map_size_x*self.map_size_y)]

        self.map_msg.header.frame_id="map"
        self.range = [[0, 700], [0, 700]]

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

    def save_map(self):
        full_path = 'C:\\Users\\SSAFY\\Desktop\\\S10P22A209\\catkin_ws\\src\\test_209\\map\\new_map.txt'
        f=open(full_path,'w')
        data=''
        data += '{0} {1}\n'.format(self.map_size_x, self.map_size_y)
        for pixel in self.map_msg.data :
            data+='{0} '.format(pixel)
        
        #data += '\n{0} {1}'.format(node.map_msg.info.origin.position.x, node.map_msg.info.origin.position.y)
        f.write(data)
        f.close()

    def read_txt(self):
        full_path = 'C:\\Users\\SSAFY\\Desktop\\\S10P22A209\\catkin_ws\\src\\test_209\\map\\map.txt'
        self.f = open(full_path, 'r')
        
        lines = self.f.readlines()
        line_data = lines[0].split()
        offset = lines[1].split()
        offset_x, offset_y = float(offset[0]), float(offset[1])
        
        for num,data in enumerate(line_data) :
            self.map_data[num] = int(data)

        self.f.close()

        grid = np.array(self.map_data)
        grid = np.reshape(grid,(self.map_size_x, self.map_size_y))

        new_grid = self.resize_map(grid)
        
        np_map_data=new_grid.reshape(1,self.map_size_x*self.map_size_y)
        list_map_data=np_map_data.tolist()

        ## 로직2를 완성하고 주석을 해제 시켜주세요.

        self.map_msg.info.width = self.map_size_y
        self.map_msg.info.height = self.map_size_x

        self.map_msg.data=list_map_data[0]
        self.map_msg.info.origin.position.x = offset_x + (self.range[1][0] - 5)*self.map_resolution
        self.map_msg.info.origin.position.y = offset_y + (self.range[0][0] - 5)*self.map_resolution

    def odom_callback(self, msg):
        if self.is_odom == False:
            self.is_odom = True

            # self.map_offset_x = msg.pose.pose.position.x - (self.map_size_x*self.map_resolution*0.5)
            # self.map_offset_y = msg.pose.pose.position.y - (self.map_size_y*self.map_resolution*0.5)

            m = MapMetaData()
            m.resolution = self.map_resolution
            m.width = self.map_size_x
            m.height = self.map_size_y
            m.origin = Pose()
            # m.origin.position.x = self.map_offset_x
            # m.origin.position.y = self.map_offset_y
            m.origin.position.x = 0.0
            m.origin.position.y = 0.0

            self.map_meta_data = m
            self.map_msg.info=self.map_meta_data

            self.read_txt()
            self.save_map()


    def timer_callback(self):
        if self.is_odom:
            self.map_msg.header.stamp =rclpy.clock.Clock().now().to_msg()
            self.map_pub.publish(self.map_msg)

       
def main(args=None):
    rclpy.init(args=args)

    load_map = loadMap()
    rclpy.spin(load_map)
    load_map.destroy_node()
    rclpy.shutdown()



if __name__ == '__main__':
    main()