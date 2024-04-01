import rclpy
from rclpy.node import Node

from std_msgs.msg import String
import json


class YoloSubscriber(Node):

    def __init__(self):
        super().__init__('minimal_subscriber')
        self.subscription = self.create_subscription(
            String,
            'captured_object',
            self.listener_callback,
            10)
        self.subscription  # prevent unused variable+warning

    def listener_callback(self, msg):
        # print(msg.data, '\n---------')
        
        data = json.loads(msg.data)
        for i in data['obstacle_list']:
            print('Obstacle :', i)
        for i in data['furniture_list']:
            print('Furniture :', i)
        for i in data['dog_list']:
            print('Dog :', i)
        for i in data['human_list']:
            print('Human :', i)
        for i in data['iot_list']:
            print('Iot :', i)
        print()


def main(args=None):
    rclpy.init(args=args)
    
    print('yolo sub start')
    yolo_subscriber = YoloSubscriber()

    print('yolo sub run!')
    rclpy.spin(yolo_subscriber)

    # Destroy the node explicitly
    # (optional - otherwise it will be done automatically
    # when the garbage collector destroys the node object)
    yolo_subscriber.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()