# import rclpy
# from rclpy.node import Node
# from squaternion import Quaternion
# from nav_msgs.msg import Odometry, OccupancyGrid
# from math import pi,cos,sin
# import tf2_ros
# import geometry_msgs.msg
# import time
# import numpy as np

# # odom 노드는 로봇의 속도(/turtlebot_status), Imu센서(/imu) 메시지를 받아서 로봇의 위치를 추정하는 노드입니다.
# # sub1_odom은 imu로 부터 받은 Quaternion을 사용하거나 각속도, 가속도 데이터를 이용해서 로봇의 포즈를 추정 할 것입니다.

# # 노드 로직 순서
# # 1. publisher, subscriber, broadcaster 만들기
# # 2. publish, broadcast 할 메시지 설정
# # 3. imu 에서 받은 quaternion을 euler angle로 변환해서 사용
# # 4. 로봇 위치 추정
# # 5. 추정한 로봇 위치를 메시지에 담아 publish, broadcast


# class odom(Node):

#     def __init__(self):
#         super().__init__('odom')
        
#         # 로직 1. publisher, subscriber, broadcaster 만들기

#         self.map_sub = self.create_subscription(OccupancyGrid,'map',self.map_callback,1) #tt
#         self.odom_sub = self.create_subscription(Odometry,'odom',self.odom_callback,1)


#         # 로봇의 pose를 저장해 publish 할 메시지 변수 입니다.
#         self.odom_msg=Odometry()
#         self.map_msg=OccupancyGrid() # tt

#         self.map_size_x=350
#         self.map_size_y=350
#         self.map_resolution=0.05
#         self.map_offset_x=-8-8.75
#         self.map_offset_y=-4-8.75

#         time_period = 0.5
#         self.timer = self.create_timer(time_period, self.timer_callback)


#     def pose_to_grid_cell(self,x,y):
#         map_point_x = int((x - self.map_offset_x) / self.map_resolution)
#         map_point_y = int((y - self.map_offset_y) / self.map_resolution)
        
#         return map_point_x,map_point_y


#     def grid_cell_to_pose(self,grid_cell):

#         x = grid_cell[0] * self.map_resolution + self.map_offset_x
#         y = grid_cell[1] * self.map_resolution + self.map_offset_y

#         return [x,y]

#     def map_callback(self, msg): # tt
#         self.map_msg = msg
#         self.map_to_grid = np.array(self.map_msg.data).reshape((self.map_size_x, self.map_size_y))


#     def odom_callback(self, msg):
#         self.odom_msg = msg

#     def timer_callback(self):
#         x = self.odom_msg.pose.pose.position.x
#         y = self.odom_msg.pose.pose.position.y
#         cell_x, cell_y = self.pose_to_grid_cell(x,y)
#         print(self.map_to_grid[cell_x][cell_y])


        
# def main(args=None):
#     rclpy.init(args=args)
#     odom_node = odom()
#     rclpy.spin(odom_node)
#     odom_node.destroy_node()
#     rclpy.shutdown()


# if __name__ == '__main__':
#     main()