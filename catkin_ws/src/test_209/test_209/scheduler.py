import rclpy
from rclpy.node import Node
from apscheduler.schedulers.background import BackgroundScheduler
from datetime import datetime, timedelta
import requests

class CommandExecutorNode(Node):
    def __init__(self):
        super().__init__('command_executor_node')
        self.scheduler = BackgroundScheduler()
        self.fetch_and_schedule()  # 시작 시 스케줄 정보를 가져오고 스케줄링
        self.scheduler.add_job(self.fetch_and_schedule, 'interval', minutes=60)  # 매 시간마다 스케줄 정보 업데이트
        self.scheduler.start()
        self.get_logger().info('Scheduler has started.')

    def fetch_and_schedule(self):
        home_id = 1
        url = f'https://j10a209.p.ssafy.io/api/v1/schedules/{home_id}'
        try:
            response = requests.get(url)
            if response.status_code == 200:
                schedules = response.json()
                for schedule in schedules:
                    if schedule['isActivated']:
                        self.schedule_command(schedule)
            else:
                self.get_logger().error('Failed to fetch schedule information.')
        except Exception as e:
            self.get_logger().error(f'Exception occurred during request: {e}')

    def schedule_command(self, schedule):
        start_time = schedule['startTime']  # "HH:MM" 형식
        now = datetime.now()
        start_datetime = now.replace(hour=int(start_time.split(':')[0]), minute=int(start_time.split(':')[1]), second=0, microsecond=0)
        if start_datetime < now:
            start_datetime += timedelta(days=1)  # 이미 시간이 지났다면 다음 날로 설정

        if schedule['isRepeat']:
            self.scheduler.add_job(self.execute_command, 'cron', day_of_week='*', hour=start_time.split(':')[0], minute=start_time.split(':')[1], args=[schedule])
        else:
            self.scheduler.add_job(self.execute_command, 'date', run_date=start_datetime, args=[schedule])

    def execute_command(self, schedule):
        appliance_uuid = schedule['uuid']
        command = schedule['command']  # "ON" 또는 "OFF"
        position = schedule['position']  # 가전 제품의 위치
        self.get_logger().info(f'Moving to position: {position} and executing {command} command on appliance with UUID: {appliance_uuid}')
        # 위치 이동 및 명령 실행 로직 구현

def main(args=None):
    rclpy.init(args=args)
    node = CommandExecutorNode()
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        node.scheduler.shutdown()
    finally:
        node.destroy_node()
        rclpy.shutdown()

if __name__ == '__main__':
    main()