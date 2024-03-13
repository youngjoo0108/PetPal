# import rclpy
# from rclpy.node import Node
# from geometry_msgs.msg import Twist
# from nav_msgs.msg import Odometry, Path
# from squaternion import Quaternion
# from math import atan2, sqrt

# class PurePursuit(Node):
#     def __init__(self):
#         super().__init__('pure_pursuit_path_tracking')
#         self.cmd_pub = self.create_publisher(Twist, 'cmd_vel', 10)
#         self.odom_sub = self.create_subscription(Odometry, '/odom', self.odom_callback, 10)
#         self.path_sub = self.create_subscription(Path, '/local_path', self.path_callback, 10)

#         self.is_odom = False
#         self.is_path = False
#         self.odom_msg = Odometry()
#         self.path_msg = Path()

#         self.lookahead_distance = 1.0  # Lookahead distance 설정, 상황에 맞게 조정

#     def odom_callback(self, msg):
#         self.is_odom = True
#         self.odom_msg = msg

#     def path_callback(self, msg):
#         self.is_path = True
#         self.path_msg = msg

#     def get_nearest_point_index(self, robot_position, path_points):
#         closest_point_index = 0
#         closest_distance = float('inf')

#         for i, point in enumerate(path_points):
#             distance = sqrt((point.x - robot_position.x)**2 + (point.y - robot_position.y)**2)
#             if distance < closest_distance:
#                 closest_point_index = i
#                 closest_distance = distance
        
#         return closest_point_index

#     def get_lookahead_point(self, start_index, path_points):
#         for i in range(start_index, len(path_points)):
#             distance = sqrt((path_points[i].x - self.odom_msg.pose.pose.position.x)**2 + (path_points[i].y - self.odom_msg.pose.pose.position.y)**2)
#             if distance >= self.lookahead_distance:
#                 return path_points[i]
#         return None

#     def timer_callback(self):
#         if self.is_odom and self.is_path:
#             path_points = [pose.pose.position for pose in self.path_msg.poses]
#             robot_position = self.odom_msg.pose.pose.position

#             closest_point_index = self.get_nearest_point_index(robot_position, path_points)
#             lookahead_point = self.get_lookahead_point(closest_point_index, path_points)

#             if lookahead_point is not None:
#                 robot_orientation_q = self.odom_msg.pose.pose.orientation
#                 robot_orientation_euler = Quaternion(robot_orientation_q.w, robot_orientation_q.x, robot_orientation_q.y, robot_orientation_q.z).to_euler()
#                 robot_yaw = robot_orientation_euler[2]

#                 angle_to_target = atan2(lookahead_point.y - robot_position.y, lookahead_point.x - robot_position.x)
#                 angle_diff = (angle_to_target - robot_yaw)

#                 cmd_msg = Twist()
#                 cmd_msg.linear.x = 0.5  # 기본 선속도 설정, 상황에 맞게 조정
#                 cmd_msg.angular.z = 1.5 * angle_diff  # 회전속도 설정, 상황에 맞게 조정

#                 self.cmd_pub.publish(cmd_msg)

#     def run(self):
#         self.timer = self.create_timer(0.1, self.timer_callback)  # 0.1초마다 timer_callback 실행

# def main(args=None):
#     rclpy.init(args=args)
#     pure_pursuit_node = PurePursuit()
#     rclpy.spin(pure_pursuit_node)
#     pure_pursuit_node.destroy_node()
#     rclpy.shutdown()

# if __name__ == '__main__':
#     main()

import rclpy
from rclpy.node import Node
from geometry_msgs.msg import Twist, Point
from nav_msgs.msg import Odometry, Path
from squaternion import Quaternion
from math import atan2, sqrt, pi
import numpy as np

class PurePursuit(Node):
    def __init__(self):
        super().__init__('pure_pursuit_path_tracking')
        self.cmd_pub = self.create_publisher(Twist, 'cmd_vel', 10)
        self.odom_sub = self.create_subscription(Odometry, '/odom', self.odom_callback, 10)
        self.path_sub = self.create_subscription(Path, '/local_path', self.path_callback, 10)

        self.is_odom = False
        self.is_path = False
        self.odom_msg = Odometry()
        self.path_msg = Path()

        self.lookahead_distance = 1.0  # Lookahead distance 설정, 상황에 맞게 조정
        self.timer = self.create_timer(0.1, self.timer_callback)  # 0.1초마다 timer_callback 실행

    def odom_callback(self, msg):
        self.is_odom = True
        self.odom_msg = msg

    def path_callback(self, msg):
        self.is_path = True
        self.path_msg = msg

    def timer_callback(self):
        if self.is_odom and self.is_path:
            path_points = [pose.pose.position for pose in self.path_msg.poses]
            robot_pose_x = self.odom_msg.pose.pose.position.x
            robot_pose_y = self.odom_msg.pose.pose.position.y

            closest_point, lookahead_point = self.find_lookahead_point(path_points, robot_pose_x, robot_pose_y)

            cmd_msg = Twist()  # cmd_msg를 여기서 초기화

            if lookahead_point is not None:
                robot_orientation_q = self.odom_msg.pose.pose.orientation
                robot_orientation_euler = Quaternion(robot_orientation_q.w, robot_orientation_q.x, robot_orientation_q.y, robot_orientation_q.z).to_euler()
                robot_yaw = robot_orientation_euler[2]

                angle_to_target = atan2(lookahead_point.y - robot_pose_y, lookahead_point.x - robot_pose_x)
                theta = self.normalize_angle(angle_to_target - robot_yaw)

                # cmd_msg.linear.x = 0.5  # 기본 선속도 설정, 상황에 맞게 조정
                # cmd_msg.angular.z = -1.0 * angle_diff  # 회전속도 설정, 상황에 맞게 조정
                if theta > 1.5 or theta < -1.5:
                    cmd_msg.linear.x = 0.0
                    cmd_msg.angular.z = -theta / 5

                elif 0.7 < theta < 1.5 or -1.5 < theta < -0.7:
                    cmd_msg.linear.x = 0.3
                    cmd_msg.angular.z =- theta / 4
                
                elif 0.3 < theta <= 0.7 or -0.7 <= theta < -0.3:
                    cmd_msg.linear.x = 0.5
                    cmd_msg.angular.z =- theta / 3
                else:
                    cmd_msg.linear.x = 1.0
                    cmd_msg.angular.z = - theta


            else:
                # lookahead_point가 None이면, 경로의 끝에 도달했거나 경로가 비어 있음
                cmd_msg.linear.x = 0.0
                cmd_msg.angular.z = 0.0

            self.cmd_pub.publish(cmd_msg)


    def find_lookahead_point(self, path_points, robot_position_x, robot_position_y):
        closest_distance = float('inf')
        lookahead_point = None
        for point in path_points:
            distance = sqrt((point.x - robot_position_x)**2 + (point.y - robot_position_y)**2)
            # 현재 로직을 변경하여 lookahead distance에 더 근접하게 맞춥니다.
            if self.lookahead_distance <= distance < closest_distance:
                closest_distance = distance
                lookahead_point = point

        # 추가 로직: lookahead point가 결정되지 않았다면, 가장 가까운 포인트를 사용
        if lookahead_point is None and path_points:
            min_dist_point = min(path_points, key=lambda point: sqrt((point.x - robot_position_x)**2 + (point.y - robot_position_y)**2))
            if sqrt((min_dist_point.x - robot_position_x)**2 + (min_dist_point.y - robot_position_y)**2) < self.lookahead_distance * 2:
                lookahead_point = min_dist_point

        return None, lookahead_point


    def normalize_angle(self, angle):
        while angle > pi:
            angle -= 2 * pi
        while angle < -pi:
            angle += 2 * pi
        return angle

def main(args=None):
    rclpy.init(args=args)
    pure_pursuit_node = PurePursuit()
    rclpy.spin(pure_pursuit_node)
    pure_pursuit_node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()
