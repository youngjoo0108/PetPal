import rclpy, json
from rclpy.node import Node
from std_msgs.msg import String, Int32
from ssafy_msgs.msg import IotCmd
import numpy as np

class controlDevice(Node):

    def __init__(self):
        super().__init__('control')

        self.sock_pub = self.create_publisher(String, '/to_server/data', 10)

        while True:
            menu=input('test : ')
            data_json = {
                'type': 'COMPLETE',
                'message': menu
                }
            temp = json.dumps(data_json)
            msg = String()
            msg.data = temp
            self.sock_pub.publish(msg)

def main(args=None):
    rclpy.init(args=args)
    control_device = controlDevice()
    rclpy.spin(control_device)
    control_device.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()