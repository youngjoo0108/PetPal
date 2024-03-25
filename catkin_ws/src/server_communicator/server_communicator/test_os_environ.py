import os

# os.environ['LOG_RABBITMQ_ID'] = 'admin'
# os.environ['LOG_RABBITMQ_PW'] = 'claris1234'
# os.environ['LOG_RABBITMQ_HOST'] = 'j10a209.p.ssafy.io'
# os.environ['LOG_RABBITMQ_PORT'] = '4885'

print(os.environ.get('LOG_RABBITMQ_ID'))
print(os.environ.get('LOG_RABBITMQ_PW'))
print(os.environ.get('LOG_RABBITMQ_HOST'))
print(os.environ.get('LOG_RABBITMQ_PORT'))




### test stomp_ws_py
# from stomp_ws.client import Client
# import argparse
# import asyncio
# import websockets
# import stomper

# async def connect():
#   ws_url = f"https://{os.environ.get('LOG_RABBITMQ_HOST')}/api/ws"
#   async with websockets.connect(ws_url) as websocket:
#       sub_offer = stomper.subscribe("/exchange/control.exchange/user.209", idx="209")
#       await websocket.send(sub_offer)

#       sub_ice = stomper.subscribe("/exchange/control.exchange/user.209", idx="209")
#       await websocket.send(sub_ice)

#       send = stomper.send("/app/initiate", "1234")
#       await websocket.send(send)

#       while True:
#           message = await websocket.recv()
#           print(f"Received message" + message)


'''
import os
import rclpy
from rclpy.node import Node
from std_msgs.msg import String
import stomp
import time

class StompPublisher(Node):
    def __init__(self):
        super().__init__('stomp_publisher')
        self.subscription = self.create_subscription(
            String,
            'ros/data',
            self.listener_callback,
            10)
        self.subscription  # prevent unused variable warning

        self.conn = stomp.Connection([('j10a209.p.ssafy.io', 4885)])
        self.conn.set_listener('', MyListener())
        self.conn.connect('admin', 'claris1234', wait=True)

    def listener_callback(self, msg):
        self.get_logger().info('I heard: "%s"' % msg.data)
        try:
            self.conn.send(body=msg.data, destination='/topic/rosdata')
        except Exception as e:
            self.get_logger().error(f"STOMP message send error: {e}")

    def __del__(self):
        self.conn.disconnect()

class MyListener(stomp.ConnectionListener):
    def on_error(self, frame):
        print('Received an error: "%s"' % frame.body)

    def on_message(self, frame):
        print('Received a message: "%s"' % frame.body)

def main(args=None):
    rclpy.init(args=args)
    stomp_publisher = StompPublisher()
    rclpy.spin(stomp_publisher)

    stomp_publisher.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()
'''

'''
import stomp
import time

class StompClient:
    def __init__(self, host, port, user_id):
        self.host = host
        self.port = port
        self.user_id = user_id
        self.conn = stomp.Connection([(self.host, self.port)])
        self.conn.set_listener('', MyListener())
        self.conn.connect(wait=True)

    def subscribe(self):
        subscription_url = f"/exchange/control.exchange/user.{self.user_id}"
        self.conn.subscribe(destination=subscription_url, id=1, ack='auto')

    def send_message(self, message):
        destination_queue = f"/pub/control.message.{self.user_id}"
        self.conn.send(body=message, destination=destination_queue)

    def disconnect(self):
        self.conn.disconnect()

class MyListener(stomp.ConnectionListener):
    def on_error(self, frame):
        print('Received an error: "%s"' % frame.body)

    def on_message(self, frame):
        print('Received a message: "%s"' % frame.body)

if __name__ == '__main__':
    user_id = "random_value"  # 임의의 값 설정
    client = StompClient(host="j10a209.p.ssafy.io", port=8081, user_id=user_id)
    client.subscribe()
    
    # 잠시 대기 후 메시지 전송 (STOMP 연결 및 구독 설정에 시간이 필요할 수 있음)
    time.sleep(2)
    client.send_message("Hello, World!")
    
    # 데모를 위한 대기 시간 후 연결 해제
    time.sleep(10)
    client.disconnect()
'''