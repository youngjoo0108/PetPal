import rclpy
from rclpy.node import Node
from geometry_msgs.msg import Twist

class stop(Node):

  def __init__(self):
    super().__init__('stop')
    self.cmd_publisher = self.create_publisher(Twist, 'cmd_vel', 10)
    self.timer = self.create_timer(0.1, self.timer_callback)

    self.cmd_msg = Twist()
    
  def timer_callback(self):
    self.cmd_msg.linear.x = 0.0
    self.cmd_msg.angular.z = 0.0

    self.cmd_publisher.publish(self.cmd_msg)


def main(args = None):
  rclpy.init(args=args)
  stay = stop()
  rclpy.spin(stay)
  stay.destroy_node()
  rclpy.shutdown()

if __name__ == '__main__':
  main()