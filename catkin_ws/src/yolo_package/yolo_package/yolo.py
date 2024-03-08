#!/ C:\Python37\python.exe

import numpy as np
import cv2
from ultralytics import YOLO
import rclpy
from rclpy.node import Node

from sensor_msgs.msg import CompressedImage

# image parser 노드는 이미지를 받아서 opencv 의 imshow로 윈도우창에 띄우는 역할을 합니다.
# 이를 resize나 convert를 사용하여 이미지를 원하는대로 바꿔보세요.

# 노드 로직 순서
# 1. image subscriber 생성
# 2. 카메라 콜백함수에서 compressed image 디코딩
# 3. 이미지 색 채널을 gray scale로 컨버팅
# 4. 이미지 resizing
# 5. 이미지 imshow


CONFIDENCE_THRESHOLD = 0.6
GREEN = (0, 255, 0)
WHITE = (255, 255, 255)

class_txt = open('C:/Users/SSAFY/Desktop/S10P22A209/catkin_ws/src/yolo_package/classes/classes_v2.txt', 'r')
data = class_txt.read()
class_list = data.split('\n')
class_txt.close()

model = YOLO('C:/Users/SSAFY/Desktop/S10P22A209/catkin_ws/src/yolo_package/model/my_model_small_2.pt') 



class IMGParser(Node):

    def __init__(self):
        super().__init__(node_name='image_convertor')

        # 로직 1. image subscriber 생성
        ## 아래와 같이 subscriber가 
        ## 미리 정의된 토픽 이름인 '/image_jpeg/compressed' 에서
        ## CompressedImage 메시지를 받도록 설정된다.

        try:
            self.subscription = self.create_subscription(
                CompressedImage,
                '/image_jpeg/compressed',
                self.img_callback,
                10)
        except:
            print('init error')
        

    def img_callback(self, msg):

        # 로직 2. 카메라 콜백함수에서 이미지를 클래스 내 변수로 저장
        ## msg.data 는 bytes로 되어 있고 이를 uint8로 바꾼 다음
        ## cv2 내의 이미지 디코딩 함수로 bgr 이미지로 바꾸세요.        

        np_arr = np.frombuffer(msg.data, np.uint8)
        img_bgr = cv2.imdecode(np_arr, cv2.IMREAD_COLOR)
        # print("np_arr's type: ", type(np_arr))
        # print("np_arr's sizw: ", np_arr.shape)
        # print("img_bgr's type: ", type(img_bgr))
        # print("img_bgr's sizw: ", img_bgr.shape)
        '''
        로직 3. 이미지 색 채널을 gray scale로 컨버팅
        cv2. 내의 이미지 색 채널 컨터버로 bgr 색상을 gary scale로 바꾸십시오.

        img_gray = 

        '''

        '''
        로직 4. 이미지 resizing
        cv2를 사용해서 이미지를 원하는 크기로 바꿔보십시오.

        img_resize = 
        '''
        
        results = model(img_bgr)
        detection = results[0]  # 탐지된 객체 정보

        for data in detection.boxes.data.tolist(): # data : [xmin, ymin, xmax, ymax, confidence_score, class_id]
            # print(data)
            confidence = float(data[4])
            if confidence < CONFIDENCE_THRESHOLD:
                continue

            xmin, ymin, xmax, ymax = int(data[0]), int(data[1]), int(data[2]), int(data[3])
            label = int(data[5])
            cv2.rectangle(img_bgr, (xmin, ymin), (xmax, ymax), GREEN, 2)
            cv2.putText(img_bgr, class_list[label]+' '+str(round(confidence, 2)) + '%', (xmin, ymin), cv2.FONT_ITALIC, 0.5, WHITE, 1)
        # 로직 5. 이미지 출력 (cv2.imshow)       
        
        re_img = cv2.resize(img_bgr, (0, 0), fx=2, fy=2, interpolation=cv2.INTER_NEAREST)
        
        cv2.imshow("re_img", re_img)
        # cv2.imshow("img_gray", img_gray)
        # cv2.imshow("resize and gray", img_resize)       
        
        cv2.waitKey(1)


def main(args=None):

    ## 노드 초기화 : rclpy.init 은 node의 이름을 알려주는 것으로, ROS master와 통신을 가능하게 해줍니다.
    rclpy.init(args=args)
    
    print('step 1')

    ## 메인에 돌릴 노드 클래스 정의 
    image_parser = IMGParser()
    print('step 2')

    ## 노드 실행 : 노드를 셧다운하기 전까지 종료로부터 막아주는 역할을 합니다
    rclpy.spin(image_parser)
    print('step 3')


if __name__ == '__main__':

    main()