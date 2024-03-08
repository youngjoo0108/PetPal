import rclpy
from rclpy.node import Node
from geometry_msgs.msg import Twist
from nav_msgs.msg import Odometry, Path
from squaternion import Quaternion
from math import atan2, sqrt

class PurePursuit(Node):
    def __init__(self):
        super().__init__('pure_pursuit_path_tracking')
        self.cmd_pub = self.create_publisher(Twist, 'cmd_vel', 10)
        self.odom_sub = self.create_subscription(Odometry, '/odom', self.odom_callback, 10)
        self.path_sub = self.create_subscription(Path, '/local_path', self.path_callback, 10)

        self.is_odom = False
        self.is_path = False
        self.odom_msg = Odometry()
        self.path_msg = Path()

        self.lookahead_distance = 1.0  # Lookahead distance 설정, 상황에 맞게 조정

    def odom_callback(self, msg):
        self.is_odom = True
        self.odom_msg = msg

    def path_callback(self, msg):
        self.is_path = True
        self.path_msg = msg

    def get_nearest_point_index(self, robot_position, path_points):
        closest_point_index = 0
        closest_distance = float('inf')

        for i, point in enumerate(path_points):
            distance = sqrt((point.x - robot_position.x)**2 + (point.y - robot_position.y)**2)
            if distance < closest_distance:
                closest_point_index = i
                closest_distance = distance
        
        return closest_point_index

    def get_lookahead_point(self, start_index, path_points):
        for i in range(start_index, len(path_points)):
            distance = sqrt((path_points[i].x - self.odom_msg.pose.pose.position.x)**2 + (path_points[i].y - self.odom_msg.pose.pose.position.y)**2)
            if distance >= self.lookahead_distance:
                return path_points[i]
        return None

    def timer_callback(self):
        if self.is_odom and self.is_path:
            path_points = [pose.pose.position for pose in self.path_msg.poses]
            robot_position = self.odom_msg.pose.pose.position

            closest_point_index = self.get_nearest_point_index(robot_position, path_points)
            lookahead_point = self.get_lookahead_point(closest_point_index, path_points)

            if lookahead_point is not None:
                robot_orientation_q = self.odom_msg.pose.pose.orientation
                robot_orientation_euler = Quaternion(robot_orientation_q.w, robot_orientation_q.x, robot_orientation_q.y, robot_orientation_q.z).to_euler()
                robot_yaw = robot_orientation_euler[2]

                angle_to_target = atan2(lookahead_point.y - robot_position.y, lookahead_point.x - robot_position.x)
                angle_diff = (angle_to_target - robot_yaw)

                cmd_msg = Twist()
                cmd_msg.linear.x = 0.5  # 기본 선속도 설정, 상황에 맞게 조정
                cmd_msg.angular.z = 1.5 * angle_diff  # 회전속도 설정, 상황에 맞게 조정

                self.cmd_pub.publish(cmd_msg)

    def run(self):
        self.timer = self.create_timer(0.1, self.timer_callback)  # 0.1초마다 timer_callback 실행

def main(args=None):
    rclpy.init(args=args)
    pure_pursuit_node = PurePursuit()
    rclpy.spin(pure_pursuit_node)
    pure_pursuit_node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()
