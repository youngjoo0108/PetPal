import rclpy, time, cv2
from rclpy.node import Node

from std_msgs.msg import String
import json
from geometry_msgs.msg import Twist, PoseStamped, Point32
from sensor_msgs.msg import LaserScan
from squaternion import Quaternion
from nav_msgs.msg import Odometry, Path
from std_msgs.msg import Int32

import numpy as np


class TestTracking(Node):

    def __init__(self):
        super().__init__('minimal_subscriber')
        self.yolo_sub = self.create_subscription(
            String,
            'captured_object',
            self.listener_callback,
            10)

        self.goal_pub = self.create_publisher(PoseStamped,'goal_pose', 10)
        self.odom_sub = self.create_subscription(Odometry, '/odom', self.odom_callback, 10)
        self.timer = self.create_timer(1, self.timer_callback)
        self.cmd_pub = self.create_publisher(Twist, 'cmd_vel', 10)
        self.tracking_pub = self.create_publisher(Int32, 'tracking_err', 10)

        self.lidar_sub = self.create_subscription(LaserScan, '/scan', self.lidar_callback, 10)

        self.yolo_sub  # prevent unused variable warning
        self.goal_msg = PoseStamped()
        self.goal_msg.header.frame_id = 'map'
        self.is_odom = False
        self.odom_msg = Odometry()
        self.cmd_msg = Twist()
        self.tracking_err_msg = Int32()
        self.is_dog = False

        self.last_dog_seen_time = 0.0  
        self.dog_seen_timeout = 3.0

        self.robot_pose_x = 0.0
        self.robot_pose_y = 0.0
        self.robot_yaw = 0.0
        self.goal_x = 0.0
        self.goal_y = 0.0
        self.goal_yaw = 0.0
        self.dog_height = 0.0
        self.dog_x_in_camera = 0.0
        self.dog_y_in_camera = 0.0
        self.turtlebot_to_dog_theta = 0.0
        self.turtlebot_to_dog_distance = 0.0

        #lidar callback
        

        # retry

        self.params_cam = {
            "WIDTH": 320,
            "HEIGHT": 240,
            "FOV": 60,
            "X": 0.07,
            "Y": 0,
            "Z": 0.15
        }

        self.params_lidar = {
            "X": 0,
            "Y": 0,
            "Z": 0.19
        }


    def lidar_callback(self, msg):
        if self.is_dog == True:
            possible_list = []
            for angle, r in enumerate(msg.ranges):
                if r < 2:
                    possible_list.append((angle, r))
            print(possible_list)
        
        # for angle,r in enumerate(msg.ranges):
        #     lidar_point = Point32()

        # if 0.0 < r < 12:
        #     lidar_point.x = r*cos(angle*pi/180)
        #     lidar_point.y = r*sin(angle*pi/180)
        #     pcd_msg.points.append(lidar_point)
    
    


    def listener_callback(self, msg):
        data = json.loads(msg.data)
        if 'list' in data:
            for dog in data['list']:
                self.is_dog = True
                self.last_dog_seen_time = time.time()

                left_top = dog.split('/')[-2]
                right_bottom = dog.split('/')[-1]
                left_top_x, left_top_y = map(float, left_top.split('-'))
                right_bottom_x, right_bottom_y = map(float, right_bottom.split('-'))

                self.dog_height = right_bottom_y - left_top_y
                self.dog_x_in_camera = (left_top_x + right_bottom_x) / 2      # 카메라 중심으로부터의 x 거리
                self.dog_y_in_camera = (left_top_y + right_bottom_y) / 2      # 카메라 중심으로부터의 y 거리

                x_lidar, y_lidar = self.transform_camera_to_world(self.dog_x_in_camera, self.dog_y_in_camera)
                # x_lidar, y_lidar = self.pixel_to_3d(self.dog_x_in_camera, self.dog_y_in_camera)

                self.goal_x = x_lidar
                self.goal_y = y_lidar
                # self.goal_x = self.robot_pose_x + x_lidar
                # self.goal_y = self.robot_pose_y + y_lidar
                # print(f"Transformed Lidar Coordinates: x={self.robot_pose_x}, y={self.robot_pose_y}")
                # print(f"x={self.robot_pose_x}, y={self.robot_pose_y} // x={self.goal_x}, y={self.goal_y}")
                



    def rotationMtx(self, yaw, pitch, roll):

        R_x = np.array([[1, 0, 0],
                        [0, np.cos(roll), -np.sin(roll)],
                        [0, np.sin(roll), np.cos(roll)]])
                        
        R_y = np.array([[np.cos(pitch), 0, np.sin(pitch)],
                        [0, 1, 0],
                        [-np.sin(pitch), 0, np.cos(pitch)]])
        
        R_z = np.array([[np.cos(yaw), -np.sin(yaw), 0],
                        [np.sin(yaw), np.cos(yaw), 0],
                        [0, 0, 1]])
                        
        R = np.dot(R_z, np.dot(R_y, R_x))
        return R
    
    
    def translationMtx(self, x, y, z):

        M = np.array([[1, 0, 0, x],
                    [0, 1, 0, y],
                    [0, 0, 1, z],
                    [0, 0, 0, 1]])
        return M
    

    def transform_camera_to_world(self, x_pixel, y_pixel):
        # Step 1: 카메라 내부 파라미터를 사용하여 픽셀 좌표를 카메라 기준의 3D 좌표로 변환
        fov = self.params_cam["FOV"]
        width = self.params_cam["WIDTH"]
        height = self.params_cam["HEIGHT"]
        f = 0.5 * width / np.tan(np.deg2rad(fov / 2))
        cx = width / 2
        cy = height / 2
        depth= 5.0
        
        x_cam = (x_pixel - cx) / f * depth
        y_cam = (y_pixel - cy) / f * depth
        z_cam = depth

        # 카메라 기준 좌표를 로봇 기준 좌표계로 변환 (카메라의 위치 고려)
        x_robot = x_cam + self.params_cam["X"]
        y_robot = y_cam
        z_robot = z_cam + self.params_cam["Z"] - self.params_lidar["Z"]

        # Step 2: 로봇 기준 좌표를 세계 좌표계로 변환 (로봇의 위치와 방향 고려)
        # 로봇의 방향을 고려하여 회전 변환 적용
        x_world = np.cos(self.robot_yaw) * x_robot - np.sin(self.robot_yaw) * y_robot + self.robot_pose_x
        y_world = np.sin(self.robot_yaw) * x_robot + np.cos(self.robot_yaw) * y_robot + self.robot_pose_y

        return x_world, y_world





    def odom_callback(self, msg):
        self.is_odom = True
        self.odom_msg = msg
        q = Quaternion(msg.pose.pose.orientation.w , msg.pose.pose.orientation.x, msg.pose.pose.orientation.y, msg.pose.pose.orientation.z)
        _,_,self.robot_yaw = q.to_euler()
        self.robot_pose_x = self.odom_msg.pose.pose.position.x
        self.robot_pose_y = self.odom_msg.pose.pose.position.y

        

    def timer_callback(self):
        current_time = time.time()
        if self.is_dog and (current_time - self.last_dog_seen_time) > self.dog_seen_timeout:
            # 마지막으로 강아지가 감지된 후 일정 시간이 지났다면
            self.is_dog = False  # 강아지가 더 이상 감지되지 않음으로 표시
            print("강아지 감지 시간 초과 - 강아지가 없습니다.")
            return

        # 강아지가 감지되지 않은 경우 메시지를 발행하지 않음
        if not self.is_dog:
            print("강아지가 감지되지 않았습니다.")
            # self.tracking_err_msg.data = None
            # self.tracking_pub.publish(self.tracking_err_msg)
            return  

        # if self.turtlebot_to_dog_distance < 1.5:
        #     print('short')
        #     if self.turtlebot_to_dog_distance < 0.7 or self.dog_height > 150:
        #         self.tracking_err_msg.data = 4
        #         self.tracking_pub.publish(self.tracking_err_msg)
        #         print('logic0')
        #     else:
        #         if 100 < self.dog_x_in_camera < 220:
        #             print('logic1')
        #             self.tracking_err_msg.data = 1
        #             self.tracking_pub.publish(self.tracking_err_msg)

        #         elif 0 < self.dog_x_in_camera <= 100:
        #             print('logic2')
        #             self.tracking_err_msg.data = 2
        #             self.tracking_pub.publish(self.tracking_err_msg)

        #         elif 220 <= self.dog_x_in_camera < 320:
        #             print('logic3')
        #             self.tracking_err_msg.data = 3
        #             self.tracking_pub.publish(self.tracking_err_msg)
        # else:
        self.goal_msg.pose.position.x = self.goal_x
        self.goal_msg.pose.position.y = self.goal_y
        print(f'tracing {self.goal_x} {self.goal_y}')
        q = Quaternion.from_euler(0, 0, self.goal_yaw)

        self.goal_msg.pose.orientation.x = q.x
        self.goal_msg.pose.orientation.y = q.y
        self.goal_msg.pose.orientation.z = q.z
        self.goal_msg.pose.orientation.w = q.w

        self.goal_msg.header.stamp = rclpy.clock.Clock().now().to_msg()
        self.goal_pub.publish(self.goal_msg)

        self.tracking_err_msg.data = 5
        self.tracking_pub.publish(self.tracking_err_msg)

        

def main(args=None):
    rclpy.init(args=args)
    
    print('yolo sub start')
    yolo_subscriber = TestTracking()

    print('yolo sub run!')
    rclpy.spin(yolo_subscriber)

    yolo_subscriber.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()