import rclpy, json
from std_msgs.msg import String
from squaternion import Quaternion


class ObstacleControl(Node):

    def __init__(self):
        super().__init__('obstacle_controller')
        self.yolo_sub = self.create_subscription(String, 'captured_object', self.obstacle_callback, 10)
        self.odom_sub = self.create_subscription(Odometry, '/odom', self.odom_callback, 10)

        self.is_obstacle = False


    def obstacle_callback(self, msg):
        data = json.loads(msg.data)
        if 'list' in data:
            for obstacle in data['list']:
                self.is_obstacle = True
    

    def odom_callback(self, msg):
        self.is_odom = True
        self.odom_msg = msg
        q = Quaternion(msg.pose.pose.orientation.w , msg.pose.pose.orientation.x, msg.pose.pose.orientation.y, msg.pose.pose.orientation.z)
        _,_,self.robot_yaw = q.to_euler()
        self.robot_pose_x = self.odom_msg.pose.pose.position.x
        self.robot_pose_y = self.odom_msg.pose.pose.position.y

        

def main(args=None):
    rclpy.init(args=args)
    obstacle_controller = ObstacleControl()
    rclpy.spin(obstacle_controller)
    obstacle_controller.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()
