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

from ros_log_package.RosLogPublisher import RosLogPublisher



debug_mode = True

class SendDataClassifyNode(Node):
    def __init__(self):
        super().__init__('send_data_classify_node')
        self.half_frame = True
        
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
            
    
    def video_callback(self, video_image):
        try:
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
