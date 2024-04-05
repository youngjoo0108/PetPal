import rclpy, json
import numpy as np
from rclpy.node import Node

import os
from geometry_msgs.msg import Pose
from squaternion import Quaternion
from nav_msgs.msg import Odometry,OccupancyGrid,MapMetaData
from std_msgs.msg import String
from math import pi
from test_209.resize_map import resize

# load_map 노드는 맵 데이터를 읽어서, 맵 상에서 점유영역(장애물) 근처에 로봇이 움직일 수 없는 영역을 설정하고 맵 데이터로 publish 해주는 노드입니다.
# 추 후 a_star 알고리즘에서 맵 데이터를 subscribe 해서 사용합니다.

# 노드 로직 순서
# 1. 맵 파라미터 설정
# 2. 맵 데이터 읽고, 2차원 행렬로 변환
# 3. 점유영역 근처 필터처리

class loadMap(Node):

    def __init__(self):
        super().__init__('load_map')
        self.odom_sub = self.create_subscription(Odometry,'odom',self.odom_callback,10)
        self.map_pub = self.create_publisher(OccupancyGrid, 'map', 10)
        self.data_pub = self.create_publisher(String, '/to_server/data', 10)
        
        #self.timer = self.create_timer(1, self.timer_callback)
        self.is_odom = False

        self.odom_msg = Odometry()
        self.map_msg=OccupancyGrid()
        self.map_size_x=700 
        self.map_size_y=700
        self.map_resolution=0.05
        # self.map_offset_x = -8 - (self.map_size_x * self.map_resolution) / 2
        # self.map_offset_y = -4 - (self.map_size_y * self.map_resolution) / 2
        self.map_data = [0 for i in range(self.map_size_x*self.map_size_y)]

        self.map_msg.header.frame_id="map"

        full_path = 'C:\\Users\\SSAFY\\Desktop\\\S10P22A209\\catkin_ws\\src\\test_209\\map\\new_map.txt'
        f=open(full_path,'r')
        line = f.readlines()[0].split()
        self.start_grid = (int(line[0]), int(line[1]))
        f.close()
        #print(self.start_grid)

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
        self.map_offset_x, self.map_offset_y = float(offset[0]), float(offset[1])
        
        for num,data in enumerate(line_data) :
            self.map_data[num] = int(data)

        grid = np.array(self.map_data)
        grid = np.reshape(grid,(self.map_size_x, self.map_size_y))
                
        
        np_map_data=grid.reshape(1,self.map_size_x*self.map_size_y) 
        list_map_data=np_map_data.tolist()

        ## 로직2를 완성하고 주석을 해제 시켜주세요.
        self.f.close()
        self.map_msg.data=list_map_data[0]
        self.map_msg.info.origin.position.x = self.map_offset_x
        self.map_msg.info.origin.position.y = self.map_offset_y

    def odom_callback(self, msg):
        self.odom_msg = msg
        if self.is_odom == False:
            self.is_odom = True

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
            self.resize = resize(self.map_msg)


    def timer_callback(self):
        if self.is_odom:
            self.map_msg.header.stamp =rclpy.clock.Clock().now().to_msg()
            self.map_pub.publish(self.map_msg)

            x=self.odom_msg.pose.pose.position.x
            y=self.odom_msg.pose.pose.position.y
            now_grid_cell=self.pose_to_grid_cell(x,y)
            new_grid_cell=(now_grid_cell[0]-self.start_grid[0], now_grid_cell[1]-self.start_grid[1])
            print(now_grid_cell)
            print(new_grid_cell)

            msg = String()
            temp = {
                'type' : 'TURTLE',
                'message' : ""
            }
            data = json.dumps(temp)
            msg.data = data
            self.data_pub.publish(msg)

    def pose_to_grid_cell(self,x,y):

        map_point_x = int((x - self.map_offset_x) / self.map_resolution)
        map_point_y = int((y - self.map_offset_y) / self.map_resolution)
        
        return map_point_x,map_point_y

       
def main(args=None):
    rclpy.init(args=args)

    load_map = loadMap()
    rclpy.spin(load_map)
    load_map.destroy_node()
    rclpy.shutdown()



if __name__ == '__main__':
    main()