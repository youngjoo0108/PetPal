import rclpy, json, os
import numpy as np
from rclpy.node import Node
from geometry_msgs.msg import Pose,PoseStamped
from squaternion import Quaternion
from nav_msgs.msg import Odometry,OccupancyGrid,MapMetaData,Path
from std_msgs.msg import Int32, String
from math import pi,cos,sin, sqrt
from collections import deque
from queue import PriorityQueue

class patrolRoute(Node):

    def __init__(self):
        super().__init__('patrolRoute')
        self.map_sub = self.create_subscription(OccupancyGrid,'/map',self.map_callback,10)
        self.odom_sub = self.create_subscription(Odometry,'/odom',self.odom_callback, 10)
        self.goal_pub = self.create_publisher(PoseStamped,'goal_pose', 10)
        self.patrol_sub = self.create_subscription(Int32, '/patrol', self.patrol_callback, 10)
        self.reqeust_pub = self.create_publisher(String, '/request', 20)
        self.yolo_sub = self.create_subscription(String,'captured_object',self.yolo_callback, 10)

        self.timer = self.create_timer(0.5, self.timer_callback)

        # test
        self.error_pub = self.create_publisher(Int32, 'err', 10)
        self.error_msg = Int32()
        self.is_route = False

        self.goal_msg = PoseStamped()
        self.goal_msg.header.frame_id = 'map'
        self.map_msg = OccupancyGrid()
        self.odom_msg = Odometry()

        self.map_size_x=700
        self.map_size_y=700
        self.map_resolution=0.05
        self.GRIDSIZE=700

        self.dx = [0,1,0,-1,-1,-1,1,1]
        self.dy = [-1,0,1,0,-1,1,-1,1]
        self.dCost = [1,1,1,1,1.414,1.414,1.414,1.414]

        self.yolo_sub
        self.request_msg = String()

        self.is_odom=False
        self.is_map=False
        self.is_make_list=False
        self.is_param = False
        self.is_goal = False

        self.goal_list = []
        self.idx = 0
        self.edges = []
        self.route = []
        self.count = 0
        self.new_grid = np.zeros((70,70))

    
    def yolo_callback(self, msg):

        data = json.loads(msg.data)
        if data:
            if 'dog_list' in data:
                pass
            elif 'knife_list' in data:
                self.request_msg.data = 'interrupt_on'
                self.reqeust_pub.publish(self.goal_msg)



    def patrol_callback(self, msg):
        if msg.data == 0:
            self.is_goal = False

        elif msg.data == 1:
            if self.is_goal == False:
                self.idx += 1
                if self.idx >= len(self.route):
                    self.idx = 0
                self.is_goal = True


    def map_callback(self,msg):
        self.is_map = True
        self.map_msg = msg


    def odom_callback(self, msg):
        if self.is_param == False and self.is_map == True:
            self.is_param = True

            self.map_offset_x = self.map_msg.info.origin.position.x
            self.map_offset_y = self.map_msg.info.origin.position.y

        self.is_odom = True
        self.odom_msg = msg

    # def save(self):
    #     full_path = 'C:\\Users\\SSAFY\\Desktop\\tt.txt'
    #     f=open(full_path,'w')
    #     data=''

    #     for i in range(70):
    #         for j in range(70):
    #             data += '{0} '.format(self.new_grid[i, j])
    #         data += '\n'
        
    #     f.write(data) 
    #     f.close()
    #     print('done')


    def timer_callback(self):
        if self.is_param==False:
            return

        x=self.odom_msg.pose.pose.position.x
        y=self.odom_msg.pose.pose.position.y
        now_grid_cell=self.pose_to_grid_cell(x,y)

        if self.is_goal and 100 <= self.map_to_grid[now_grid_cell[0], now_grid_cell[1]]:
            self.error_msg.data = 2
            self.error_pub.publish(self.error_msg)
        else:
            self.error_msg.data = 0
            self.error_pub.publish(self.error_msg)

        if self.is_map==True and self.is_odom==True:
            if self.is_make_list==False :
                self.make_list()
                self.calc_route()
                self.is_make_list=True
                
                #self.save()
            
            # if not self.is_route:
            #     self.is_route=True

            #     temp_array = []

            #     for i in range(len(self.route)):
            #         temp_array.append(self.goal_list[self.route[i]][0])
            #         temp_array.append(self.goal_list[self.route[i]][1])

            #     self.patrol_msg.data = temp_array

            #     self.patrol_pub.publish(self.patrol_msg)
            # -----
            now_goal = self.goal_list[self.route[self.idx]]
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


    def bfs(self, idx):
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
        self.map_to_grid = np.array(self.map_msg.data).reshape((self.map_size_x, self.map_size_y)).transpose()

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
            self.bfs(i)

        self.prim(goal_num)
        

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
