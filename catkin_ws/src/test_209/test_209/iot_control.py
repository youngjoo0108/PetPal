import rclpy, json
from rclpy.node import Node
from std_msgs.msg import String, Int32
import numpy as np
from nav_msgs.msg import Odometry, Path
from ssafy_msgs.msg import IotInfo, IotCmd
from geometry_msgs.msg import PoseStamped

class iotControl(Node):

    def __init__(self):
        super().__init__('iot_control')
        
        self.iot_sub = self.create_subscription(IotInfo, '/iot', self.iot_callback, 10)
        self.odom_sub = self.create_subscription(Odometry, '/odom', self.odom_callback, 1)
        self.iot_cmd_sub = self.create_subscription(IotCmd, '/iot_cmd', self.iot_cmd_callback, 10)
        self.goal_pub = self.create_publisher(PoseStamped, 'goal_pose', 10)
        self.request_pub = self.create_publisher(String, 'request', 10)
        self.data_pub = self.create_publisher(String, '/to_server/data', 10)
        self.iot_user_pub = self.create_publisher(IotCmd, 'iot_user', 10)
        self.timer = self.create_timer(0.1, self.timer_callback)

        self.devices = {}
        self.device_uid = []
        self.now_device = None

        self.iot_msg = IotInfo()
        self.odom_msg = Odometry()
        self.goal_msg = PoseStamped()
        self.goal_msg.header.frame_id = 'map'
        self.request_msg = String()
        self.data_msg = String()

        self.is_odom = False
        self.is_path = False
        self.is_state_change = True

        full_path = 'C:\\Users\\SSAFY\\Desktop\\iot.txt'
        f = open(full_path, 'r')

        lines = f.readlines()

        for data in lines:
            line_data = data.split()
            self.devices[line_data[0]] = (line_data[1], line_data[2])
            self.device_uid.append(line_data[0])
        
        f.close()

    def iot_callback(self, msg):
        self.iot_msg = msg

        # if self.is_odom:
        #     if not msg.uid in self.devices:
        #         x = self.odom_msg.pose.pose.position.x
        #         y = self.odom_msg.pose.pose.position.y
        #         self.devices[msg.uid] = (x, y)
        #         self.device_uid.append(msg.uid)
        #         self.f.write('{0} {1} {2}\n'.format(msg.uid, x, y))

    def odom_callback(self, msg):
        self.is_odom = True
        self.odom_msg = msg

    def iot_cmd_callback(self, msg):
        if self.is_odom:
            self.now_device = msg.iot_uuid
            self.cmd = msg.control_action

            if self.cmd == "register":
                if not self.iot_msg.uid in self.devices:
                    x = self.odom_msg.pose.pose.position.x
                    y = self.odom_msg.pose.pose.position.y
                    self.devices[self.iot_msg.uid] = (x, y)
                    self.device_uid.append(self.iot_msg.uid)
                    # self.f.write('{0} {1} {2}\n'.format(self.iot_msg.uid, x, y))
                
                temp = {
                    'type' : 'REGISTER',
                    'message' : self.iot_msg.uid
                }
                data = json.dumps(temp)
                self.data_msg.data = data
                self.data_pub.publish(self.data_msg)
            else:
                self.is_state_change = False
                self.request_msg.data = "iot_on"
                self.request_pub.publish(self.request_msg)
                


    def timer_callback(self):

        if self.is_state_change == False:
            if self.now_device == self.iot_msg.uid:
                msg = IotCmd()
                msg.iot_uuid = self.now_device
                msg.control_action = self.cmd
                self.iot_user_pub.publish(msg)
                # self.iot_control.user_cmd(self.now_device, self.cmd)
                self.is_state_change = True
                self.now_device = None

                temp = {
                    'type' : 'ACOMPLETE',
                    'message' : ""
                }
                data = json.dumps(temp)
                self.data_msg.data = data
                self.data_pub.publish(self.data_msg)

                self.request_msg.data = "iot_off"
                self.request_pub.publish(self.request_msg)
            else:
                goal = self.devices[self.now_device]
                #print(goal)
                self.goal_msg.pose.position.x = float(goal[0])
                self.goal_msg.pose.position.y = float(goal[1])

                self.goal_msg.pose.orientation.x = 0.0
                self.goal_msg.pose.orientation.y = 0.0
                self.goal_msg.pose.orientation.z = 0.0
                self.goal_msg.pose.orientation.w = 1.0

                self.goal_msg.header.stamp = rclpy.clock.Clock().now().to_msg()
                self.goal_pub.publish(self.goal_msg)

    def save_iot(self):
        full_path = 'C:\\Users\\SSAFY\\Desktop\\iot.txt'
        f = open(full_path, 'w')
        
        temp = ''
        for key,value in self.devices.items():
            temp += '{0} {1} {2}\n'.format(key, value[0], value[1])
        f.write(temp)
        f.close()

def main(args=None):
    rclpy.init(args=args)
    device_control = iotControl()
    try :
        rclpy.spin(device_control)
        device_control.destroy_node()
        rclpy.shutdown()
    except :
        device_control.save_iot()

if __name__ == '__main__':
    main()