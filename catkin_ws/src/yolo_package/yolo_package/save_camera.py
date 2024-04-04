#!/ C:\Python37\python.exe

import numpy as np
import cv2
import time
import os
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

current_dir = os.getcwd()
folder_name = 'images_data'

if not os.path.exists(os.path.join(current_dir, folder_name)):
    os.makedirs(os.path.join(current_dir, folder_name))


class IMGParser(Node):

    def __init__(self):
        super().__init__(node_name='image_convertor')
        print(current_dir)
        
        self.last_save_time = 0

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

        current_time = time.time()  # 현재 시간 가져오기
        if current_time - self.last_save_time >= 1:  # 마지막 저장 이후 1초 이상 경과했는지 확인
            # 이미지 저장
            save_path = os.path.join(current_dir, folder_name, f'image_{int(current_time)}.jpg')
            cv2.imwrite(save_path, img_bgr)  # 이미지 저장
            self.last_save_time = current_time  # 마지막 저장 시간 업데이트

        # 로직 5. 이미지 출력 (cv2.imshow)       
        
        cv2.imshow("img_bgr", img_bgr)
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