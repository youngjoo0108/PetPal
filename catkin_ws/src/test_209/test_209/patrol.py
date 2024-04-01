import rclpy
import numpy as np
from rclpy.node import Node
import os
from geometry_msgs.msg import Pose,PoseStamped
from squaternion import Quaternion
from nav_msgs.msg import Odometry,OccupancyGrid,MapMetaData,Path
from std_msgs.msg import Int32
from math import pi,cos,sin, sqrt
from collections import deque
from queue import PriorityQueue

class patrolRoute(Node):

    def __init__(self):
        super().__init__('patrolRoute')
        self.odom_sub = self.create_subscription(Odometry,'/odom',self.odom_callback, 10)
        self.goal_pub = self.create_publisher(PoseStamped,'goal_pose', 10)
        self.patrol_sub = self.create_subscription(Int32, '/patrol', self.patrol_callback, 10)
        self.map_sub = self.create_subscription(OccupancyGrid,'/map',self.map_callback,10)
        self.timer = self.create_timer(0.5, self.timer_callback)

        self.error_msg = Int32()
        self.is_route = False

        self.goal_msg = PoseStamped()
        self.goal_msg.header.frame_id = 'map'
        self.odom_msg = Odometry()

        self.map_size_x=700
        self.map_size_y=700
        self.map_resolution=0.05

        self.is_odom=False
        self.is_goal = True
        self.is_param = False
        self.is_map = False

        self.idx = 0
        self.route = []

        full_path = 'C:\\Users\\SSAFY\\Desktop\\pppp.txt'
        f=open(full_path,'r')
        lines = f.readlines()
        for line in lines:
            data = line.split()
            self.route.append((int(data[0]), int(data[1])))
            
    
    def patrol_callback(self, msg):
        if msg.data == 0:
            self.is_goal = False

        elif msg.data == 1:
            if self.is_goal == False:
                self.idx += 1
                if self.idx >= len(self.route):
                    self.idx = 0
                self.is_goal = True

    def odom_callback(self, msg):
        if self.is_param == False and self.is_map == True:
            self.is_param = True

            self.map_offset_x = self.map_msg.info.origin.position.x
            self.map_offset_y = self.map_msg.info.origin.position.y

        self.is_odom = True
        self.odom_msg = msg
    
    def map_callback(self,msg):
        self.is_map = True
        self.map_msg = msg

    def grid_update(self):
        self.is_grid_update=True
        self.map_to_grid = np.array(self.map_msg.data).reshape((self.map_size_x, self.map_size_y)).transpose()

        for i in range(self.map_size_x):
            for j in range(self.map_size_y):
                # 값이 100인 원소 찾기
                if self.map_to_grid[i, j] == 100:
                    # 주변 원소 탐색
                    for dx in range(-5, 6):  # x 좌표 차이가 -2부터 2까지
                        for dy in range(-5, 6):  # y 좌표 차이가 -2부터 2까지
                            # 새로운 위치 계산
                            new_i = i + dx
                            new_j = j + dy
                            # 새로운 위치가 배열 범위 내에 있는지 확인
                            if 0 <= new_i < self.map_size_x and 0 <= new_j < self.map_size_y and self.map_to_grid[new_i, new_j] == 0:
                                # 조건에 맞는 주변 원소의 값을 100으로 설정
                                self.map_to_grid[new_i, new_j] = 101

    def timer_callback(self):
        if self.is_param and self.is_map and self.is_odom:
            if self.is_goal:
                self.is_goal = False
                now_goal = self.route[self.idx]
                #print(self.idx, 'th = ', now_goal)
                goal_x, goal_y = self.grid_cell_to_pose(now_goal)
                self.goal_msg.pose.position.x = goal_x
                self.goal_msg.pose.position.y = goal_y

                q = Quaternion.from_euler(0, 0, 0)
                self.goal_msg.pose.orientation.x = q.x
                self.goal_msg.pose.orientation.y = q.y
                self.goal_msg.pose.orientation.z = q.z
                self.goal_msg.pose.orientation.w = q.w

                self.goal_msg.header.stamp = rclpy.clock.Clock().now().to_msg()
                self.goal_pub.publish(self.goal_msg)

    def pose_to_grid_cell(self,x,y):
        map_point_x = int((x - self.map_offset_x) / self.map_resolution)
        map_point_y = int((y - self.map_offset_y) / self.map_resolution)
        
        return map_point_x,map_point_y

    def grid_cell_to_pose(self,grid_cell):
        x = grid_cell[0] * self.map_resolution + self.map_offset_x
        y = grid_cell[1] * self.map_resolution + self.map_offset_y

        return [x,y]


def main(args=None):
    rclpy.init(args=args)
    patrol = patrolRoute()
    rclpy.spin(patrol)
    patrol.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()
