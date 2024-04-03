import rclpy, json

from rclpy.node import Node
from std_msgs.msg import String
from squaternion import Quaternion
from nav_msgs.msg import Odometry, Path, OccupancyGrid
from geometry_msgs.msg import Twist, PoseStamped, Point32
from ssafy_msgs.msg import TurtlebotStatus
from ros_log_package.RosLogPublisher import RosLogPublisher


class YoloSub(Node):

    def __init__(self):
        super().__init__('yolo_sub')

        self.yolo_sub = self.create_subscription(String, 'captured_object', self.yolo_callback, 10**3)
        self.odom_sub = self.create_subscription(Odometry, '/odom', self.odom_callback, 10)
        self.request_pub = self.create_publisher(String, 'request', 10)
        try:
            self.publisher_data = self.create_publisher(String, '/to_server/data', 20)
        except:
            print("init publisher data error")

        self.odom_msg = Odometry()

        self.is_odom = False

        self.robot_pose_x = 0.0
        self.robot_pose_y = 0.0

    def yolo_callback(self, msg):
        data = json.loads(msg.data)
        if data:
            # data topic 4개
            if data['dog_list']:

                # 발견 시 터틀봇 마지막 위치 redis 저장
                last_found_topic_data = {'last_found_point' : (self.robot_pose_x, self.robot_pose_y)}
                last_found_json_str = json.dumps(last_found_topic_data)
                last_found_msg = String()
                last_found_msg.data = last_found_json_str
                self.to_server_callback(msg)

                # 강아지 위치 pub
                for dog in data['dog_list']:
                    msg = String()
                    msg.data = "found"
                    self.request_pub.publish(msg)


            elif data['obstacle_list']:

                for obstacle in data['obstacle_list']:
                    msg = String()
                    msg.data = "obstacle_on"
                    self.request_pub.publish(msg)

        


    def odom_callback(self, msg):

        self.is_odom = True
        self.odom_msg = msg
  
        self.robot_pose_x = self.odom_msg.pose.pose.position.x
        self.robot_pose_y = self.odom_msg.pose.pose.position.y

    
    def to_server_callback(self, msg):
        self.publisher_data.publish(msg)


def main(args=None):
    rclpy.init(args=args)
    yolo_sub = YoloSub()
    rclpy.spin(yolo_sub)
    yolo_sub.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()
