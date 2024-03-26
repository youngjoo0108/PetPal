import rclpy, time
from rclpy.node import Node

from std_msgs.msg import String
import json
from geometry_msgs.msg import Twist, PoseStamped, Point32
from sensor_msgs.msg import LaserScan
from squaternion import Quaternion
from nav_msgs.msg import Odometry, Path, OccupancyGrid
from std_msgs.msg import Int32
import pprint
import numpy as np


class Tracking(Node):

    def __init__(self):
        super().__init__('minimal_subscriber')
        self.yolo_sub = self.create_subscription(
            String,
            'captured_object',
            self.listener_callback,
            10)

        self.goal_pub = self.create_publisher(PoseStamped,'goal_pose', 10)
        self.odom_sub = self.create_subscription(Odometry, '/odom', self.odom_callback, 10)
        self.timer = self.create_timer(0.1, self.timer_callback)
        self.cmd_pub = self.create_publisher(Twist, 'cmd_vel', 10)
        self.tracking_pub = self.create_publisher(Int32, 'tracking_err', 10)



        self.yolo_sub
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
                self.dog_x_in_camera = 160 - (left_top_x + right_bottom_x) / 2.0   # 카메라 중심으로부터의 x 거리
                self.dog_y_in_camera = 240 - (left_top_y + right_bottom_y) / 2.0 # 카메라 바닥으로부터의 y 거리
                
                self.dog_distance_in_camera = np.sqrt(self.dog_x_in_camera ** 2 + self.dog_y_in_camera ** 2)

                self.turtlebot_to_dog_theta = np.arctan2(self.dog_x_in_camera * 3, self.dog_y_in_camera * 4)
                self.turtlebot_to_dog_distance = self.dog_distance_in_camera / (self.dog_height * np.cos(self.turtlebot_to_dog_theta))  

                self.goal_x = self.robot_pose_x + (self.turtlebot_to_dog_distance - 1) * np.cos(self.robot_yaw + self.turtlebot_to_dog_theta)
                self.goal_y = self.robot_pose_y + (self.turtlebot_to_dog_distance -1) * np.sin(self.robot_yaw + self.turtlebot_to_dog_theta)
                self.goal_yaw = self.turtlebot_to_dog_theta + self.robot_yaw

                # self.get_logger().info(f'theta: {self.turtlebot_to_dog_theta}, Dog distance: {self.turtlebot_to_dog_distance}, Goal X: {self.goal_x}, Goal Y: {self.goal_y}')
                # self.get_logger().info(f'theta: {self.turtlebot_to_dog_theta}, dog_x: {self.dog_x_in_camera}, dog_y : {self.dog_y_in_camera}')
                
         

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
        else:
            self.tracking_dog()


    def tracking_dog(self):
        if self.turtlebot_to_dog_distance < 2.0:
            print('short')
            if self.turtlebot_to_dog_distance < 0.7 or self.dog_height > 150:
                self.tracking_err_msg.data = 4
                self.tracking_pub.publish(self.tracking_err_msg)
                print('logic0')
            else:
                if 100 < self.dog_x_in_camera < 220:
                    print('logic1')
                    self.tracking_err_msg.data = 1
                    # self.tracking_err_msg.data = None
                    self.tracking_pub.publish(self.tracking_err_msg)
                    return
                    
                elif 0 < self.dog_x_in_camera <= 100:
                    print('logic2')
                    self.tracking_err_msg.data = 2
                    self.tracking_pub.publish(self.tracking_err_msg)
                    

                elif 220 <= self.dog_x_in_camera < 320:
                    print('logic3')
                    self.tracking_err_msg.data = 3
                    self.tracking_pub.publish(self.tracking_err_msg)
        else:
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
        return



def main(args=None):
    rclpy.init(args=args)
    
    print('yolo sub start')
    yolo_subscriber = Tracking()

    print('yolo sub run!')
    rclpy.spin(yolo_subscriber)

    yolo_subscriber.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()