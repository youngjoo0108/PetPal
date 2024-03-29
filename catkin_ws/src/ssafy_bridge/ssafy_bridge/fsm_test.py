import os
import signal
import subprocess
import time
import rclpy
from rclpy.node import Node
from std_msgs.msg import String

# 상태에 따른 런치 파일 매핑
state_launch_file_map = {
    'patrol': 'patrol.py',
    'stay': 'stay.py',
    'scan': 'scan.py',
    'tracking' : 'tracking.py',
}

FSM = {
    "stay" : {
        "scan_on" : "scan",
        "patrol_on" : "patrol",
        "tracking_on" : "search",
        "interrupt_on" : "interrupt",
    },
    "scan" : {
        "scan_off" : "stay",
    },
    "patrol" : {
        "patrol_off" : "stay",
        "tracking_on" : "search",
        "interrupt_on" : "interrupt",
    },
    "search" : {
        "tracking_off" : "stay",
        "patrol_on" : "patrol",
        "found" : "tracking",
        "interrupt_on" : "interrupt",
    },
    "tracking" : {
        "tracking_off" : "stay",
        "patrol_on" : "patrol",
        "lost" : "search",
        "interrupt_on" : "interrupt",
    },
    "interrupt" : {
        "interrupt_off" : "check_last_state",
    },
}

class control_tower(Node) :
    def __init__(self):
        super().__init__('control_tower')

        #self.reqeust_sub = self.create_subscription(String, '/request', self.reqeust_callback, 20)
        self.fsm_pub = self.create_publisher(String, 'fsm', 10)

        self.current_process = None
        self.current_state = "stay"
        self.last_state = None

        self.fsm_msg = String()

        while True:
            menu=input('FSM 입력 : ')
            self.fsm_msg.data = menu
            self.fsm_pub.publish(self.fsm_msg)
            self.launch_file_for_state(menu)

        # while True:
        #     state = self.read_robot_state()
        #     print('update')
        #     if state != last_state:
        #         self.launch_file_for_state(state)
        #         last_state = state

        #     time.sleep(1)

    def read_robot_state(self):
        # ROBOT_STATE 값을 파일로부터 읽어오는 코드 예시
        try:
            with open("robot_state.txt", "r") as file:
                return file.read().strip()
        except FileNotFoundError:
            return None

    def launch_file_for_state(self, state):
        if self.current_process:
            # Windows에서 taskkill 명령을 사용하여 프로세스와 그 하위 프로세스를 종료
            subprocess.call(['taskkill', '/F', '/T', '/PID', str(self.current_process.pid)])
            self.current_process.terminate()
            self.current_process.wait()

        launch_file = state_launch_file_map.get(state)
        if launch_file:
            print(f"Launching {launch_file} for state '{state}'...")
            self.current_process = subprocess.Popen(["ros2", "launch", "test_209", launch_file])
    
    def reqeust_callback(self, msg):
        if msg.data in FSM[self.current_state]:
            if FSM[self.current_state][msg.data] == "check_last_state":
                self.current_state = self.last_state
                self.last_state = "interrupt"
            else:
                self.last_state = self.current_state
                self.current_state = FSM[self.current_state][msg.data]
            
            self.launch_file_for_state(self.current_state)
            self.fsm_msg = self.current_state
            self.fsm_pub.publish(self.fsm_msg)


def main(args=None):
    rclpy.init(args=args)
    tower = control_tower()
    rclpy.spin(tower)
    tower.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()