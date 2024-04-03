import rclpy
from rclpy.node import Node
from rclpy.clock import Clock, ClockType
import requests
import threading
import datetime

class TimedTaskExecutor(Node):
    def __init__(self):
        super().__init__('timed_task_executor')
        self.homeId = '2'
        self.ros_clock = Clock(clock_type=ClockType.ROS_TIME)
        self.scheduled_tasks = {}  # 실행할 작업 목록을 저장하는 딕셔너리
        self.fetch_schedule_period = 60  # 스케줄 정보를 가져오는 주기(초)
        self.api_url = "https://j10a209.p.ssafy.io/api/v1/schedules/" + self.homeId  # API URL
        self.init_schedule_update()

    def fetch_and_update_schedules(self):
        try:
            response = requests.get(self.api_url)
            if response.status_code == 200:
                schedules = response.json()
                # 스케줄 정보 업데이트
                for schedule in schedules:
                    if schedule['isActive']:
                        task_time = schedule['day'].strftime('%Y-%m-%d') + ' ' + schedule['time'].strftime('%H:%M')
                        task_name = schedule['taskType']  # 예: 'task1', 'task2' 등의 작업 이름
                        self.scheduled_tasks[task_time] = getattr(self, task_name, self.unknown_task)
            else:
                self.get_logger().error('Failed to fetch schedules from API.')
        except Exception as e:
            self.get_logger().error(f'Exception occurred during API request: {e}')

    def unknown_task(self):
        self.get_logger().info('Attempting to execute an unknown task.')

    def task1(self):
        self.get_logger().info('Executing Task 1')

    def task2(self):
        self.get_logger().info('Executing Task 2')

    def init_schedule_update(self):
        # 스케줄 정보 주기적 업데이트
        threading.Thread(target=self.periodic_schedule_update, daemon=True).start()

    def periodic_schedule_update(self):
        while rclpy.ok():
            self.fetch_and_update_schedules()
            rclpy.spin_once(self, timeout_sec=self.fetch_schedule_period)

    def check_time_and_execute(self):
        while rclpy.ok():
            now = datetime.datetime.now().strftime('%Y-%m-%d %H:%M')
            if now in self.scheduled_tasks:
                self.scheduled_tasks[now]()
                # 실행 후 해당 작업을 목록에서 제거
                del self.scheduled_tasks[now]
            rclpy.spin_once(self, timeout_sec=60)  # 매 분마다 현재 시간 확인

def main(args=None):
    rclpy.init(args=args)
    node = TimedTaskExecutor()
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        node.destroy_node()
        rclpy.shutdown()

if __name__ == '__main__':
    main()