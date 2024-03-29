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
from ros_log_package.RosLogPublisher import RosLogPublisher

class Tracking(Node):

    def __init__(self):
        super().__init__('minimal_subscriber')
        self.yolo_sub = self.create_subscription(String,'captured_object',self.listener_callback, 10)
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
        self.dog_seen_timeout = 5.0

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
        
        # log
        self.ros_log_pub = None
        try:
            self.ros_log_pub = RosLogPublisher(self)
        except Exception as e:
            self.get_logger().error('Subscription initialization error: {}'.format(e))
    

    def listener_callback(self, msg):
        data = json.loads(msg.data)
        if 'dog_list' in data:
            for dog in data['dog_list']:
                self.is_dog = True
                self.last_dog_seen_time = time.time()

                left_top = dog.split('/')[-2]
                right_bottom = dog.split('/')[-1]
                left_top_x, left_top_y = map(float, left_top.split('-'))
                right_bottom_x, right_bottom_y = map(float, right_bottom.split('-'))

                self.dog_height = right_bottom_y - left_top_y
                self.dog_x_in_camera = 160 - (left_top_x + right_bottom_x) / 2.0     # 카메라 중심으로부터의 x 거리
                self.dog_y_in_camera = 240 - (left_top_y + right_bottom_y) / 2.0     # 카메라 바닥으로부터의 y 거리
                
                self.dog_distance_in_camera = np.sqrt(self.dog_x_in_camera ** 2 + self.dog_y_in_camera ** 2)

                self.turtlebot_to_dog_theta = np.arctan2(self.dog_x_in_camera * 3, self.dog_y_in_camera * 4)
                self.turtlebot_to_dog_distance = self.dog_distance_in_camera / (self.dog_height * np.cos(self.turtlebot_to_dog_theta))  

                self.goal_x = self.robot_pose_x + (self.turtlebot_to_dog_distance - 1.5) * np.cos(self.robot_yaw + self.turtlebot_to_dog_theta)
                self.goal_y = self.robot_pose_y + (self.turtlebot_to_dog_distance -1.5) * np.sin(self.robot_yaw + self.turtlebot_to_dog_theta)
                self.goal_yaw = self.turtlebot_to_dog_theta + self.robot_yaw

         
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
            self.is_dog = False 
            self.ros_log_pub.publish_log('DEBUG', 'Subscription tracking: Cannot find Dog for 5 seconds')
            return

        if not self.is_dog:
            # print("강아지가 감지되지 않았습니다.")
            return  
        else:
            self.tracking_dog()


    def tracking_dog(self):
        if self.turtlebot_to_dog_distance < 1.3 or self.dog_height > 120:

            if self.turtlebot_to_dog_distance < 0.7 or self.dog_height > 150:

                self.tracking_err_msg.data = 4
                self.tracking_pub.publish(self.tracking_err_msg)
                
            else:
                if -100 < self.dog_x_in_camera < 100:

                    self.tracking_err_msg.data = 1
                    self.tracking_pub.publish(self.tracking_err_msg)
                    return
                    
                elif -160 < self.dog_x_in_camera <= -100:

                    self.tracking_err_msg.data = 2
                    self.tracking_pub.publish(self.tracking_err_msg)
                    

                elif 100 <= self.dog_x_in_camera < 160:

                    self.tracking_err_msg.data = 3
                    self.tracking_pub.publish(self.tracking_err_msg)
        else:
            
            self.goal_msg.pose.position.x = self.goal_x
            self.goal_msg.pose.position.y = self.goal_y
            print(f'tracing {self.goal_x} {self.goal_y} {self.turtlebot_to_dog_distance}')
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