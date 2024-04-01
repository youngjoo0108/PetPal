import rclpy
from rclpy.node import Node
from sensor_msgs.msg import CompressedImage
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


obstacles= ['Knife', 'PenHolder', 'BookPile', 'Stapler', 'Mug']
furnitures = ['Plant', 'Chair', 'Table', 'BoxTable', 'BackPack', 'Bed', 'Sofa', 'Washer']
dogs = ['Dog']
humans = ['Person']
iots = ['AirConditioner', 'TV']

class WebSocketClientReceiveNode(Node):
    def __init__(self):
        super().__init__('websocket_client_receive_node')
        
        self.ros_log_pub = None
        try:
            self.ros_log_pub = RosLogPublisher(self)
        except Exception as e:
            self.get_logger().error('ERROR', 'Subscription initialization error: {}'.format(e))
        
        try:
            self.publisher_yolo = self.create_publisher(String, 'captured_object', 10)
        except:
            self.ros_log_pub.publish_log('ERROR', 'init publisher yolo error: {}'.format(e))
        
        self.ws_url = "wss://j10a209.p.ssafy.io/api/ws"
        self.websocket = None

        self.loop = asyncio.new_event_loop()
        threading.Thread(target=self.run_asyncio_loop, args=(self.loop,), daemon=True).start()

        asyncio.run_coroutine_threadsafe(self.receive_messages(), self.loop)
        
    def run_asyncio_loop(self, loop):
        asyncio.set_event_loop(loop)
        loop.run_forever()
        
    async def connect_websocket(self):
        try:
            self.websocket = await websockets.connect(self.ws_url, max_size=2**20, max_queue=2**5)
            await self.websocket.send("CONNECT\naccept-version:1.0,1.1,2.0\n\n\x00\n")
            sub_offer = stomper.subscribe("/exchange/control.exchange/home.1", "user.2")
            await self.websocket.send(sub_offer)
        except Exception as e:
            self.ros_log_pub.publish_log('ERROR', 'WebSocket connection error: {}'.format(e))
            self.websocket = None # 변경: 연결 실패 시 websocket을 None으로 설정
            
    async def ensure_websocket_connected(self):
        if self.websocket is None or self.websocket.closed:
            await self.connect_websocket() # 변경: 웹소켓이 연결되지 않았거나 닫혀있으면 재연결 시도
            self.ros_log_pub.publish_log('INFO', f"connected {time.strftime('%X', time.localtime())}")
    
    # {
        # 'type': 'yolo_data', 
        # 'sender': 'user_1', 
        # 'time': '13:50:20', 
        # 'message': '{
            # "list": [
                # "13:50:20/Chair/0.94%/254-200/336-357",
                # "13:50:20/Chair/0.82%/310-227/364-354",
                # "13:50:20/Chair/0.79%/308-228/391-348"
            # ]
        # }'
    # }
    
    async def receive_messages(self):
        while True:
            try:
                await self.ensure_websocket_connected()
                
                message = await self.websocket.recv()
                # print(f"Received message: {message}")
                
                if message:
                    try:
                        message = message.rstrip('\0')
                        json_start = message.find('{')
                        json_data = message[json_start:]
                        message_data = json.loads(json_data)
                        
                        if message_data.get('type') == "yolo_data":
                            # print("yolo")
                            obj_list = json.loads(message_data['message'])
                            obj_list = obj_list['list']
                            
                            topic_data = await self.classification_object(obj_list)
                            json_str = json.dumps(topic_data)
                            msg = String()
                            msg.data = json_str
                            # print('send list:', json_str)
                            self.publisher_yolo.publish(msg)
                        else:
                            print(message_data)
                    except json.JSONDecodeError as e:
                        self.ros_log_pub.publish_log('ERROR', f'Decode Json message error: {e}')
            except Exception as e:
                self.ros_log_pub.publish_log('ERROR', f'Receiving message error: {e}')
                self.websocket = None  # 연결 오류 시 websocket을 None으로 재설정


    async def classification_object(self, obj_list):
        # print("object list:")
        # print(obj_list)
        obstacle_list = []
        furniture_list = []
        dog_list = []
        human_list = []
        iot_list = []
        
        for obj in obj_list:
            start_type = obj.find('/')
            end_type = obj.find('/', start_type+1)

            obj_type = obj[start_type+1 : end_type]
                
            if obj_type in obstacles:
                obstacle_list.append(obj)
            elif obj_type in furnitures:
                furniture_list.append(obj)
            elif obj_type in dogs:
                dog_list.append(obj)
            elif obj_type in humans:
                human_list.append(obj)
            elif obj_type in iots:
                iot_list.append(obj)
            
            topic_data = {
                'obstacle_list': obstacle_list,
                'furniture_list': furniture_list,
                'dog_list': dog_list,
                'human_list': human_list,
                'iot_list': iot_list
            }
        return topic_data
    
    # async def obj_component(self):
    #     return time_str + '/' + class_list[label] + '/'+str(round(confidence, 2)) + '%' + '/' + str(xmin) + '-' + str(ymin) + '/' + str(xmax) + '-' + str(ymax)
        
def main(args=None):
    rclpy.init(args=args)
    websocket_client_node = WebSocketClientReceiveNode()
    rclpy.spin(websocket_client_node)
    websocket_client_node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()
