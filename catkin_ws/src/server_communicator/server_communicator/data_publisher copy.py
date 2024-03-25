#It is for Send data to Server
import rclpy
from rclpy.node import Node

from std_msgs.msg import String
import json
import stomp
import os


class DataPublisher(Node):

    def __init__(self):
        super().__init__('data_publisher')
        self.subscription = self.create_subscription(
            String,
            'ros/data',
            self.listener_callback,
            10)
        self.subscription  # prevent unused variable warning
        
        try:
            self.server_host = 'wss://{url}/api/ws'.format(
                    url=os.environ.get('LOG_RABBITMQ_HOST')
                )
            self.user_id = 209
            self.conn = stomp.Connection([(self.server_host, 6163)])
            self.conn.set_listener('', MyListener())
            self.conn.connect(wait=True)
            print('Data Publisher : Connecting Stomp Clear')
        except Exception as e:
            print('Data Publisher : Connecting Stomp Error')
            print(e)
            
            
        try:
            subscription_url = f"/exchange/control.exchange/user.{self.user_id}"
            self.conn.subscribe(destination=subscription_url, id=1, ack='auto')
            print('Data Publisher : Stomp Subscribe Clear')
        except Exception as e:
            print('Data Publisher : Stomp Subscribe Error')
            print(e)
            
            
        try:
            test_data = {
                "type" : "control",
                "sender" : "##",
                "message" : "@@@"
            }
            self.send_message(json.dumps(test_data))
        except Exception as e:
            print('Data Publisher : Send Test Message Error')
            print(e)

    def listener_callback(self, msg):
        self.get_logger().info('I heard: "%s"' % msg.data)
        try:
            self.send_message(msg)
        except Exception as e:
            self.get_logger().error(f"STOMP message send error: {e}")
            

    def send_message(self, message):
        try:
            destination_queue = f"/pub/control.message.{self.user_id}"
            self.conn.send(body=message, destination=destination_queue)
            print('Data Publisher : Send Message Clear')
        except Exception as e:
            print('Data Publisher : Send Message Error')
            print(e)
        
    def __del__(self):
        self.conn.disconnect()
        
        
class MyListener(stomp.ConnectionListener):
    def on_error(self, frame):
        print('Received an error: "%s"' % frame.body)

    def on_message(self, frame):
        print('Received a message: "%s"' % frame.body)


def main(args=None):
    rclpy.init(args=args)
    stomp_publisher = DataPublisher()
    rclpy.spin(stomp_publisher)

    stomp_publisher.conn.disconnect()
    stomp_publisher.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()