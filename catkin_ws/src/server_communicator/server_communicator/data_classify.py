import rclpy
from rclpy.node import Node
from ssafy_msgs.msg import IotCmd
from std_msgs.msg import String
import json
import logging
import time

from ros_log_package.RosLogPublisher import RosLogPublisher


obstacles= ['Knife', 'PenHolder', 'BookPile', 'Stapler', 'Mug']
furnitures = ['Plant', 'Chair', 'Table', 'BoxTable', 'BackPack', 'Bed', 'Sofa', 'Washer']
dogs = ['Dog']
humans = ['Person']
iots = ['AirConditioner', 'TV']

debug_mode = True

class DataClassifyNode(Node):
    def __init__(self):
        super().__init__('data_classify_node')
        
        self.ros_log_pub = None
        try:
            self.ros_log_pub = RosLogPublisher(self)
        except Exception as e:
            self.get_logger().error('ERROR', 'Subscription initialization error: {}'.format(e))
        
        try:
            self.publisher_yolo = self.create_publisher(String, 'captured_object', 10**3)
        except:
            self.ros_log_pub.publish_log('ERROR', 'init publisher yolo error: {}'.format(e))
            
        try:
            self.publisher_iot_control = self.create_publisher(IotCmd, '/iot_cmd', 10)
        except:
            self.ros_log_pub.publish_log('ERROR', 'init publisher iot control error: {}'.format(e))
        
        try:
            self.request_pub = self.create_publisher(String, '/request', 10)
        except:
            self.ros_log_pub.publish_log('ERROR', 'init publisher iot control error: {}'.format(e))
            
        try:
            self.data_subscription = self.create_subscription(
                String,
                '/data/classify',
                self.data_callback,
                10**3)
        except Exception as e:
            self.ros_log_pub.publish_log('ERROR', 'Subscription initialization error: {}'.format(e))


    def data_callback(self, msg):
        self.receive_messages(msg.data)
    
    def receive_messages(self, message):
        try:
            if debug_mode:
                print(f"Received message: {message}")
            
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
                        
                        topic_data = self.classification_object(obj_list)
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
                            'iot_uuid': topic_data[:slice_point],
                            'control_action': topic_data[slice_point + 1:]
                        }
                        print
                        msg = IotCmd()
                        msg.iot_uuid = iot_control_data['iot_uuid']
                        msg.control_action = iot_control_data['control_action']
                        print(msg)
                        self.publisher_iot_control.publish(msg)
                        self.ros_log_pub.publish_log('INFO', f'IoT control message enter : {msg}')
                    elif message_data.get('type') == "SCAN":
                        msg = String()
                        msg.data = 'scan_on'
                        self.request_pub.publish(msg)
                        self.ros_log_pub.publish_log('INFO', f'Scan start message enter : {msg}')
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
                    else:
                        self.ros_log_pub.publish_log('WARN', f'Not Defined message type enter : {msg}')
                        
                except json.JSONDecodeError as e:
                    self.ros_log_pub.publish_log('ERROR', f'Decode Json message error: {e}')
        except Exception as e:
            if debug_mode:
                print('ERROR', f'Receiving message error: {e}')
            self.ros_log_pub.publish_log('ERROR', f'Receiving message error: {e}')


    def classification_object(self, obj_list):
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
        
def main(args=None):
    rclpy.init(args=args)
    data_classify_node = DataClassifyNode()
    rclpy.spin(data_classify_node)
    data_classify_node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()
