import rclpy
from rclpy.node import Node
from geometry_msgs.msg import Twist
from ssafy_msgs.msg import TurtlebotStatus

class Communicator(Node):
    def __init__(self):
        super().__init__('Communicator')
        self.cmd_publisher = self.create_publisher(Twist, 'cmd_vel', 10)
        self.turtlebot_status_sub = self.create_subscription(TurtlebotStatus, '/turtlebot_status', self.status_callback, 10)
        self.timer = self.create_timer(0.1, self.timer_callback)

        self.cmd_msg = Twist()
        self.turtlebot_status_msg = TurtlebotStatus()

    def status_callback(self, msg):
        print('linear velocity :{0} , Angular V : {1} Battery : {2}'.format(msg.twist.linear.x, msg.twist.angular.z, msg.battery_percentage))

    def timer_callback(self):
        self.cmd_msg.linear.x = 2.0
        self.cmd_msg.angular.z = 1.8

        self.cmd_publisher.publish(self.cmd_msg)

def main(args=None):
    rclpy.init(args=args)
    com = Communicator()
    rclpy.spin(com)
    com.destroy_node()
    rclpy.shutdown()

if __name__ == "__main__":
    main()