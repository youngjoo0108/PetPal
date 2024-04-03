import rclpy
from rclpy.node import Node
from sensor_msgs.msg import CompressedImage
from ssafy_msgs.msg import IotCmd
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
        logging.basicConfig(level=logging.DEBUG) 
        self.ros_log_pub = None
        try:
            self.ros_log_pub = RosLogPublisher(self)
        except Exception as e:
            self.get_logger().error('ERROR', 'Subscription initialization error: {}'.format(e))
            
        try:
            self.publisher_data_classify = self.create_publisher(String, '/data/classify', 10**3)
        except:
            self.ros_log_pub.publish_log('ERROR', 'init publisher_data_classify error: {}'.format(e))
        
        '''
        # try:
        #     self.publisher_yolo = self.create_publisher(String, 'captured_object', 10)
        # except:
        #     self.ros_log_pub.publish_log('ERROR', 'init publisher yolo error: {}'.format(e))
            
        # try:
        #     self.publisher_iot_control = self.create_publisher(IotCmd, '/iot_cmd', 10)
        # except:
        #     self.ros_log_pub.publish_log('ERROR', 'init publisher iot control error: {}'.format(e))

        # try:
        #     self.request_pub = self.create_publisher(String, '/request', 10)
        # except:
        #     self.ros_log_pub.publish_log('ERROR', 'init publisher request error: {}'.format(e))
        
        try:
            self.request_pub = self.create_publisher(String, '/request', 10)
        except:
            self.ros_log_pub.publish_log('ERROR', 'init publisher iot control error: {}'.format(e))
        
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
            self.websocket = await websockets.connect(self.ws_url, max_size=2**20, max_queue=2**7)
            await self.websocket.send("CONNECT\naccept-version:1.0,1.1,2.0\n\n\x00\n")
            
            sub_offer1 = stomper.subscribe("/exchange/control.exchange/home.2", "home.2")
            await self.websocket.send(sub_offer1)
            sub_offer2 = stomper.subscribe("/exchange/control.exchange/home.2.yolo", "user.2")
            await self.websocket.send(sub_offer2)
            
        except Exception as e:
            self.ros_log_pub.publish_log('ERROR', 'WebSocket connection error: {}'.format(e))
            self.websocket = None # 변경: 연결 실패 시 websocket을 None으로 설정
            
    async def ensure_websocket_connected(self):
        if self.websocket is None or self.websocket.closed:
            await self.connect_websocket() # 변경: 웹소켓이 연결되지 않았거나 닫혀있으면 재연결 시도
            self.ros_log_pub.publish_log('INFO', f"connected {time.strftime('%X', time.localtime())}")
    
    async def receive_messages(self):
        while True:
            try:
                await self.ensure_websocket_connected()
                
                message = await self.websocket.recv()
                # print(f"Received message: {message}")
                
                if message:
                    #print(message)
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
                            self.ros_log_pub.publish_log('INFO', f'Object detected message enter : {msg}')
                        elif message_data.get('type') == "IOT":
                            topic_data = message_data['message']
                            slice_point = topic_data.find('/')
                            iot_control_data = {
                                'iot_uuid': topic_data[:slice_point - 1],
                                'control_action': topic_data[slice_point + 1:]
                            }
                            
                            msg = IotCmd()
                            msg.iot_uuid = iot_control_data['iot_uuid']
                            msg.control_action = iot_control_data['control_action']
                            
                            self.publisher_iot_control.publish(msg)
                            #print(message_data)
                        elif message_data.get('type') == "SCAN":
                            msg = String()
                            msg.data = "scan_on"
                            self.request_pub.publish(msg)
                            #print('scan')
                        elif message_data.get('type') == "REGISTER_REQUEST":
                            msg = IotCmd()
                            msg.iot_uuid = ""
                            msg.control_action = "register"
                            self.publisher_iot_control.publish(msg)
                        elif message_data.get('type') == "MODE":
                            mode_data = message_data['message']
                            msg = String()
                            if mode_data == "stay":
                                msg.data = "off"
                            else:
                                msg.data = mode_data + "_on"
                            self.request_pub.publish(msg)
                        elif message_data.get('type') == "HOMEID":
                            homeId = message_data['message']
                            full_path = 'C:\\Users\\SSAFY\\Desktop\\\S10P22A209\\catkin_ws\\src\\test_209\\homeId.txt'
                            f=open(full_path,'w')
                            data=homeId
                            f.write(data)
                            f.close()

                            
                            
                    except json.JSONDecodeError as e:
                        self.ros_log_pub.publish_log('ERROR', f'Decode Json message error: {e}')
            except Exception as e:
                self.ros_log_pub.publish_log('ERROR', f'Receiving message error: {e}')
                self.websocket = None  # 연결 오류 시 websocket을 None으로 재설정
    
    '''
    # async def receive_messages(self):
    #     while True:
    #         try:
    #             await self.ensure_websocket_connected()
                
    #             message = await self.websocket.recv()
                
    #             if debug_mode:
    #                 print(f"Received message: {message}")
                
    #             if message:
    #                 #print(message)
    #                 try:
    #                     message = message.rstrip('\0')
    #                     json_start = message.find('{')
    #                     json_data = message[json_start:]
    #                     message_data = json.loads(json_data)
                        
    #                     if message_data.get('type') == "yolo_data":
    #                         # print("yolo")
    #                         obj_list = json.loads(message_data['message'])
    #                         obj_list = obj_list['list']
                            
    #                         topic_data = await self.classification_object(obj_list)
    #                         json_str = json.dumps(topic_data)
    #                         msg = String()
    #                         msg.data = json_str
    #                         # print('send list:', json_str)
    #                         self.publisher_yolo.publish(msg)
    #                         self.ros_log_pub.publish_log('INFO', f'Object detected message enter : {msg}')
    #                     elif message_data.get('type') == "IOT":
    #                         topic_data = message_data['message']
    #                         slice_point = topic_data.find('/')
    #                         iot_control_data = {
    #                             'iot_uuid': topic_data[:slice_point - 1],
    #                             'control_action': topic_data[slice_point + 1:]
    #                         }
                            
    #                         msg = IotCmd()
    #                         msg.iot_uuid = iot_control_data['iot_uuid']
    #                         msg.control_action = iot_control_data['control_action']
                            
    #                         self.publisher_iot_control.publish(msg)
    #                         #print(message_data)
    #                     elif message_data.get('type') == "SCAN":
    #                         msg = String()
    #                         msg.data = "scan_on"
    #                         self.request_pub.publish(msg)
    #                         #print('scan')
    #                     elif message_data.get('type') == "REGISTER_REQUEST":
    #                         msg = IotCmd()
    #                         msg.iot_uuid = ""
    #                         msg.control_action = "register"
    #                         self.publisher_iot_control.publish(msg)
    #                     elif message_data.get('type') == "MODE":
    #                         mode_data = message_data['message']
    #                         msg = String()
    #                         if mode_data == "stay":
    #                             msg.data = "off"
    #                         else:
    #                             msg.data = mode_data + "_on"
    #                         self.request_pub.publish(msg)
    #                     elif message_data.get('type') == "HOMEID":
    #                         homeId = message_data['message']
    #                         full_path = 'C:\\Users\\SSAFY\\Desktop\\\S10P22A209\\catkin_ws\\src\\test_209\\homeId.txt'
    #                         f=open(full_path,'w')
    #                         data=homeId
    #                         f.write(data)
    #                         f.close()

                            
                            
    #                 except json.JSONDecodeError as e:
    #                     self.ros_log_pub.publish_log('ERROR', f'Decode Json message error: {e}')
    #         except Exception as e:
    #             if debug_mode:
    #                 print('ERROR', f'Receiving message error: {e}')
    #             self.ros_log_pub.publish_log('ERROR', f'Receiving message error: {e}')
    #             self.websocket = None  # 연결 오류 시 websocket을 None으로 재설정


    # async def classification_object(self, obj_list):
    #     # print("object list:")
    #     # print(obj_list)
    #     obstacle_list = []
    #     furniture_list = []
    #     dog_list = []
    #     human_list = []
    #     iot_list = []
        
    #     for obj in obj_list:
    #         start_type = obj.find('/')
    #         end_type = obj.find('/', start_type+1)

    #         obj_type = obj[start_type+1 : end_type]
                
    #         if obj_type in obstacles:
    #             obstacle_list.append(obj)
    #         elif obj_type in furnitures:
    #             furniture_list.append(obj)
    #         elif obj_type in dogs:
    #             dog_list.append(obj)
    #         elif obj_type in humans:
    #             human_list.append(obj)
    #         elif obj_type in iots:
    #             iot_list.append(obj)
            
        #     topic_data = {
        #         'obstacle_list': obstacle_list,
        #         'furniture_list': furniture_list,
        #         'dog_list': dog_list,
        #         'human_list': human_list,
        #         'iot_list': iot_list
        #     }
        # return topic_data
        
def main(args=None):
    rclpy.init(args=args)
    websocket_client_node = WebSocketClientReceiveNode()
    rclpy.spin(websocket_client_node)
    websocket_client_node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()
