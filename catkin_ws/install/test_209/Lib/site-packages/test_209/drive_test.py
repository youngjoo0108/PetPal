import rclpy
from rclpy.node import Node
from geometry_msgs.msg import Point32, Twist
from sensor_msgs.msg import LaserScan, PointCloud
from math import pi,cos,sin
class driving(Node):

  def __init__(self):
    super().__init__('driving')
    self.lidar_sub = self.create_subscription(LaserScan, '/scan', self.lidar_callback, 10)
    self.cmd_publisher = self.create_publisher(Twist, 'cmd_vel', 10)
    self.timer = self.create_timer(0.1, self.timer_callback)

    self.cmd_msg = Twist()

    self.is_collision = False
    self.handle_direction = False

  def check_collision(self, msg):
    for angle,r in enumerate(msg.ranges):
      
      if 0 <= angle < 10 or angle > 350:
        if 0.0 < r < 1.5:
          return True
    return False

  def lidar_callback(self, msg):
    self.is_collision = self.check_collision(msg)

    tempL = 0
    tempR = 0
    for angle,r in enumerate(msg.ranges):
      if 88 <= angle <= 92:
        tempL += r
      elif 268 <= angle <= 272:
        tempR += r
    
    if tempL <= tempR:
      self.handle_direction = True
    else:
      self.handle_direction = False
    #   if 0 <= angle < 10 or angle > 350:
    #     if 0.0 < r < 1.0:
    #       self.is_collision = True

  def timer_callback(self):
    
    if self.is_collision:
      self.cmd_msg.linear.x = 0.0

      if self.handle_direction:
        self.cmd_msg.angular.z = 0.2
      else:
        self.cmd_msg.angular.z = -0.2
    else:
      self.cmd_msg.linear.x = 1.0
      self.cmd_msg.angular.z = 0.0

    self.cmd_publisher.publish(self.cmd_msg)



def main(args = None):
  rclpy.init(args=args)
  drive_test = driving()
  rclpy.spin(drive_test)
  drive_test.destroy_node()
  rclpy.shutdown()

if __name__ == '__main__':
  main()