
import asyncio
import websockets
import stomper
import nest_asyncio
import json
import base64
import cv2
import numpy as np
import time

nest_asyncio.apply()

msg = {"type":"control", "sender":"user_1", "message":"msg"}

async def connect():
    ws_url = f"wss://j10a209.p.ssafy.io/api/ws" 
    async with websockets.connect(ws_url, max_size = 2**20, max_queue = 2**5) as websocket:
        await websocket.send("CONNECT\naccept-version:1.0,1.1,2.0\n\n\x00\n")

        sub_offer = stomper.subscribe("/exchange/control.exchange/home.1", "user.1")
        await websocket.send(sub_offer)


        # while True:
             
        #     print("send msg")
        #     time.sleep(3)
        
        while True:
            # print("try")
            message = await websocket.recv()
            
            if message:
                # print(message) 
                try:                    
                    message = message.rstrip('\0')
                    
                    json_start = message.find('{')

                    # JSON 데이터만 추출합니다. (-1을 하지 않으면 마지막 괄호를 놓칠 수 있음)
                    json_data = message[json_start:]
                    
                    # JSON 본문을 파싱합니다.
                    message_data = json.loads(json_data)
                    

                    # print(f"Received message type: {message_data['type']}")

                    if message_data.get("type") == "video_streaming":
                        display_image_from_base64(message_data['message'])
                    else:
                        print(message_data)
                except json.JSONDecodeError as e:
                    print(f"JSON decode error: {e}")
                except ValueError as e:
                    print(f"Error processing message: {e}")
            else:
                print("Received an empty message.")



def display_image_from_base64(base64_string):
    # Base64 문자열을 바이트로 디코딩합니다.
    img_bytes = base64.b64decode(base64_string)
    
    # 바이트 배열을 numpy 배열로 변환합니다.
    np_arr = np.frombuffer(img_bytes, np.uint8)
    
    # numpy 배열을 이미지로 디코딩합니다.
    img = cv2.imdecode(np_arr, cv2.IMREAD_COLOR)
    
    # 이미지를 화면에 표시합니다.
    cv2.imshow('Received Image', img)
    cv2.waitKey(1)  # 화면을 갱신하고, 키 입력을 대기합니다.

if __name__ == '__main__':
    asyncio.get_event_loop().run_until_complete(connect())
