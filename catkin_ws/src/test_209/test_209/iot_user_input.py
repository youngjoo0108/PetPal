import rclpy
from rclpy.node import Node
from std_msgs.msg import String, Int32
import numpy as np

class controlDevice(Node):

    def __init__(self):
        super().__init__('control')

        self.c_pub = self.create_publisher(Int32, 'iot_cmd', 10)
        self.c_msg = Int32()

        while True:
            menu=int(input('제어할 가전 번호 : '))
            self.c_msg.data = menu
            self.c_pub.publish(self.c_msg)

def main(args=None):
    rclpy.init(args=args)
    control_device = controlDevice()
    rclpy.spin(control_device)
    control_device.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()