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

class mapSetting(Node):

    def __init__(self):
        super().__init__('mapSetting')
        self.map_sub = self.create_subscription(OccupancyGrid,'/map',self.map_callback,10)
        self.odom_sub = self.create_subscription(Odometry,'/odom',self.odom_callback, 10)
        self.goal_pub = self.create_publisher(PoseStamped,'goal_pose', 10)
        self.timer = self.create_timer(0.5, self.timer_callback)

        # test
        self.error_pub = self.create_publisher(Int32, 'err', 10)
        self.error_msg = Int32()

        self.goal_msg = PoseStamped()
        self.goal_msg.header.frame_id = 'map'
        self.map_msg = OccupancyGrid()
        self.odom_msg = Odometry()

        self.map_size_x=700
        self.map_size_y=700
        self.map_resolution=0.05
        # self.map_offset_x=-8-8.75
        # self.map_offset_y=-4-8.75

        self.dx = [-1,0,0,1]
        self.dy = [0,1,-1,0]
        self.is_goal = False
        self.goal = [ 0, 0 ]

        self.is_odom=False
        self.is_map=False
        self.is_grid_update=False
        self.is_param = False

        self.end_count = 0
        self.count1 = [0, 0]
        self.count2 = 0

    
    def map_callback(self,msg):
        self.is_map = True
        self.map_msg = msg
        self.is_grid_update = False


    def odom_callback(self, msg):
        if self.is_param == False:
            self.is_param = True

            self.map_offset_x= msg.pose.pose.position.x - (self.map_size_x*self.map_resolution*0.5)
            self.map_offset_y= msg.pose.pose.position.y - (self.map_size_y*self.map_resolution*0.5)

        self.is_odom = True
        self.odom_msg = msg
        

    def timer_callback(self):
        if self.is_param==False or self.is_goal==True:
            return

        x=self.odom_msg.pose.pose.position.x
        y=self.odom_msg.pose.pose.position.y
        now_grid_cell=self.pose_to_grid_cell(x,y)

        # dist = sqrt(pow(now_grid_cell[0] - self.goal[0], 2) + pow(now_grid_cell[1] - self.goal[1], 2))
        # if self.is_goal == False and dist > 5:
        #     return

        if self.is_map==True and self.is_odom==True:
            if self.is_grid_update==False :
                self.grid_update()

            # if self.is_goal: # 도착한 경우 새 목적지 설정
                #print(now_grid_cell)
            if 100 <= self.map_to_grid[now_grid_cell[0], now_grid_cell[1]]:
                if self.count2 >= 10:
                    self.count2 = 0
                    self.error_msg.data = 4
                    print('error4')
                else:
                    self.count2 += 1
                    self.error_msg.data = 2
                    print('error2')
                
                self.error_pub.publish(self.error_msg)
                return
            else:
                self.count2 = 0

            self.goal = self.select_goal(now_grid_cell)
            print(self.goal)
            dis = (now_grid_cell[0] - self.goal[0], now_grid_cell[1] - self.goal[1])
            if self.goal == [-1, -1] or (dis[0]*dis[0]+dis[1]*dis[1]) <= 25:
                if self.count1[1] >= 10 and self.count1[0] < 2:
                    self.count1[1] = 0
                    self.count1[0] += 1
                    self.error_msg.data = 0
                    self.error_pub.publish(self.error_msg)
                    self.goal = [350, 350]
                elif self.count1[1] >= 10 and self.count1[0] >= 2:
                    self.error_msg.data = 100
                    self.error_pub.publish(self.error_msg)
                    self.is_goal = True
                    print('End')
                else:
                    self.count1[1] += 1
                    self.error_msg.data = 1
                    self.error_pub.publish(self.error_msg)
                    return
                
                # self.error_pub.publish(self.error_msg)
                # return
            elif self.goal == [-2, -2]:
                self.error_msg.data = 100
                self.error_pub.publish(self.error_msg)
                self.is_goal = True
                print('End')

            else:
                self.count1 = [0, 0]
                self.error_msg.data = 0
                self.error_pub.publish(self.error_msg)
                
            goal_x, goal_y = self.grid_cell_to_pose(self.goal)

            self.goal_msg.pose.position.x = goal_x
            self.goal_msg.pose.position.y = goal_y

            q = Quaternion.from_euler(0, 0, 0)
            self.goal_msg.pose.orientation.x = q.x
            self.goal_msg.pose.orientation.y = q.y
            self.goal_msg.pose.orientation.z = q.z
            self.goal_msg.pose.orientation.w = q.w

            self.goal_msg.header.stamp = rclpy.clock.Clock().now().to_msg()
            self.goal_pub.publish(self.goal_msg)

            # else: # 도착하지 않은 경우
            #     print(self.map_to_grid[self.goal[0]][self.goal[1]])
            #     if self.map_to_grid[self.goal[0]][self.goal[1]] == 0:
            #         self.is_goal = True
            # else:
            #     dis = sqrt(pow(now_grid_cell[0] - self.goal[0], 2) + pow(now_grid_cell[1] - self.goal[1], 2))
            #     if dis < 7:
            #         self.is_goal = True
            #     if self.map_to_grid[now_grid_cell[0], now_grid_cell[1]] == 0 or self.map_to_grid[now_grid_cell[0], now_grid_cell[1]] >= 100:
            #         self.is_goal = True
        
    def grid_update(self):
        self.is_grid_update=True
        self.map_to_grid = np.array(self.map_msg.data).reshape((self.map_size_x, self.map_size_y)).transpose()

        for i in range(self.map_size_x):
            for j in range(self.map_size_y):
                # 값이 100인 원소 찾기
                if self.map_to_grid[i, j] == 100:
                    # 주변 원소 탐색
                    for dx in range(-6, 7):
                        for dy in range(-6, 7):
                            # 새로운 위치 계산
                            new_i = i + dx
                            new_j = j + dy
                            # 새로운 위치가 배열 범위 내에 있는지 확인
                            if 0 <= new_i < self.map_size_x and 0 <= new_j < self.map_size_y and self.map_to_grid[new_i, new_j] == 0:
                                # 조건에 맞는 주변 원소의 값을 100으로 설정
                                self.map_to_grid[new_i, new_j] = 101


    def pose_to_grid_cell(self,x,y):
        map_point_x = int((x - self.map_offset_x) / self.map_resolution)
        map_point_y = int((y - self.map_offset_y) / self.map_resolution)
        
        return map_point_x,map_point_y

    def grid_cell_to_pose(self,grid_cell):
        x = grid_cell[0] * self.map_resolution + self.map_offset_x
        y = grid_cell[1] * self.map_resolution + self.map_offset_y

        return [x,y]

    def select_goal(self, start):

        Q = deque()
        Q.append(start)
        vis = np.zeros((self.map_size_x, self.map_size_y))
        vis[start[0]][start[1]] = 1

        while Q:
            now = Q.popleft()

            if vis[now[0], now[1]] >= 400 and self.map_to_grid[now[0], now[1]] == 0:
                self.end_count += 1
                if self.end_count >= 10:
                    return [-2, -2]
                else:
                    return [now[0], now[1]]

            for i in range(4):
                next_x, next_y = now[0] + self.dx[i], now[1] + self.dy[i]

                if not (0 <= next_x < self.map_size_x and 0 <= next_y < self.map_size_y):
                    continue  # 맵 범위를 벗어나면 무시
                if vis[next_x][next_y] != 0:
                    continue  # 이미 방문한 셀은 무시

                vis[next_x, next_y] = vis[now[0], now[1]] + 1
                #print(next_x, next_y)
                if self.map_to_grid[next_x][next_y] == 0:
                    Q.append((next_x, next_y))
                elif 10 < self.map_to_grid[next_x][next_y] and self.map_to_grid[next_x][next_y] < 100:
                    self.target = [next_x, next_y]
                    return [now[0], now[1]]
    
        return [-1, -1]  # 목표 지점을 찾지 못한 경우
    

def main(args=None):
    rclpy.init(args=args)
    map_set = mapSetting()
    rclpy.spin(map_set)
    map_set.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()
