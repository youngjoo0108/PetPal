import rclpy
from rclpy.node import Node

from std_msgs.msg import String
import json
from geometry_msgs.msg import Twist, PoseStamped
from squaternion import Quaternion
from nav_msgs.msg import Odometry, Path
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
        self.timer = self.create_timer(0.5, self.timer_callback)


        self.yolo_sub  # prevent unused variable warning
        self.goal_msg = PoseStamped()
        self.goal_msg.header.frame_id = 'map'
        self.is_odom = False
        self.odom_msg = Odometry()

        self.robot_pose_x = 0.0
        self.robot_pose_y = 0.0
        self.robot_yaw = 0.0
        self.goal_x = 0.0
        self.goal_y = 0.0


    def listener_callback(self, msg):
        data = json.loads(msg.data)
        for dog in data['list']:
            #print(dog)
            # self.get_logger().info('"%s"' % dog)

            left_top = dog.split('/')[-2]
            left_top_x, left_top_y = map(int, left_top.split('-'))

            right_bottom = dog.split('/')[-1]
            right_bottom_x, right_bottom_y = map(int, right_bottom.split('-'))

            dog_height = right_bottom_y - left_top_y
            dog_x_in_camera = (left_top_x + right_bottom_x) / 2
            dog_y_in_camera = 240 - (left_top_y + right_bottom_y) / 2

            turtlebot_to_dog_theta = np.arctan((dog_y_in_camera - dog_x_in_camera) / dog_y_in_camera)
            turtlebot_to_dog_distance = 130 / (dog_height * np.cos(turtlebot_to_dog_theta))
            
            self.goal_x = self.robot_pose_x + turtlebot_to_dog_distance * np.cos(self.robot_yaw + turtlebot_to_dog_theta)
            self.goal_y = self.robot_pose_y + turtlebot_to_dog_distance * np.sin(self.robot_yaw + turtlebot_to_dog_theta)

            # self.get_logger().info(str(dog_height))
            # self.get_logger().info(str(dog_x_in_camera))
            # self.get_logger().info(str(dog_y_in_camera))
            # self.get_logger().info(str(turtlebot_to_dog_theta * 180 / np.pi))
            # self.get_logger().info(str(turtlebot_to_dog_distance))
            self.get_logger().info(str(self.goal_x))
            self.get_logger().info(str(self.goal_y))



    def odom_callback(self, msg):
        self.is_odom = True
        self.odom_msg = msg
        q = Quaternion(msg.pose.pose.orientation.w , msg.pose.pose.orientation.x, msg.pose.pose.orientation.y, msg.pose.pose.orientation.z)
        _,_,self.robot_yaw = q.to_euler()
        self.robot_pose_x = self.odom_msg.pose.pose.position.x
        self.robot_pose_y = self.odom_msg.pose.pose.position.y


    def timer_callback(self):
        self.goal_msg.pose.position.x = self.goal_x
        self.goal_msg.pose.position.y = self.goal_y

        self.goal_msg.pose.orientation.x = 0.0
        self.goal_msg.pose.orientation.y = 0.0
        self.goal_msg.pose.orientation.z = 0.0
        self.goal_msg.pose.orientation.w = 1.0

        # print(self.goal)
        self.goal_msg.header.stamp = rclpy.clock.Clock().now().to_msg()
        self.goal_pub.publish(self.goal_msg)
        

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