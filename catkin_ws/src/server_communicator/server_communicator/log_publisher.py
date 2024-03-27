#It is for Send data to Server
import rclpy
from rclpy.node import Node

from std_msgs.msg import String
import pika
import json
import os


class LogPublisher(Node):

    def __init__(self):
        super().__init__('_subscriber')
        
        try:
            rabbitmq_user = os.environ.get('LOG_RABBITMQ_ID')
            rabbitmq_password = os.environ.get('LOG_RABBITMQ_PW')
            rabbitmq_host = os.environ.get('LOG_RABBITMQ_HOST')
            rabbitmq_port = os.environ.get('LOG_RABBITMQ_PORT')
            
            print(rabbitmq_user)
            print(rabbitmq_password)
            print(rabbitmq_host)
            print(rabbitmq_port)
            
            amqp_url = 'amqp://{user}:{password}@{hostname}:{port}/'.format(
                user=rabbitmq_user,
                password=rabbitmq_password,
                hostname=rabbitmq_host,
                port=rabbitmq_port
            )
            
            print(amqp_url)
            
            url_params = pika.URLParameters(amqp_url)
            print(url_params)

            self.amqp_connection = pika.BlockingConnection(url_params)
            self.amqp_channel = self.amqp_connection.channel()

            self.amqp_channel.queue_declare(queue='log_queue')
            
            print('Log Publisher : connecting RabbitMQ Clear')
            
            test_data = {
                "level": "INFO",
                "message": "This is a log message from ROS2."
            }
            self.amqp_callback(test_data)
        except Exception as e:
            print('Log Publisher : connecting RabbitMQ Error')
            print(e)
            
        
        try:
            self.subscription = self.create_subscription(
                String,
                'ros_log',
                self.log_callback,
                10)
            self.subscription  # prevent unused variable warning
            print('Log Publisher : subscript inner log topic Clear')
        except Exception as e:
            print('Log Publisher : subscript inner log topic Error')
            print(e)


    def amqp_callback(self, log_data): ### <<< log_data 설정 필요함
        # log_data = {
        #     "level": "INFO",
        #     "message": "This is a log message from ROS2."
        # }
        log_message = json.dumps(log_data)
        
        self.amqp_channel.basic_publish(exchange='', ### <<< 교환기 이름 정하고, 설정 필요함
                                   routing_key='log_queue', ### <<< 메세지가 전달될 큐의 이름 교환기를 정한다면 필요 없을지도?
                                   body=log_message)
        self.get_logger().info('Log message sent to RabbitMQ: %s' % log_message)


    def log_callback(self, msg):
        log_data = {"level": "INFO", "message": msg.data}  # msg.data를 직접 사용
        self.amqp_callback(log_data)  # 수정된 호출 방식
        self.get_logger().info('I heard: "%s"' % msg.data)


def main(args=None):
    rclpy.init(args=args)

    #data publisher createde
    log_publisher = LogPublisher()

    #execute class objects.
    rclpy.spin(log_publisher)

    log_publisher.destroy_node()
    log_publisher.amqp_connection.close()
    rclpy.shutdown()

if __name__ == '__main__':
    main()