import rclpy
from rclpy.node import Node

from std_msgs.msg import String


class YoloSubscriber(Node):

    def __init__(self):
        super().__init__('minimal_subscriber')
        self.subscription = self.create_subscription(
            String,
            'captured_object',
            self.listener_callback,
            10)
        self.subscription  # prevent unused variable warning

    def listener_callback(self, msg):
        #
        self.get_logger().info('Yolo Subscriber heards: "%s"' % msg.data)


def main(args=None):
    rclpy.init(args=args)

    yolo_subscriber = YoloSubscriber()

    rclpy.spin(yolo_subscriber)

    # Destroy the node explicitly
    # (optional - otherwise it will be done automatically
    # when the garbage collector destroys the node object)
    yolo_subscriber.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()