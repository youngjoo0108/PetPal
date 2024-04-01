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

class makeRoute:

    def __init__(self, map_data):

        self.map_data = OccupancyGrid()
        self.map_data = map_data

        self.map_size_x=700
        self.map_size_y=700
        self.map_resolution=0.05
        self.GRIDSIZE=700

        self.dx = [0,1,0,-1,-1,-1,1,1]
        self.dy = [-1,0,1,0,-1,1,-1,1]
        self.dCost = [1,1,1,1,1.414,1.414,1.414,1.414]

        self.goal_list = []
        self.idx = 0
        self.edges = []
        self.route = []
        self.count = 0
        self.new_grid = np.zeros((70,70))

        self.make_list()
        self.calc_route()
        self.rearrange()


    def dijkstra(self, idx):
        start = self.goal_list[idx]
        Q = deque()
        Q.append(start)
        self.cost[start[0]][start[1]] = 0
        
        while Q:
            current = Q.popleft()

            for i in range(8):
                next = (current[0] + self.dx[i], current[1] + self.dy[i])
                if 0 <= next[0] < self.GRIDSIZE and 0 <= next[1] < self.GRIDSIZE:
                    if self.map_to_grid[next[0]][next[1]] == 0:
                        new_cost = self.cost[current[0]][current[1]] + self.dCost[i]
                        if self.cost[next[0]][next[1]] > new_cost:
                            Q.append(next)
                            self.cost[next[0]][next[1]] = new_cost

        for i in range(len(self.goal_list)):
            if i == idx:
                continue
            if self.cost[self.goal_list[i][0], self.goal_list[i][1]] == 0 or self.cost[self.goal_list[i][0], self.goal_list[i][1]] > 200:
                self.edges[idx, i] = -1
            else:
                self.edges[idx, i] = self.cost[self.goal_list[i][0], self.goal_list[i][1]]
    
    def prim(self, num):
        que = PriorityQueue()

        vis = np.zeros(num)
        vis[0] = 1
        self.route.append(0)

        cnt = 1

        for i in range(num):
            if self.edges[0, i] == -1 or self.edges[0, i] == 0:
                continue
            que.put((self.edges[0, i], i))
        
        while que:
            if cnt >= num:
                break
            now_edge = que.get()
            node = now_edge[1]

            if vis[node] != 0:
                continue
            vis[node] = 1
            cnt += 1
            self.route.append(node)

            for i in range(num):
                next_edge = (self.edges[node, i], i)
                if next_edge[0] == -1 or next_edge[0] == 0:
                    continue
                if vis[i] != 0:
                    continue
                que.put(next_edge)


    def make_list(self):
        self.map_to_grid = np.array(self.map_data).reshape((self.map_size_x, self.map_size_y)).transpose()

        for i in range(self.map_size_x):
            for j in range(self.map_size_y):
                if self.map_to_grid[i, j] == 100:
                    for dx in range(-5, 6):
                        for dy in range(-5, 6):
                            new_i = i + dx
                            new_j = j + dy
                            if 0 <= new_i < self.map_size_x and 0 <= new_j < self.map_size_y and self.map_to_grid[new_i, new_j] == 0:
                                # 조건에 맞는 주변 원소의 값을 100으로 설정
                                self.map_to_grid[new_i, new_j] = 101

        for i in range(1, 34):
            for j in range(1, 34):
                x = 20*i + 10
                y = 20*j + 10
                if self.map_to_grid[x, y] == 0:
                    for d in range(4):
                        next1 = (x + 20*self.dx[d], y + 20*self.dy[d])
                        next2 = (x + 20*self.dx[(d+1)%4], y + 20*self.dy[(d+1)%4])
                        if self.map_to_grid[next1[0], next1[1]] != 0 and self.map_to_grid[next2[0], next2[1]] != 0:
                            self.goal_list.append((x, y))
                            break
    
    def calc_route(self):
        goal_num = len(self.goal_list)
        self.edges = np.zeros((goal_num, goal_num))

        for i in range(goal_num):
            self.cost = np.array([[self.GRIDSIZE*self.GRIDSIZE for col in range(self.GRIDSIZE)] for row in range(self.GRIDSIZE)], dtype=float)
            self.dijkstra(i)

        self.prim(goal_num)

    def rearrange(self):
        self.answer = [() for _ in range(len(self.goal_list))]
        for i in range(len(self.goal_list)):
            self.answer[self.route[i]] = self.goal_list[i]
        