import rclpy, json, requests
import numpy as np

from rclpy.node import Node
from std_msgs.msg import String
from squaternion import Quaternion
from nav_msgs.msg import Odometry, Path, OccupancyGrid
from geometry_msgs.msg import Twist, PoseStamped, Point32
from ssafy_msgs.msg import TurtlebotStatus,HandControl
from sensor_msgs.msg import LaserScan, CompressedImage
from ros_log_package.RosLogPublisher import RosLogPublisher


class ObstacleControl(Node):

    def __init__(self):
        super().__init__('obstacle_controller')
        self.yolo_sub = self.create_subscription(String, 'captured_object', self.obstacle_callback, 10**3)
        self.odom_sub = self.create_subscription(Odometry, '/odom', self.odom_callback, 10)
        self.goal_pub = self.create_publisher(PoseStamped,'goal_pose', 10)
        # self.cmd_pub = self.create_publisher(Twist, 'cmd_vel', 10)
        self.timer = self.create_timer(0.5, self.timer_callback)
        self.hand_control_pub = self.create_publisher(HandControl, '/hand_control', 10)                
        self.turtlebot_status = self.create_subscription(TurtlebotStatus,'/turtlebot_status',self.turtlebot_status_cb,10)
        self.lidar_sub = self.create_subscription(LaserScan, '/scan', self.lidar_callback, 10)
        self.publisher_save_camera = self.create_publisher(String, '/screen_shot/recall', 10)
        self.subscriber_save_camera = self.create_subscription(CompressedImage, '/screen_shot/pub', self.capture_callback , 10)
        self.data_pub = self.create_publisher(String, '/to_server/data', 10)
        self.request_pub = self.create_publisher(String, '/request', 10)

        
        self.hand_control_msg=HandControl()        
        self.turtlebot_status_msg = TurtlebotStatus()
        self.goal_msg = PoseStamped()
        self.odom_msg = Odometry()
        self.cmd_msg = Twist()
        self.lidar_msg = LaserScan()
        self.data_msg = String()
        self.request_msg = String()

        self.goal_msg.header.frame_id = 'map'

        self.is_turtlebot_status = False
        self.is_obstacle = False
        self.is_odom = False
        self.is_lifted = False
        self.is_obstacle_goal = False
        self.is_goal_setting = False
        self.camera_captured = False
        
        # self.is_obstacle_control_finished = False
    

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

        self.obstacle_name = ''
        self.target_id = 0
        


        # log
        self.ros_log_pub = None
        try:
            self.ros_log_pub = RosLogPublisher(self)
        except Exception as e:
            self.get_logger().error('Subscription initialization error: {}'.format(e))


    def obstacle_callback(self, msg):
        data = json.loads(msg.data)
        if data['obstacle_list']:
            self.request_msg.data = "obstacle_on"
            self.request_pub.publish(self.request_msg)

            obstacles = data['obstacle_list']
            for obstacle in obstacles:
                if obstacle and not self.turtlebot_status_msg.can_use_hand and not self.is_obstacle_goal:
                    # for obstacle in data:
                    self.is_obstacle = True

                    # BookPile, Mug, PenHolder, Stapler
                    self.obstacle_name = obstacle.split('/')[1]
                    # print(obstacle_name)
                    if self.obstacle_name == "Mug":
                        self.obstacle_real_height = 0.3
                    elif self.obstacle_name == "BookPile":
                        self.obstacle_real_height = 0.7
                    elif self.obstacle_name == "PenHolder":
                        self.obstacle_real_height = 0.25
                    elif self.obstacle_name == "Stapler":
                        self.obstacle_real_height = 0.3
                
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
                    

                    self.turtlebot_to_obstacle_distance = self.obstacle_distance_in_camera * self.obstacle_real_height / (self.obstacle_width * np.cos(self.turtlebot_to_obstacle_theta))
                    # self.turtlebot_to_obstacle_distance = self.lidar_msg.ranges[(int(self.turtlebot_to_obstacle_theta + 360)) % 360]

                    self.goal_x = self.robot_pose_x + (self.turtlebot_to_obstacle_distance) * np.cos(self.robot_yaw + self.turtlebot_to_obstacle_theta)
                    self.goal_y = self.robot_pose_y + (self.turtlebot_to_obstacle_distance) * np.sin(self.robot_yaw + self.turtlebot_to_obstacle_theta)
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


    def lidar_callback(self, msg):
        self.lidar_msg = msg


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
        # self.ros_log_pub.publish_log('DEBUG', 'Tracking Obstacle')

    
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
                    
                    # 다시 물건 처리한 장소로 돌아가기
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
                         
                        dt = {
                            'objectId' : self.target_id,
                            'objectType' : self.obstacle_name 
                        }
                        temp = {
                            'type' : 'OCOMPLETE',
                            'message' : dt
                        }
                        data = json.dumps(temp)
                        self.data_msg.data = data
                        self.data_pub.publish(self.data_msg)

                        self.request_msg.data = "obstacle_off"
                        self.request_pub.publish(self.request_msg)

                        self.is_lifted = False
                        self.is_obstacle = False
                        self.is_goal_setting = False
                        self.camera_captured = False

            else:
                if self.is_obstacle and not self.is_obstacle_goal:

                    if not self.camera_captured:
                        none_msg = String()
                        self.publisher_save_camera.publish(none_msg)
                        self.camera_captured = True

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



    
    def capture_callback(self, video_image):
     # 서버의 엔드포인트 주소
        # endpoint = "http://localhost:8081/api/v1/images"
        base_endpoint = "https://j10a209.p.ssafy.io/api/v1/"
        # 파일 확장자명
        params = {'homeId':2,'extension': 'png'}
        self.screenShot_type = self.obstacle_name
        self.screenShot_position = {
            "x": self.robot_pose_x,
            "y": self.robot_pose_y,
        }

        response = requests.post(base_endpoint+"images", json=params)
        if response.status_code == 200:
            data = response.json()
            upload_url = data['presignedURL']
            image_id = data['imageId']
            print(f"Received upload URL: {upload_url}")
            print(f"Image ID: {image_id}")
        else:
            print("Failed to get upload URL and Image ID")
            # 에러 처리

        # # S3 업로드 파트
        # file_path = "C:/Users/SSAFY/Desktop/과제2.PNG" # 여기에 전송할 사진의 절대경로

        # with open(file_path, 'rb') as f:
        #     # 파일의 바이너리 데이터를 PUT 요청의 본문으로 전송
        upload_response = requests.put(upload_url, data=video_image.data)


        if upload_response.status_code == 200:
            print("Upload successful")
        else:
            print(upload_response.status_code)
            print("Upload failed")


        # Target 생성
        params = {
                    'homeId':2,
                    'imageId':image_id,
                    'objectType':self.screenShot_type, 
                    "coordinate":self.screenShot_position
                }
        target_response = requests.post(base_endpoint+"targets", json=params)
        self.target_id = int(target_response.text)


def main(args=None):
    rclpy.init(args=args)
    obstacle_controller = ObstacleControl()
    rclpy.spin(obstacle_controller)
    obstacle_controller.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()
