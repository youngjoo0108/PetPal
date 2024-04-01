import rclpy, json, requests

from rclpy.node import Node
from std_msgs.msg import String
from squaternion import Quaternion
from nav_msgs.msg import Odometry, Path, OccupancyGrid
from geometry_msgs.msg import Twist, PoseStamped, Point32
from ssafy_msgs.msg import TurtlebotStatus
from ros_log_package.RosLogPublisher import RosLogPublisher


class Search(Node):

    def __init__(self):
        super().__init__('yolo_sub')
        self.api_call()
        self.dog_sub = self.create_subscription(String, 'dog_position', self.dog_callback, 10)
        self.goal_pub = self.create_publisher(PoseStamped, 'goal_pose', 1)
        self.odom_sub = self.create_subscription(Odometry, '/odom', self.odom_callback, 10)

        self.odom_msg = Odometry()

        self.is_dog = False
        self.is_goal = False
        self.is_goal_set = False
        self.is_odom = False


    def api_call(self):
        url = "https://j10a209.p.ssafy.io/api/v1/homes/turtle/{homeId}"
        params = {'homeId' : 1}
        response = requests.get(url, params=params)
        if response.status_code == 200:
            data = response.json()
            #print(data)
            # 변경 필수
            self.goal_x = data
            self.goal_y = data

            self.go_last_point(self.goal_x, self.goal_y)
            
        else:
            print('Failed to get data')
    

    def go_last_point(self, x, y):
        if not self.is_dog:
            if not self.is_goal and not self.is_goal_set:
                self.goal_msg.pose.position.x = x
                self.goal_msg.pose.position.y = y
                q = Quaternion.from_euler(0, 0, self.goal_yaw)

                self.goal_msg.pose.orientation.x = q.x
                self.goal_msg.pose.orientation.y = q.y
                self.goal_msg.pose.orientation.z = q.z
                self.goal_msg.pose.orientation.w = q.w

                self.goal_msg.header.stamp = rclpy.clock.Clock().now().to_msg()
                self.goal_pub.publish(self.goal_msg)
                self.is_goal_set = True

            elif self.is_goal_set and self.is_goal:

                # 순찰 트랙
                pass
 
        else:
            # tracking
            pass


    def dog_callback(self, msg):
        data = msg.data
        if data:
            self.is_dog = True
        else:
            self.is_dog = False

    def odom_callback(self, msg):
        
        self.is_odom = True
        self.odom_msg = msg
        q = Quaternion(msg.pose.pose.orientation.w , msg.pose.pose.orientation.x, msg.pose.pose.orientation.y, msg.pose.pose.orientation.z)
        _,_,self.robot_yaw = q.to_euler()
        self.robot_pose_x = self.odom_msg.pose.pose.position.x
        self.robot_pose_y = self.odom_msg.pose.pose.position.y

        if abs(self.robot_pose_x - self.goal_x) < 0.5 and abs(self.robot_pose_y - self.goal_y) < 0.5:
            self.is_goal = True
        else:
            self.is_goal = False


def main(args=None):
    rclpy.init(args=args)
    search = Search()
    rclpy.spin(search)
    search.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()