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

    def api_call(self):
        url = "https://j10a209.p.ssafy.io/api/v1/homes/turtle/{homeId}"
        params = {'homeId' : 1}
        response = requests.get(url, params=params)
        if response.status_code == 200:
            data = response.json()
            print(data)
        else:
            print('Failed to get data')
    

def main(args=None):
    rclpy.init(args=args)
    search = Search()
    rclpy.spin(search)
    search.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()