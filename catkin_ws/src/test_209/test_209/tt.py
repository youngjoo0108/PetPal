import rclpy, json
from rclpy.node import Node
import ros2pkg
from geometry_msgs.msg import Twist,PoseStamped,Pose,TransformStamped
from ssafy_msgs.msg import TurtlebotStatus
from sensor_msgs.msg import Imu,LaserScan
from std_msgs.msg import Float32, Int32, String
from squaternion import Quaternion
from nav_msgs.msg import Odometry,Path,OccupancyGrid,MapMetaData
from math import pi,cos,sin,sqrt
import tf2_ros
import os
import test_209.utils as utils
from test_209.make_route import makeRoute
import numpy as np
import cv2
import time


class loadMap(Node):

    def __init__(self):
        super().__init__('load_map')
        self.sock_pub = self.create_publisher(String, '/to_server/data', 10)
        
        self.timer = self.create_timer(1, self.timer_callback)
        self.is_odom = False

        self.map_msg=OccupancyGrid()
        self.map_size_x=700 
        self.map_size_y=700
        self.map_resolution=0.05
        # self.map_offset_x = -8 - (self.map_size_x * self.map_resolution) / 2
        # self.map_offset_y = -4 - (self.map_size_y * self.map_resolution) / 2
        self.map_data = [0 for i in range(self.map_size_x*self.map_size_y)]

        self.map_msg.header.frame_id="map"

        self.read_txt()

    def read_txt(self):
        full_path = 'C:\\Users\\SSAFY\\Desktop\\\S10P22A209\\catkin_ws\\src\\test_209\\map\\map.txt'
        self.f = open(full_path, 'r')
        
        lines = self.f.readlines()
        
        data_json = {
                'type': 'COMPLETE',
                'message': lines,
                }
        dt = json.dumps(data_json)
        msg = String()
        msg.data = dt
        self.sock_pub.publish(msg)


    def timer_callback(self):
        if self.is_odom:
            self.map_msg.header.stamp =rclpy.clock.Clock().now().to_msg()
            self.map_pub.publish(self.map_msg)

       
def main(args=None):
    rclpy.init(args=args)

    load_map = loadMap()
    rclpy.spin(load_map)
    load_map.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()