import rclpy
from rclpy.node import Node
from std_msgs.msg import String
import asyncio
import websockets
import threading
import stomper
import json
import base64
import logging
import time

from ros_log_package.RosLogPublisher import RosLogPublisher


class WebSocketClientSendNode(Node):
    def __init__(self):
        super().__init__('websocket_client_send_node')
        #logging.basicConfig(level=logging.DEBUG) 
        self.ros_log_pub = None
        try:
            self.ros_log_pub = RosLogPublisher(self)
        except Exception as e:
            self.get_logger().error('ERROR', 'Subscription initialization error: {}'.format(e))
            
        try:
            self.data_subscription = self.create_subscription(
                String,
                'to_server/encode_data',
                self.data_callback,
                10**3)
        except Exception as e:
            self.ros_log_pub.publish_log('ERROR', 'Subscription initialization error: {}'.format(e))   
        
        '''try:
            self.video_subscription = self.create_subscription(
                CompressedImage,
                '/image_jpeg/compressed',
                self.video_callback,
                10)
        except Exception as e:
            self.ros_log_pub.publish_log('ERROR', 'Subscription initialization error: {}'.format(e))
             
        try:
            self.data_subscription = self.create_subscription(
                String,
                '/to_server/data',
                self.data_callback,
                20)
        except Exception as e:
            self.ros_log_pub.publish_log('ERROR', 'Subscription initialization error: {}'.format(e))'''
            
        self.loop = asyncio.new_event_loop()
        threading.Thread(target=self.run_asyncio_loop, args=(self.loop,), daemon=True).start()
        
        self.ws_url = "wss://j10a209.p.ssafy.io/api/ws"
        self.websocket = None
        
        
    def run_asyncio_loop(self, loop):
        asyncio.set_event_loop(loop)
        loop.run_forever()
        
    async def connect_websocket(self):
        try:
            self.websocket = await websockets.connect(self.ws_url, max_size=2**20, max_queue=2**5)
            await self.websocket.send("CONNECT\naccept-version:1.0,1.1,2.0\n\n\x00\n")
            # sub_offer = stomper.subscribe("/exchange/control.exchange/user.1", "user.1")
            # await self.websocket.send(sub_offer)
        except Exception as e:
            self.ros_log_pub.publish_log('ERROR', 'WebSocket connection error: {}'.format(e))
            self.websocket = None # 변경: 연결 실패 시 websocket을 None으로 설정
            
    async def ensure_websocket_connected(self):
        if self.websocket is None or self.websocket.closed:
            await self.connect_websocket() # 변경: 웹소켓이 연결되지 않았거나 닫혀있으면 재연결 시도
            self.ros_log_pub.publish_log('INFO', f"connected {time.strftime('%X', time.localtime())}")
    
    # {'type': 'yolo_data', 'sender': 'user_1', 'time': '13:50:20', 'message': '{"list": ["13:50:20/Chair/0.94%/254-200/336-357", "13:50:20/Chair/0.82%/310-227/364-354", "13:50:20/Chair/0.79%/308-228/391-348"]}'}
            
    async def send_message(self, msg):
        await self.ensure_websocket_connected() # 변경: 메시지 전송 전에 웹소켓 연결 상태 확인
        try:
            if(msg[0] == 'D'):
                send = stomper.send("/pub/ros.control.message.2", msg[1:])
            elif(msg[0] == 'V'):
                send = stomper.send("/pub/images.stream.2.images", msg[1:])    
        except:
            self.ros_log_pub.publish_log('ERROR', f"wrong encoded data {msg}")
            
        await self.websocket.send(send)
        
    '''async def send_video(self, video_image):
        try:
            video_image_base64 = base64.b64encode(video_image).decode('utf-8')
            now = time.localtime()
            msg = {
                "type": "video_streaming", 
                "sender": "user_1",
                "time": time.strftime('%X', now),
                "message": video_image_base64
            }
            
            await self.ensure_websocket_connected() # 변경: 메시지 전송 전에 웹소켓 연결 상태 확인
            # send = stomper.send("/pub/images.stream.2.images", json.dumps(msg))
            # await self.websocket.send(send)
            
            # print("sended image")
        except Exception as e:
            self.ros_log_pub.publish_log('ERROR', 'Sending video error: {}'.format(e))
            self.websocket = None # 변경: 오류 발생 시 websocket을 None으로 재설정하여 재연결 로직을 트리거
    
    async def send_data(self, data_msg):
        try:
            now = time.localtime()
            json_data = json.loads(data_msg)
            
            msg = {
                "type": json_data['type'], 
                "sender": "user_1",
                "time": time.strftime('%X', now),
                "message": json_data['message']
            }
            await self.send_message(msg) # 변경: send_message 함수를 통해 메시지 전송
        except Exception as e:
            self.ros_log_pub.publish_log('ERROR', 'Sending video error: {}'.format(e))
            self.websocket = None'''
    
    # def video_callback(self, msg):
    #     asyncio.run_coroutine_threadsafe(self.send_video(msg.data), self.loop) # 변경 없음
        
    def data_callback(self, msg):
        asyncio.run_coroutine_threadsafe(self.send_message(msg.data), self.loop) # 변경 없음
        
def main(args=None):
    rclpy.init(args=args)
    websocket_client_node = WebSocketClientSendNode()
    rclpy.spin(websocket_client_node)
    websocket_client_node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()