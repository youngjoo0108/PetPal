# log_helper.py
from std_msgs.msg import String

class RosLogPublisher:
    def __init__(self, node):
        """
        node: 로그를 발행할 ROS 2 노드의 인스턴스
        """
        print("Log init")
        self.node = node
        self.publisher_ = self.node.create_publisher(String, 'ros_log', 10)
        print("Log start")

    def publish_log(self, log_message):
        """ros_log 토픽으로 로그 메시지를 발행합니다."""
        self.node.get_logger().info(log_message)  # 콘솔에 로그 기록
        msg = String()
        msg.data = log_message
        self.publisher_.publish(msg)  # ros_log 토픽으로 메시지 발행