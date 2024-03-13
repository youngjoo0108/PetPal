import rclpy
import numpy as np
from rclpy.node import Node
import os
from geometry_msgs.msg import Pose,PoseStamped
from squaternion import Quaternion
from nav_msgs.msg import Odometry,OccupancyGrid,MapMetaData,Path
from math import pi,cos,sin
from collections import deque


class rrt_star(Node):

    def __init__(self):
        super().__init__('a_Star')
        # 로직 1. publisher, subscriber 만들기
        self.map_sub = self.create_subscription(OccupancyGrid,'map',self.map_callback,1)
        self.odom_sub = self.create_subscription(Odometry,'odom',self.odom_callback,1)
        self.goal_sub = self.create_subscription(PoseStamped,'goal_pose',self.goal_callback,1)
        self.a_star_pub= self.create_publisher(Path, 'global_path', 1)
        
        self.map_msg=OccupancyGrid()
        self.odom_msg=Odometry()
        self.is_map=False
        self.is_odom=False
        self.is_found_path=False
        self.is_grid_update=False


        # 로직 2. 파라미터 설정
        self.goal = [184,224] 
        self.map_size_x=350
        self.map_size_y=350
        self.map_resolution=0.05
        self.map_offset_x=-8-8.75
        self.map_offset_y=-4-8.75
    
        self.GRIDSIZE=350
       

    def grid_update(self):
        self.is_grid_update=True
        self.map_to_grid = np.array(self.map_msg.data).reshape((self.map_size_x, self.map_size_y)).transpose()
        self.grid = np.where(self.map_to_grid > 30, 1, 0)  # Obstacle cells as 1, free space as 0


    def pose_to_grid_cell(self,x,y):
        map_point_x = int((x - self.map_offset_x) / self.map_resolution)
        map_point_y = int((y - self.map_offset_y) / self.map_resolution)
        
        return map_point_x,map_point_y


    def grid_cell_to_pose(self,grid_cell):
        
        x = grid_cell[0] * self.map_resolution + self.map_offset_x
        y = grid_cell[1] * self.map_resolution + self.map_offset_y

        return [x,y]


    def odom_callback(self,msg):
        self.is_odom=True
        self.odom_msg=msg


    def map_callback(self,msg):
        self.is_map=True
        self.map_msg=msg
        

    def goal_callback(self,msg):
        
        if msg.header.frame_id=='map':
            goal_x=msg.pose.position.x
            goal_y=msg.pose.position.y
            goal_cell=self.pose_to_grid_cell(goal_x, goal_y)
            self.goal = goal_cell            

            if self.is_map ==True and self.is_odom==True  :
                if self.is_grid_update==False :
                    self.grid_update()

                self.final_path=[]

                x=self.odom_msg.pose.pose.position.x
                y=self.odom_msg.pose.pose.position.y
                start_grid_cell=self.pose_to_grid_cell(x,y)

                self.path = [[0 for col in range(self.GRIDSIZE)] for row in range(self.GRIDSIZE)]
                
                if self.grid[self.goal[0]][self.goal[1]] ==0  and start_grid_cell != self.goal :
                    self.dijkstra(start_grid_cell)
                else:
                    print('na')


                self.global_path_msg=Path()
                self.global_path_msg.header.frame_id='map'
                print(self.final_path)
                for grid_cell in reversed(self.final_path) :
                    tmp_pose=PoseStamped()
                    waypoint_x,waypoint_y=self.grid_cell_to_pose(grid_cell)
                    tmp_pose.pose.position.x=waypoint_x
                    tmp_pose.pose.position.y=waypoint_y
                    tmp_pose.pose.orientation.w=1.0
                    self.global_path_msg.poses.append(tmp_pose)
            
                if len(self.final_path)!=0 :
                    self.a_star_pub.publish(self.global_path_msg)

    def dijkstra(self,start):
        Q = deque()
        Q.append(start)
        self.cost[start[0]][start[1]] = 0
        found = False
        
        # 로직 7. grid 기반 최단경로 탐색
        
        while Q:
            current = Q.popleft()
            if current == self.goal:
                found = True
                break

            for i in range(8):
                next = (current[0] + self.dx[i], current[1] + self.dy[i])
                if 0 <= next[0] < self.GRIDSIZE and 0 <= next[1] < self.GRIDSIZE:
                    # Check if the 3x3 area around the next point is all zero
                    area_is_clear = True
                    for x in range(next[0]-2, next[0]+3):
                        for y in range(next[1]-2, next[1]+3):
                            if not (0 <= x < self.GRIDSIZE and 0 <= y < self.GRIDSIZE):
                                area_is_clear = False
                                break
                            if self.grid[x][y] != 0:
                                area_is_clear = False
                                break
                        if not area_is_clear:
                            break

                    if area_is_clear:
                        new_cost = self.cost[current[0]][current[1]] + self.dCost[i]
                        if self.cost[next[0]][next[1]] > new_cost:
                            Q.append(next)
                            self.path[next[0]][next[1]] = current
                            self.cost[next[0]][next[1]] = new_cost
        if found:
            node = self.goal
            while node != start:
                self.final_path.append(node)
                node = self.path[node[0]][node[1]]                

        
def main(args=None):
    rclpy.init(args=args)

    global_planner = rrt_star()

    rclpy.spin(global_planner)


    global_planner.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()
