import rclpy, json, requests
from rclpy.node import Node
from std_msgs.msg import String
from geometry_msgs.msg import Twist
from ssafy_msgs.msg import TurtlebotStatus, EnviromentStatus
from sensor_msgs.msg import Imu
from squaternion import Quaternion
from nav_msgs.msg import Odometry
from math import pi,cos,sin
import tf2_ros
import geometry_msgs.msg
import time


class odom(Node):

    def __init__(self):
        super().__init__('odom')
        
        # 로직 1. publisher, subscriber, broadcaster 만들기
        self.subscription = self.create_subscription(TurtlebotStatus,'/turtlebot_status',self.listener_callback,10)
        self.envir_sub = self.create_subscription(EnviromentStatus, '/envir_status', self.envir_callback, 10)
        self.imu_sub = self.create_subscription(Imu,'/imu',self.imu_callback,10)
        self.odom_publisher = self.create_publisher(Odometry, 'odom', 10)
        self.data_pub = self.create_publisher(String, '/to_server/data', 10)
        self.broadcaster = tf2_ros.StaticTransformBroadcaster(self)

        self.timer = self.create_timer(10, self.timer_callback)


        # 로봇의 pose를 저장해 publish 할 메시지 변수 입니다.
        self.envir_msg=EnviromentStatus()
        self.odom_msg=Odometry()
        # Map -> base_link 좌표계에 대한 정보를 가지고 있는 변수 입니다.
        self.base_link_transform=geometry_msgs.msg.TransformStamped()
        # base_link -> laser 좌표계에 대한 정보를 가지고 있는 변수 입니다.
        self.laser_transform=geometry_msgs.msg.TransformStamped()
        self.is_status=False
        self.is_imu=False
        self.is_calc_theta=False
        self.is_envir = False
        # x,y,theta는 추정한 로봇의 위치를 저장할 변수 입니다.
        self.x= -8.75
        self.y= -8.75

        self.theta=0
        # imu_offset은 초기 로봇의 orientation을 저장할 변수 입니다.
        self.imu_offset=0
        self.prev_time=0

        self.first_offset = 0.0
        # 로직 2. publish, broadcast 할 메시지 설정

        self.odom_msg.header.frame_id = 'map'
        self.odom_msg.child_frame_id = 'base_link'

        self.base_link_transform.header.frame_id = 'map'
        self.base_link_transform.child_frame_id = 'base_link'

        self.laser_transform.header.frame_id = 'base_link'
        self.laser_transform.child_frame_id = 'laser'
        self.laser_transform.transform.translation.x = 0.0
        self.laser_transform.transform.translation.y = 0.0
        self.laser_transform.transform.translation.z = 1.0
        self.laser_transform.transform.rotation.w = 1.0

    def envir_callback(self, msg):
        if not self.is_envir:
            msg = String()
            dt = {
                'weather' : self.envir_msg.weather,
                'temp' : self.envir_msg.temperature,
            }
            temp = {
                'type' : 'WEATHER',
                'message' : dt
            }
            data = json.dumps(temp)
            msg.data = data
            self.data_pub.publish(msg)
            self.is_envir=True
        self.envir_msg=msg

    def imu_callback(self,msg):
        # 로직 3. IMU 에서 받은 quaternion을 euler angle로 변환해서 사용
        
        imu_q = Quaternion(msg.orientation.w, msg.orientation.x, msg.orientation.y, msg.orientation.z)
        _, _, yaw = imu_q.to_euler()

        if self.is_calc_theta:
            if not self.is_imu:
                self.is_imu = True
                self.imu_offset = yaw - self.first_offset
            else:
                # 현재 theta 계산 시, imu_offset을 빼서 초기 방향 대비 회전한 양을 계산
                self.theta = yaw - self.imu_offset

                # theta 범위 조정 (-pi ~ pi)
                if self.theta > pi:
                    self.theta -= 2 * pi
                elif self.theta < -pi:
                    self.theta += 2 * pi


    def listener_callback(self, msg):
        if not self.is_calc_theta:
            self.first_offset = msg.twist.linear.z*pi/180
            self.x = msg.twist.angular.x
            self.y = msg.twist.angular.y
            self.is_calc_theta = True

        if self.is_imu ==True and self.is_calc_theta == True:
            if self.is_status == False :
                self.is_status=True
                self.prev_time=rclpy.clock.Clock().now()
            else :
                
                self.current_time=rclpy.clock.Clock().now()
                # 계산 주기를 저장한 변수 입니다. 단위는 초(s)
                self.period = (self.current_time-self.prev_time).nanoseconds/1000000000
                # 로봇의 선속도, 각속도를 저장하는 변수, 시뮬레이터에서 주는 각 속도는 방향이 반대이므로 (-)를 붙여줍니다.
                linear_x = msg.twist.linear.x
                angular_z = -msg.twist.angular.z
                
                # 로직 4. 로봇 위치 추정
                # (테스트) linear_x = 1, self.theta = 1.5707(rad), self.period = 1 일 때
                # self.x=0, self.y=1 이 나와야 합니다. 로봇의 헤딩이 90도 돌아가 있는
                # 상태에서 선속도를 가진다는 것은 x축방향이 아니라 y축방향으로 이동한다는 뜻입니다. 
                self.x = msg.twist.angular.x
                self.y = msg.twist.angular.y

                self.x += linear_x*cos(self.theta)*self.period
                self.y += linear_x*sin(self.theta)*self.period
                self.theta += angular_z*self.period

                self.base_link_transform.header.stamp = rclpy.clock.Clock().now().to_msg()
                self.laser_transform.header.stamp = rclpy.clock.Clock().now().to_msg()
                
                # 로직 5. 추정한 로봇 위치를 메시지에 담아 publish, broadcast

                q = Quaternion.from_euler(0, 0, self.theta)
                
                self.base_link_transform.transform.translation.x = self.x
                self.base_link_transform.transform.translation.y = self.y
                self.base_link_transform.transform.rotation.x = q.x
                self.base_link_transform.transform.rotation.y = q.y
                self.base_link_transform.transform.rotation.z = q.z
                self.base_link_transform.transform.rotation.w = q.w
                
                self.odom_msg.pose.pose.position.x = self.x
                self.odom_msg.pose.pose.position.y = self.y
                self.odom_msg.pose.pose.orientation.x = q.x
                self.odom_msg.pose.pose.orientation.y = q.y
                self.odom_msg.pose.pose.orientation.z = q.z
                self.odom_msg.pose.pose.orientation.w = q.w
                self.odom_msg.twist.twist.linear.x = linear_x
                self.odom_msg.twist.twist.angular.z = angular_z

                self.broadcaster.sendTransform(self.base_link_transform)
                self.broadcaster.sendTransform(self.laser_transform)
                self.odom_publisher.publish(self.odom_msg)
                self.prev_time=self.current_time

    def timer_callback(self):
        if self.is_envir:
            msg = String()
            dt = {
                'weather' : self.envir_msg.weather,
                'temp' : self.envir_msg.temperature,
            }
            temp = {
                'type' : 'WEATHER',
                'message' : dt
            }
            data = json.dumps(temp)
            msg.data = data
            self.data_pub.publish(msg)
        
def main(args=None):
    rclpy.init(args=args)
    odom_node = odom()
    rclpy.spin(odom_node)
    odom_node.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()