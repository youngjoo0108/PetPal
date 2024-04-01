import rclpy, time
from rclpy.node import Node
from geometry_msgs.msg import Twist, Point, PoseStamped
from sensor_msgs.msg import LaserScan
from nav_msgs.msg import Odometry, Path
from std_msgs.msg import Int32, String
from squaternion import Quaternion
from math import atan2, sqrt, pi
import numpy as np
from ros_log_package.RosLogPublisher import RosLogPublisher

class PurePursuit(Node):
    def __init__(self):
        super().__init__('pure_pursuit_path_tracking')
        self.fsm_sub = self.create_subscription(String, '/fsm', self.fsm_callback, 10)
        self.cmd_pub = self.create_publisher(Twist, 'cmd_vel', 10)
        self.odom_sub = self.create_subscription(Odometry, '/odom', self.odom_callback, 10)
        self.path_sub = self.create_subscription(Path, '/local_path', self.path_callback, 1)
        self.lidar_sub = self.create_subscription(LaserScan, '/scan', self.lidar_callback, 10)
        self.tracking_sub = self.create_subscription(Int32, 'tracking_err', self.tracking_err_callback, 1)
        self.scan_sub = self.create_subscription(Int32, '/err', self.scan_err_callback, 1)
        self.patrol_pub = self.create_publisher(Int32, 'patrol', 1)
        self.timer = self.create_timer(0.05, self.timer_callback)

        self.collision = False
        self.is_fsm = False
        self.is_odom = False
        self.is_path = False
        self.is_tracking_err = False
        self.is_goal = False

        self.fsm_msg = String()
        self.odom_msg = Odometry()
        self.path_msg = Path()
        self.lidar_msg = LaserScan()
        self.tracking_err_msg = Int32()
        self.scan_err_msg = Int32()
        self.cmd_msg = Twist()
        self.patrol_msg = Int32()

        self.lookahead_distance = 0.5

        # log
        self.ros_log_pub = None
        try:
            self.ros_log_pub = RosLogPublisher(self)
        except Exception as e:
            self.get_logger().error('Subscription initialization error: {}'.format(e))

    def fsm_callback(self, msg):
        self.is_fsm = True
        self.fsm_msg = msg

    def odom_callback(self, msg):
        self.is_odom = True
        self.odom_msg = msg


    def path_callback(self, msg):
        self.is_path = True
        self.path_msg = msg


    def check_collision(self, msg):
        for angle,r in enumerate(msg.ranges):
            if angle < 25 or angle > 335:
                if 0.0 < r < 0.2:
                    self.ros_log_pub.publish_log('DEBUG', 'Subscription PurePursuit : collsion occur')
                    return True
        return False
    

    def tracking_err_callback(self, msg):
        self.tracking_err_msg = msg
        self.is_tracking_err = True
    
    def scan_err_callback(self, msg):
        self.scan_err_msg = msg

    def lidar_callback(self, msg):
        self.lidar_msg = msg

        if self.is_path == True and self.is_odom == True:
            self.collision = self.check_collision(msg)
            self.is_lidar = True


    def timer_callback(self):
        # if not self.is_fsm or self.is_goal:
        #     return
        if self.fsm_msg.data == "stay":
            self.cmd_msg.linear.x = 0.0
            self.cmd_msg.angular.z = 0.0

        elif self.fsm_msg.data == "tracking" and self.is_tracking_err:
           
            if self.tracking_err_msg.data == 4:
                self.cmd_msg.linear.x = -1.0
                self.cmd_msg.angular.z = 0.0
                #self.cmd_pub.publish(self.cmd_msg)
                self.ros_log_pub.publish_log('DEBUG', 'Subscription PurePursuit_tracking : distance too short')
            
            if self.tracking_err_msg.data == 1:
                self.cmd_msg.linear.x = 0.0
                self.cmd_msg.angular.z = 0.0
                #self.cmd_pub.publish(self.cmd_msg)
                self.tracking_err_msg.data = False
                self.ros_log_pub.publish_log('DEBUG', 'Subscription PurePursuit_tracking : distance moderate, stop')
            
            elif self.tracking_err_msg.data == 2:
                self.cmd_msg.linear.x = 0.0
                self.cmd_msg.angular.z = 0.05
                #self.cmd_pub.publish(self.cmd_msg)
                # self.ros_log_pub.publish_log('DEBUG', 'Subscription PurePursuit_tracking : distance moderate, move clockwise')
           
            else:
                self.cmd_msg.linear.x = 0.0
                self.cmd_msg.angular.z = -0.05
                #self.cmd_pub.publish(self.cmd_msg)
                # self.ros_log_pub.publish_log('DEBUG', 'Subscription PurePursuit_tracking : distance moderate, move counterclockwise')
            
            self.is_tracking_err = False

        elif self.fsm_msg.data == "scan" and self.scan_err_msg.data != 0:
            if self.scan_err_msg.data == 1 or self.scan_err_msg.data == 4:
                self.cmd_msg.linear.x = 0.0
                self.cmd_msg.angular.z = 0.2

            elif self.scan_err_msg.data == 2:
                self.lidar_check_move()

            # elif self.scan_err_msg.data == 3:
            #     self.lidar_check_move()

            elif self.scan_err_msg.data == 100:
                self.cmd_msg.linear.x = 0.0
                self.cmd_msg.angular.z = 0.0
                self.is_goal = True
        
        else:
            if self.is_odom and self.is_path:
                path_points = [pose.pose.position for pose in self.path_msg.poses]
                robot_pose_x = self.odom_msg.pose.pose.position.x
                robot_pose_y = self.odom_msg.pose.pose.position.y

                lookahead_point = self.find_lookahead_point(path_points, robot_pose_x, robot_pose_y)
            
                if lookahead_point is not None:
                    if self.fsm_msg.data == "patrol":
                        self.is_goal = False
                    robot_orientation_q = self.odom_msg.pose.pose.orientation
                    robot_orientation_euler = Quaternion(robot_orientation_q.w, robot_orientation_q.x, robot_orientation_q.y, robot_orientation_q.z).to_euler()
                    robot_yaw = robot_orientation_euler[2]

                    angle_to_target = atan2(lookahead_point.y - robot_pose_y, lookahead_point.x - robot_pose_x)
                    theta = self.normalize_angle(angle_to_target - robot_yaw) * -1

                    if self.fsm_msg.data == "scan" and self.collision:
                        if theta < 0:
                            self.cmd_msg.linear.x = 0.0
                            self.cmd_msg.angular.z = -0.2
                        else:
                            self.cmd_msg.linear.x = 0.0
                            self.cmd_msg.angular.z = 0.2

                    elif self.collision:
                        start_time = time.time()  # 현재 시간 기록
                        while True:
                            if time.time() - start_time < 1:  # 1초 동안 실행
                                self.cmd_msg.linear.x = -0.2
                                # print('후진중!!')
                            else:
                                self.cmd_msg.linear.x = 0.0
                                self.cmd_pub.publish(self.cmd_msg)

                                break
                            self.cmd_pub.publish(self.cmd_msg)

                        self.cmd_msg.linear.x = 0.0
                        self.cmd_pub.publish(self.cmd_msg)
                        return

                    else:
                        if theta > 1.5 or theta < -1.5:
                            self.cmd_msg.linear.x = 0.0
                            self.cmd_msg.angular.z = theta/2

                        elif 0.7 < theta < 1.5 or -1.5 < theta < -0.7:
                            self.cmd_msg.linear.x = 0.2
                            self.cmd_msg.angular.z = theta/3
                        
                        elif 0.2 < theta <= 0.7 or -0.7 <= theta < -0.2:
                            self.cmd_msg.linear.x = 0.5
                            self.cmd_msg.angular.z = theta/4

                        else:
                            if 0.2 < self.lidar_msg.ranges[0]/5 < 1.0:
                                self.cmd_msg.linear.x = self.lidar_msg.ranges[0]/5
                            elif self.lidar_msg.ranges[0]/5 > 1.0:
                                self.cmd_msg.linear.x = 1.0
                            else:
                                self.cmd_msg.linear.x = 0.2
                            self.cmd_msg.angular.z = theta/5

                else:
                    self.cmd_msg.linear.x = 0.0
                    self.cmd_msg.angular.z = 0.0
                    if self.fsm_msg.data == "patrol" and self.is_goal == False:
                        self.patrol_msg.data = 1
                        self.is_goal = True
                        self.patrol_pub.publish(self.patrol_msg)

        self.cmd_pub.publish(self.cmd_msg)


    def find_lookahead_point(self, path_points, robot_position_x, robot_position_y):
        closest_distance = float('inf')
        lookahead_point = None
        for point in path_points:
            distance = sqrt((point.x - robot_position_x)**2 + (point.y - robot_position_y)**2)
            if self.lookahead_distance <= distance < closest_distance:
                closest_distance = distance
                lookahead_point = point

        return lookahead_point


    def normalize_angle(self, angle):
        while angle > pi:
            angle -= 2 * pi
        while angle < -pi:
            angle += 2 * pi
        return angle

    def lidar_check_move(self):
        if self.lidar_msg.ranges[0] + self.lidar_msg.ranges[180] < 2.0:
            self.cmd_msg.linear.x = 0.0
            self.cmd_msg.angular.z = 0.2

        else:
            if self.lidar_msg.ranges[0] < self.lidar_msg.ranges[180]:
                self.cmd_msg.linear.x = -0.2
                self.cmd_msg.angular.z = 0.0
            else:
                self.cmd_msg.linear.x = 0.2
                self.cmd_msg.angular.z = 0.0

def main(args=None):
    rclpy.init(args=args)
    pure_pursuit_node = PurePursuit()
    rclpy.spin(pure_pursuit_node)
    pure_pursuit_node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()
