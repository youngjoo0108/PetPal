import rclpy
from rclpy.node import Node

from geometry_msgs.msg import Twist, PoseStamped
from ssafy_msgs.msg import TurtlebotStatus,EnviromentStatus
from std_msgs.msg import Float32,Int8MultiArray

# controller는 시뮬레이터로 부터를 데이터를 수신해서 확인(출력)하고, 송신해서 제어가 되는지 확인해보는 통신 테스트를 위한 노드입니다.
# 메시지를 받아서 어떤 데이터들이 있는지 확인하고, 어떤 메시지를 보내야 가전 또는 터틀봇이 제어가 되는지 확인해보면서 ros2 통신에 익숙해지세요.
# 수신 데이터 : 터틀봇 상태(/turtlebot_status), 환경정보(/envir_status), 가전정보(/app_status)
# 송신 데이터 : 터틀봇 제어(/ctrl_cmd), 가전제어(/app_control)

# 노드 로직 순서
# 1. 수신 데이터 출력
# 2. 특정 가전제품 ON
# 3. 특정 가전제품 OFF
# 4. 터틀봇 정지
# 5. 터틀봇 시계방향 회전
# 6. 터틀봇 반시계방향 회전


class Controller(Node):

    def __init__(self):
        super().__init__('sub1_controller')
        ## 메시지 송신을 위한 PUBLISHER 생성
        # self.cmd_publisher = self.create_publisher(Twist, 'cmd_vel', 10)
        self.app_control_pub = self.create_publisher(Int8MultiArray, 'app_control', 10)

        ## 메시지 수신을 위한 SUBSCRIBER 생성
        self.turtlebot_status_sub = self.create_subscription(TurtlebotStatus,'/turtlebot_status',self.listener_callback,10)
        self.envir_status_sub = self.create_subscription(EnviromentStatus,'/envir_status',self.envir_callback,10)
        self.app_status_sub = self.create_subscription(Int8MultiArray,'/app_status',self.app_callback,10)
        self.timer = self.create_timer(3, self.timer_callback)
        self.goal_pub = self.create_publisher(PoseStamped,'goal_pose', 10)

        ## 제어 메시지 변수 생성 
        # self.cmd_msg=Twist()

        self.goal_msg = PoseStamped()
        self.goal_msg.header.frame_id = 'map'

        self.app_control_msg=Int8MultiArray()
        for i in range(17):
            self.app_control_msg.data.append(0)


        self.turtlebot_status_msg=TurtlebotStatus()
        self.envir_status_msg=EnviromentStatus()
        self.app_status_msg=Int8MultiArray()
        self.is_turtlebot_status=False
        self.is_app_status=False
        self.is_envir_status=False
        '''
        0: 신발장
        1: 방 1
        2: 방 2
        3: 방 3
        4: 방 4
        5: 주방 조명
        6: 거실 조명
        7: 방1 에어컨
        8: 방2 에어컨
        9: 방3 에어컨
        10: 거실 에어컨
        11: 공기 청정기
        12: TV
        13: 방1 커튼
        14: 방2 커튼
        15: 방3 커튼
        16: 거실 커튼
        '''
        self.iot_info = [(-4.52, -7.67), (-12.52, -6.55), (-5.25, -5.42), (-2.48, -6.56),
                          (-12.52, -6.55), (-9.2, -7.57), (-7.08, -5.99), (-12.49, -2.63), 
                          (-4.98, -3.75), (-2.52, -3.64), (-7.34, -1.13), (-9.8, -5.17), 
                          (-7.33, -2.77), (-12.49, -2.63), (-4.98, -3.75), (-2.52, -3.64), (-8.76, -1.15)]
        
        self.iot_todo = [i for i in range(17)]

        self.map_size_x=350
        self.map_size_y=350
        self.map_resolution=0.05
        self.map_offset_x=-8-8.75
        self.map_offset_y=-4-8.75
    
        self.GRIDSIZE=350

        #test
        # self.iot_callback()


    def listener_callback(self, msg):
        self.is_turtlebot_status=True
        self.turtlebot_status_msg=msg


    def envir_callback(self, msg):
        self.is_envir_status=True
        self.envir_status_msg=msg

    def app_callback(self, msg):
        self.is_app_status=True
        self.app_status_msg=msg  

    def app_all_on(self):
        # print("on")
        for i in range(17):
            self.app_control_msg.data[i]=1
        self.app_control_pub.publish(self.app_control_msg)
        
    def app_all_off(self):
        for i in range(17):
            self.app_control_msg.data[i]=2
        self.app_control_pub.publish(self.app_control_msg)
        
    def app_on_select(self,num):

        self.app_control_msg.data[num]=1
        self.app_control_pub.publish(self.app_control_msg)
        
        '''
        로직 2. 특정 가전 제품 ON
        '''

    def app_off_select(self,num):
        '''
        로직 3. 특정 가전 제품 OFF
        '''


    def turtlebot_go(self) :
        # self.cmd_msg.linear.x=0.3
        # self.cmd_msg.angular.z=0.0
        pass

    def turtlebot_stop(self) :
        '''
        로직 4. 터틀봇 정지
        '''

    def turtlebot_cw_rot(self) :
        # self.cmd_msg.linear.x = 0.0
        # self.cmd_msg.angular.z = 1

        '''
        로직 5. 터틀봇 시계방향 회전
        '''

    def turtlebot_cww_rot(self) :
        '''
        로직 6. 터틀봇 반시계방향 회전
        '''

    def timer_callback(self):
        if self.iot_todo:
            if self.app_status_msg.data[self.iot_todo[0]] == 2:
                self.turtlebot_togo(self.iot_todo[0])
            else:
                self.iot_todo.pop(0)
                self.turtlebot_togo(self.iot_todo[0])
        

    def turtlebot_togo(self, num):
        goal_x, goal_y = self.iot_info[num]
        print(goal_x, goal_y, self.iot_todo)

        self.goal_msg.pose.position.x = goal_x
        self.goal_msg.pose.position.y = goal_y

        self.goal_msg.pose.orientation.x = 0.0
        self.goal_msg.pose.orientation.y = 0.0
        self.goal_msg.pose.orientation.z = 0.0
        self.goal_msg.pose.orientation.w = 1.0

        # print(self.goal)
        self.goal_msg.header.stamp = rclpy.clock.Clock().now().to_msg()
        self.goal_pub.publish(self.goal_msg)
        self.app_on_select(num)
        if self.app_status_msg.data[self.iot_todo[0]] == 1:
            self.iot_todo.pop(0)
        '''
        로직1. 수신 데이터 출력
        터틀봇 상태 : 현재 선솏도, 현재 각속도, 배터리 상태, 충전 상태 출력
        환경 정보 : 날짜, 시간, 온도, 날씨 출력
        가전 제품 : 가전상태 출력        
        '''
        # iot_info = {'kl' : }
        # print(self.turtlebot_status_msg.)
        # print(f' 터틀봇 : {self.turtlebot_status_msg}, 환경: {self.envir_status_msg}, 가전: {self.app_status_msg}')
        ## IOT(가전) 제어 함수
        # self.app_all_on()
        # self.app_all_off()
        # self.app_on_select(12)
        # self.app_select_off(12)


        ## 터틀봇 제어 함수
        # self.turtlebot_go()
        # self.turtlebot_stop()
        # self.turtlebot_cw_rot()
        # self.turtlebot_ccw_rot()


        # self.cmd_publisher.publish(self.cmd_msg)


def main(args=None):
    rclpy.init(args=args)
    sub1_controller = Controller()
    rclpy.spin(sub1_controller)
    sub1_controller.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()