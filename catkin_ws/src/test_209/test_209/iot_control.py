import rclpy
from rclpy.node import Node
from std_msgs.msg import String, Int32
import numpy as np
from ssafy_bridge.iot_udp import iot_udp
from nav_msgs.msg import Odometry, Path
from ssafy_msgs.msg import IotInfo
from geometry_msgs.msg import PoseStamped

class device(Node):

    def __init__(self):
        super().__init__('device')

        self.iot_sub = self.create_subscription(IotInfo, '/iot', self.iot_callback, 10)
        self.odom_sub = self.create_subscription(Odometry, '/odom', self.odom_callback, 1)
        self.iot_cmd_sub = self.create_subscription(Int32, '/iot_cmd', self.iot_cmd_callback, 10)
        self.path_sub = self.create_subscription(Path, '/local_path', self.path_callback, 10)
        self.goal_pub = self.create_publisher(PoseStamped, 'goal_pose', 10)
        self.timer = self.create_timer(0.1, self.timer_callback)

        self.iot_control = iot_udp()
        self.devices = {}
        self.device_uid = []
        self.now_device = None

        self.iot_msg = IotInfo()
        self.odom_msg = Odometry()
        self.goal_msg = PoseStamped()
        self.goal_msg.header.frame_id = 'map'
        self.path_msg = Path()

        self.is_odom = False
        self.is_iot = False
        self.is_path = False
        self.is_state_change = True

        full_path = 'C:\\Users\\SSAFY\\Desktop\\iot.txt'
        self.f = open(full_path, 'r+')

        lines = self.f.readlines()
        self.f.seek(0,2)

        for data in lines:
            line_data = data.split()
            self.devices[line_data[0]] = (line_data[1], line_data[2])
            self.device_uid.append(line_data[0])

    def iot_callback(self, msg):
        self.iot_msg = msg
        self.is_iot = True

        if self.is_odom:
            if not msg.uid in self.devices:
                x = self.odom_msg.pose.pose.position.x
                y = self.odom_msg.pose.pose.position.y
                self.devices[msg.uid] = (x, y)
                self.device_uid.append(msg.uid)
                self.f.write('{0} {1} {2}\n'.format(msg.uid, x, y))

    def odom_callback(self, msg):
        self.is_odom = True
        self.odom_msg = msg

    def iot_cmd_callback(self, msg):
        if self.is_odom:
            if msg.data >= len(self.devices):
                print('no device', len(self.devices))
            else:
                self.is_state_change = False
                self.now_device = self.device_uid[msg.data]
                

    def path_callback(self, msg):
        self.is_path = True
        self.path_msg = msg

    def timer_callback(self):
        if self.is_iot and self.is_state_change == False:
            if self.now_device == self.iot_msg.uid:
                self.iot_control.all_procedures(self.now_device)
                self.is_state_change = True
                self.now_device = None
            else:
                goal = self.devices[self.now_device]
                print(goal)
                self.goal_msg.pose.position.x = float(goal[0])
                self.goal_msg.pose.position.y = float(goal[1])

                self.goal_msg.pose.orientation.x = 0.0
                self.goal_msg.pose.orientation.y = 0.0
                self.goal_msg.pose.orientation.z = 0.0
                self.goal_msg.pose.orientation.w = 1.0

                self.goal_msg.header.stamp = rclpy.clock.Clock().now().to_msg()
                self.goal_pub.publish(self.goal_msg)


def main(args=None):
    rclpy.init(args=args)
    try :
        device_control = device()
        rclpy.spin(device_control)
        device_control.destroy_node()
        rclpy.shutdown()
    except :
        device_control.f.close()

if __name__ == '__main__':
    main()