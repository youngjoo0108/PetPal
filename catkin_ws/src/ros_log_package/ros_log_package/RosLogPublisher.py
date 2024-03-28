# log_helper.py
from std_msgs.msg import String
import json

class RosLogPublisher:
    def __init__(self, node):
        """
        node: 로그를 발행할 ROS 2 노드의 인스턴스
        """
        print("Log init")
        self.node = node
        self.publisher_ = self.node.create_publisher(String, 'ros_log', 10)
        self.logger = self.node.get_logger()
        print("Log start")

    def publish_log(self, msg_level, log_message):
        """ros_log 토픽으로 로그 메시지를 발행합니다."""
        if(msg_level == 'DEBUG'):
            self.logger.debug(f'[{log_message}]')  # 콘솔에 로그 기록
        elif(msg_level == 'WARN'):
            self.logger.warn(f'[{log_message}]')  # 콘솔에 로그 기록
        elif(msg_level == 'ERROR'):
            self.logger.error(f'[{log_message}]')  # 콘솔에 로그 기록
        elif(msg_level == 'FATAL'):
            self.logger.fatal(f'[{log_message}]')  # 콘솔에 로그 기록
        else:
            self.logger.info(f'[{msg_level}][{log_message}]')  # 콘솔에 로그 기록
            log_message = f'{msg_level}-{log_message}'
            msg_level = 'INFO'
        
        
        msg = String()
        log_json = {
            'level': msg_level,
            'message': log_message
        }
        msg.data = json.dumps(log_json)
        self.publisher_.publish(msg)  # ros_log 토픽으로 메시지 발행