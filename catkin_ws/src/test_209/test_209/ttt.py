import rclpy, requests, json
import numpy as np
from rclpy.node import Node

import os
from geometry_msgs.msg import Pose
from squaternion import Quaternion
from nav_msgs.msg import Odometry,OccupancyGrid,MapMetaData
from math import pi
from test_209.resize_map import resize

class loadMap(Node):

    def __init__(self):
        super().__init__('load_map')
        self.odom_sub = self.create_subscription(Odometry,'odom',self.odom_callback,1)
        
        self.is_odom = False

        self.map_msg=OccupancyGrid()
        self.map_size_x=700 
        self.map_size_y=700
        self.map_resolution=0.05
        # self.map_offset_x = -8 - (self.map_size_x * self.map_resolution) / 2
        # self.map_offset_y = -4 - (self.map_size_y * self.map_resolution) / 2
        self.map_data = [0 for i in range(self.map_size_x*self.map_size_y)]

        self.map_msg.header.frame_id="map"

        self.read_txt()
        # m = MapMetaData()
        # m.resolution = self.map_resolution
        # m.width = self.map_size_x
        # m.height = self.map_size_y
        # m.origin = Pose()
        # m.origin.position.x = self.map_offset_x
        # m.origin.position.y = self.map_offset_y

        # self.map_meta_data = m
        # self.map_msg.info=self.map_meta_data

    def read_txt(self):
        full_path = 'C:\\Users\\SSAFY\\Desktop\\\S10P22A209\\catkin_ws\\src\\test_209\\map\\map.txt'
        self.f = open(full_path, 'r')
        
        lines = self.f.readlines()
        line_data = lines[0].split()
        offset = lines[1].split()
        offset_x, offset_y = float(offset[0]), float(offset[1])
        
        for num,data in enumerate(line_data) :
            self.map_data[num] = int(data)

        grid = np.array(self.map_data)
        grid = np.reshape(grid,(self.map_size_x, self.map_size_y))

        # for y in range(self.map_size_y):
        #     for x in range(self.map_size_x):
        #         if grid[x][y]==100 :
        #             for dx in range(-10, 11):
        #                 for dy in range(-10, 11):
        #                     new_i = x + dx
        #                     new_j = y + dy

        #                     if 0 <= new_i < self.map_size_x and 0 <= new_j < self.map_size_y and grid[new_i, new_j] != 127:
        #                         grid[new_i, new_j] = 127
                
        
        np_map_data=grid.reshape(1,self.map_size_x*self.map_size_y) 
        list_map_data=np_map_data.tolist()

        ## 로직2를 완성하고 주석을 해제 시켜주세요.
        self.f.close()
        self.map_msg.data=list_map_data[0]
        self.map_msg.info.origin.position.x = offset_x
        self.map_msg.info.origin.position.y = offset_y

        self.resize = resize(self.map_msg)

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



       
def main(args=None):
    rclpy.init(args=args)

    load_map = loadMap()
    rclpy.spin(load_map)
    load_map.destroy_node()
    rclpy.shutdown()



if __name__ == '__main__':
    main()