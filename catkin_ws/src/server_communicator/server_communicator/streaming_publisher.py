import rclpy
from rclpy.node import Node
from sensor_msgs.msg import CompressedImage
import cv2
import numpy as np

class StreamingPublisher(Node):
    def __init__(self):
        super().__init__('streaming_publisher')
        self.publisher_ = self.create_publisher(CompressedImage, '/image_jpeg/compressed', 10)
        self.timer = self.create_timer(1.0, self.timer_callback)  # 초당 1회 발행

    def timer_callback(self):
        # OpenCV를 사용하여 이미지 로드
        cv_image = cv2.imread('path_to_your_image.jpg')

        # CompressedImage 메시지 생성
        msg = CompressedImage()
        msg.header.stamp = self.get_clock().now().to_msg()
        msg.format = "jpeg"  # 이미지 포맷
        msg.data = np.array(cv2.imencode('.jpg', cv_image)[1]).tostring()

        # 토픽에 이미지 메시지 발행
        self.publisher_.publish(msg)
        self.get_logger().info('Publishing compressed image')

def main(args=None):
    rclpy.init(args=args)
    streaming_publisher = StreamingPublisher()
    rclpy.spin(streaming_publisher)
    streaming_publisher.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()
