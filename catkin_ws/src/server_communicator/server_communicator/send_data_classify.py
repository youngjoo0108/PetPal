import rclpy
from rclpy.node import Node
from ssafy_msgs.msg import IotCmd
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
import requests

from ros_log_package.RosLogPublisher import RosLogPublisher



debug_mode = True

# 서버의 엔드포인트 주소
# endpoint = "http://localhost:8081/api/v1/images"
base_endpoint = "https://j10a209.p.ssafy.io/api/v1/"
# 파일 확장자명
params = {'homeId':2,'extension': 'png'}

class SendDataClassifyNode(Node):
    def __init__(self):
        super().__init__('send_data_classify_node')
        self.half_frame = True
        
        self.screenShot = False
        
        # # 서버의 엔드포인트 주소
        # # endpoint = "http://localhost:8081/api/v1/images"
        # base_endpoint = "https://j10a209.p.ssafy.io/api/v1/"
        # # 파일 확장자명
        # params = {'homeId':2,'extension': 'png'}
        # self.screenShot_type = ''
        # self.screenShot_position = {
        #     "x": 209,
        #     "y": 209
        # }
        
        self.ros_log_pub = None
        try:
            self.ros_log_pub = RosLogPublisher(self)
        except Exception as e:
            self.get_logger().error('ERROR', 'Subscription initialization error: {}'.format(e))
        
        try:
            self.publisher_data = self.create_publisher(String, 'to_server/encode_data', 10**3)
        except:
            self.ros_log_pub.publish_log('ERROR', 'init publisher encode_data error: {}'.format(e))
            
        try:
            self.video_subscription = self.create_subscription(
                CompressedImage,
                '/image_jpeg/compressed',
                self.video_callback,
                10**3)
        except Exception as e:
            self.ros_log_pub.publish_log('ERROR', 'Subscription initialization error: {}'.format(e))
             
        try:
            self.data_subscription = self.create_subscription(
                String,
                '/to_server/data',
                self.data_callback,
                10**3)
        except Exception as e:
            self.ros_log_pub.publish_log('ERROR', 'Subscription initialization error: {}'.format(e))
            
        try:
            self.save_camera_subscription = self.create_subscription(
                String,
                '/screen_shot/recall',
                self.save_camera_callback,
                10)
        except Exception as e:
            self.ros_log_pub.publish_log('ERROR', 'Subscription initialization error: {}'.format(e))
            
        try:
            self.publisher_save_camera = self.create_publisher(CompressedImage, '/screen_shot/pub', 10)
        except Exception as e:
            self.ros_log_pub.publish_log('ERROR', 'init publisher save_camera error: {}'.format(e))
            
    def save_camera_callback(self, msg):
        self.screenShot = True
        encode_msg = json.loads(msg.data)
        self.screenShot_type = encode_msg['type']
        self.screenShot_position = encode_msg['position']
            
    
    def video_callback(self, video_image):
        try:
            if self.screenShot:
                self.screenShot = False
                try:
                    self.publisher_save_camera.publish(video_image)
                except Exception as e:
                    self.ros_log_pub.publish_log('ERROR', 'Publisher save_camera error: {}'.format(e))


                # # POST 요청을 보내 URL과 image_id 받아오기
                # response = requests.post(base_endpoint+"images", json=params)
                # if response.status_code == 200:
                #     data = response.json()
                #     upload_url = data['presignedURL']
                #     image_id = data['imageId']
                #     if debug_mode:
                #         print(f"Received upload URL: {upload_url}")
                #         print(f"Image ID: {image_id}")
                # else:
                #     if debug_mode:
                #         print("Failed to get upload URL and Image ID")
                #     # 에러 처리


                # # # S3 업로드 파트
                # # file_path = "C:/Users/SSAFY/Desktop/과제2.PNG" # 여기에 전송할 사진의 절대경로

                # # with open(file_path, 'rb') as f:
                # #     # 파일의 바이너리 데이터를 PUT 요청의 본문으로 전송
                # upload_response = requests.put(upload_url, data=video_image.data)


                # if upload_response.status_code == 200:
                #     print("Upload successful")
                # else:
                #     print(upload_response.status_code)
                #     print("Upload failed")



                # # Target 생성
                # params = {
                #             'homeId':2,
                #             'imageId':image_id,
                #             'objectType':self.screenShot_type, 
                #             "coordinate":self.screenShot_position
                #         }
                # response = requests.post(base_endpoint+"images", json=params)
                # target_id = int(response.text)
                
            
            if self.half_frame:
                video_image_base64 = base64.b64encode(video_image.data).decode('utf-8')
                now = time.localtime()
                msg = {
                    "type": "video_streaming", 
                    "sender": "user_1",
                    "time": time.strftime('%X', now),
                    "message": video_image_base64
                }
                msg_string = String()
                msg_string.data = 'V' + json.dumps(msg)
                
                self.publisher_data.publish(msg_string)
                self.half_frame = False
            else:
                self.half_frame = True
        except Exception as e:
            self.ros_log_pub.publish_log('ERROR', 'Sending video error: {}'.format(e))
    
    def data_callback(self, data_msg):
        try:
            now = time.localtime()
            json_data = json.loads(data_msg.data)
            
            msg = {
                "type": json_data['type'], 
                "sender": "user_1",
                "time": time.strftime('%X', now),
                "message": json_data['message']
            }
            msg_string = String()
            msg_string.data = 'D' + json.dumps(msg)
            
            self.publisher_data.publish(msg_string)
        except Exception as e:
            self.ros_log_pub.publish_log('ERROR', 'Sending data error: {}'.format(e))


        
def main(args=None):
    rclpy.init(args=args)
    send_data_classify_node = SendDataClassifyNode()
    rclpy.spin(send_data_classify_node)
    send_data_classify_node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()
