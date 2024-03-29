import rclpy, json
import numpy as np

from rclpy.node import Node
from std_msgs.msg import String
from squaternion import Quaternion
from nav_msgs.msg import Odometry, Path, OccupancyGrid
from geometry_msgs.msg import Twist, PoseStamped, Point32
from ssafy_msgs.msg import TurtlebotStatus,HandControl
from ros_log_package.RosLogPublisher import RosLogPublisher


class ObstacleControl(Node):

    def __init__(self):
        super().__init__('obstacle_controller')
        self.yolo_sub = self.create_subscription(String, 'captured_object', self.obstacle_callback, 10)
        self.odom_sub = self.create_subscription(Odometry, '/odom', self.odom_callback, 10)
        self.goal_pub = self.create_publisher(PoseStamped,'goal_pose', 10)
        self.cmd_pub = self.create_publisher(Twist, 'cmd_vel', 10)
        self.timer = self.create_timer(0.5, self.timer_callback)
        self.hand_control_pub = self.create_publisher(HandControl, '/hand_control', 10)                
        self.turtlebot_status = self.create_subscription(TurtlebotStatus,'/turtlebot_status',self.turtlebot_status_cb,10)
        
        self.hand_control_msg=HandControl()        
        self.turtlebot_status_msg = TurtlebotStatus()
        self.goal_msg = PoseStamped()
        self.odom_msg = Odometry()
        self.cmd_msg = Twist()

        self.goal_msg.header.frame_id = 'map'

        self.yolo_sub
        self.is_turtlebot_status = False
        self.is_obstacle = False
        self.is_odom = False
        self.is_lifted = False
        self.is_obstacle_goal = False
        self.is_goal_setting = False

        self.robot_pose_x = 0.0
        self.robot_pose_y = 0.0
        self.robot_yaw = 0.0

        self.goal_x = 0.0
        self.goal_y = 0.0
        self.goal_yaw = 0.0

        self.obstacle_height = 0.0
        self.obstacle_width = 0.0
        self.obstacle_x_in_camera = 0.0
        self.obstacle_y_in_camera = 0.0
        self.turtlebot_to_obstacle_theta = 0.0
        self.turtlebot_to_obstacle_distance = 0.0

        self.obstacle_goal_x = -7.4
        self.obstacle_goal_y = 10.7
        self.obstacle_lifted_x = 0.0
        self.obstacle_lifted_y = 0.0


        # log
        self.ros_log_pub = None
        try:
            self.ros_log_pub = RosLogPublisher(self)
        except Exception as e:
            self.get_logger().error('Subscription initialization error: {}'.format(e))


    def obstacle_callback(self, msg):
        data = json.loads(msg.data)
        if 'knife_list' in data and not self.turtlebot_status_msg.can_use_hand:
            for obstacle in data['knife_list']:
                self.is_obstacle = True
                print(obstacle)
                left_top = obstacle.split('/')[-2]
                right_bottom = obstacle.split('/')[-1]
                left_top_x, left_top_y = map(float, left_top.split('-'))
                right_bottom_x, right_bottom_y = map(float, right_bottom.split('-'))

                self.obstacle_height = right_bottom_y - left_top_y
                self.obstacle_width = right_bottom_x - left_top_x
                self.obstacle_x_in_camera = 160 - (left_top_x + right_bottom_x) / 2.0   # 카메라 중심으로부터의 x 거리
                self.obstacle_y_in_camera = 240 - (left_top_y + right_bottom_y) / 2.0   # 카메라 바닥으로부터의 y 거리
                
                self.obstacle_distance_in_camera = np.sqrt(self.obstacle_x_in_camera ** 2 + self.obstacle_y_in_camera ** 2)

                self.turtlebot_to_obstacle_theta = np.arctan2(self.obstacle_x_in_camera * 3, self.obstacle_y_in_camera * 4)

                if self.obstacle_height > self.obstacle_width:
                    self.turtlebot_to_obstacle_distance = self.obstacle_distance_in_camera / (self.obstacle_height * np.cos(self.turtlebot_to_obstacle_theta))  
                else:
                    self.turtlebot_to_obstacle_distance = self.obstacle_distance_in_camera / (self.obstacle_width * np.cos(self.turtlebot_to_obstacle_theta))
                self.goal_x = self.robot_pose_x + (self.turtlebot_to_obstacle_distance - 0.3) * np.cos(self.robot_yaw + self.turtlebot_to_obstacle_theta)
                self.goal_y = self.robot_pose_y + (self.turtlebot_to_obstacle_distance - 0.3) * np.sin(self.robot_yaw + self.turtlebot_to_obstacle_theta)
                self.goal_yaw = self.turtlebot_to_obstacle_theta + self.robot_yaw
           
                self.tracking_obstacle()


    def odom_callback(self, msg):
        self.is_odom = True
        self.odom_msg = msg
        q = Quaternion(msg.pose.pose.orientation.w , msg.pose.pose.orientation.x, msg.pose.pose.orientation.y, msg.pose.pose.orientation.z)
        _,_,self.robot_yaw = q.to_euler()
        self.robot_pose_x = self.odom_msg.pose.pose.position.x
        self.robot_pose_y = self.odom_msg.pose.pose.position.y

        if abs(self.robot_pose_x - self.obstacle_goal_x) < 0.5 and abs(self.robot_pose_y - self.obstacle_goal_y) < 0.5:
            self.is_obstacle_goal = True
        else:
            self.is_obstacle_goal = False


    def tracking_obstacle(self):
    
        self.goal_msg.pose.position.x = self.goal_x
        self.goal_msg.pose.position.y = self.goal_y
        
        q = Quaternion.from_euler(0, 0, self.goal_yaw)

        self.goal_msg.pose.orientation.x = q.x
        self.goal_msg.pose.orientation.y = q.y
        self.goal_msg.pose.orientation.z = q.z
        self.goal_msg.pose.orientation.w = q.w

        self.goal_msg.header.stamp = rclpy.clock.Clock().now().to_msg()
        self.goal_pub.publish(self.goal_msg)
        self.ros_log_pub.publish_log('DEBUG', 'Tracking Obstacle')

    
    def timer_callback(self):
        # 갖다 놓는 로직
        if self.is_obstacle:
            if self.is_lifted:
                # 골까지 주행
                if not self.is_obstacle_goal and not self.is_goal_setting:
                    
                    self.goal_msg.pose.position.x = self.obstacle_goal_x
                    self.goal_msg.pose.position.y = self.obstacle_goal_y
                    
                    q = Quaternion.from_euler(0, 0, 0)

                    self.goal_msg.pose.orientation.x = q.x
                    self.goal_msg.pose.orientation.y = q.y
                    self.goal_msg.pose.orientation.z = q.z
                    self.goal_msg.pose.orientation.w = q.w

                    self.goal_msg.header.stamp = rclpy.clock.Clock().now().to_msg()
                    self.goal_pub.publish(self.goal_msg)
                    self.ros_log_pub.publish_log('DEBUG', 'Go goalpoint with Obstacle')

                    self.is_goal_setting = True

                elif self.is_goal_setting and self.is_obstacle_goal:
                    
                    cnt = 0
                    while cnt < 5:
                        self.hand_control_put_down()
                        cnt += 1
                    
                    if self.turtlebot_status_msg.can_use_hand == False:
                        self.goal_msg.pose.position.x = self.obstacle_lifted_x
                        self.goal_msg.pose.position.y = self.obstacle_lifted_y
                        
                        q = Quaternion.from_euler(0, 0, 0)

                        self.goal_msg.pose.orientation.x = q.x
                        self.goal_msg.pose.orientation.y = q.y
                        self.goal_msg.pose.orientation.z = q.z
                        self.goal_msg.pose.orientation.w = q.w

                        self.goal_msg.header.stamp = rclpy.clock.Clock().now().to_msg()
                        self.goal_pub.publish(self.goal_msg)
                        self.ros_log_pub.publish_log('obscontrol', 'Obstacle control success')
                        self.is_lifted = False
                        self.is_obstacle = False
                        self.is_goal_setting = False

            else:
                if self.is_obstacle and not self.is_obstacle_goal:
                    # 들어야함
                    self.hand_control_pick_up()
                   
                    if self.turtlebot_status_msg.can_use_hand == True:

                        self.obstacle_lifted_x = self.robot_pose_x
                        self.obstacle_lifted_y = self.robot_pose_y

                        self.is_lifted = True
                        self.ros_log_pub.publish_log('DEBUG', 'Pickup Obstacle Success')

    
    def hand_control_pick_up(self):
        self.hand_control_msg.control_mode = 2 
        self.hand_control_msg.put_distance = 1.0
        self.hand_control_msg.put_height = 0.0
        self.hand_control_pub.publish(self.hand_control_msg)
          

    def hand_control_put_down(self):

        self.hand_control_msg.control_mode = 3 
        self.hand_control_msg.put_distance = 1.0
        self.hand_control_msg.put_height = 0.5
        self.hand_control_pub.publish(self.hand_control_msg)
        

    def turtlebot_status_cb(self,msg):
        self.is_turtlebot_status=True
        self.turtlebot_status_msg=msg

        
def main(args=None):
    rclpy.init(args=args)
    obstacle_controller = ObstacleControl()
    rclpy.spin(obstacle_controller)
    obstacle_controller.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()
