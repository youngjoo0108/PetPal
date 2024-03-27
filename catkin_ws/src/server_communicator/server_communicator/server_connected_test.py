# import json
# import websocket
# import threading
# import os
# import time

# class WebSocketClient:
#     def __init__(self, url, username, password, isSendMessage=True):
#         self.url = url
#         self.username = username
#         self.password = password
#         self.isSendMessage = isSendMessage
#         self.ws = None

#     def on_message(self, ws, message):
#         print(f"---Received by {self.username}:", message)
#         if message:
#             try:
#                 recv = json.loads(message)
#                 print(recv, "\n\n")
#             except json.JSONDecodeError:
#                 print("Received non-JSON message:", message)
#         else:
#             print("Received an empty message")

#     def on_error(self, ws, error):
#         print("Error:", error)

#     def on_close(self, ws, close_status_code, close_msg):
#         print(f"### closed {self.username} ###")
#         print("Close status code:", close_status_code)
#         print("Close message:", close_msg)

#     # def on_open(self, ws):
#     #     def run(*args):
#     #         print(f"WebSocket Connected: {self.username}")
#     #         # STOMP CONNECT 프레임 전송
#     #         host = ""
#     #         cx, cy = 0, 0
#     #         ws.send(f"CONNECT\naccept-version:1.1\nhost:{host}\nheart-beat:{cx},{cy}\nlogin:{self.username}\npasscode:{self.password}\n\n\x00\n")
            
#     #         # 메시지 구독
#     #         subscribe_frame = "SUBSCRIBE\nid:1\ndestination:/exchange/control.exchange/user.1\n\n\x00"
#     #         ws.send(subscribe_frame)
            
#     #         if self.isSendMessage:
#     #             while True:
#     #                 # 메시지 전송
#     #                 send_data = {
#     #                     "type": "control",
#     #                     "sender": self.username,
#     #                     "message": "Send Message Test"
#     #                 }
#     #                 send_frame = f"SEND\ndestination:/pub/control.message.1\n\n{json.dumps(send_data)}\x00"
#     #                 ws.send(send_frame)
                    
#     #                 time.sleep(3)

#     #     thread = threading.Thread(target=run)
#     #     thread.daemon = True
#     #     thread.start()
    
#     def on_open(self, ws):
#         def run(*args):
#             print(f"WebSocket Connected: {self.username}")
#             # STOMP CONNECT 프레임 전송
#             host = ""
#             cx, cy = 0, 0
#             ws.send(f"CONNECT\naccept-version:1.1\nhost:{host}\nheart-beat:{cx},{cy}\nlogin:{self.username}\npasscode:{self.password}\n\n\x00\n")
            
#             # 메시지 구독을 client_1과 client_2가 동일한 대상으로 설정
#             # 예: "/exchange/control.exchange/user.1" 대신 공통 대상 사용
#             subscribe_frame = "SUBSCRIBE\nid:{self.username}\ndestination:/exchange/control.exchange/user.1\n\n\x00"  # 동일한 경로로 수정
#             ws.send(subscribe_frame)
            
#             if self.isSendMessage:
#                 while True:
#                     # 메시지 전송
#                     send_data = {
#                         "type": "control",
#                         "sender": self.username,
#                         "message": "Send Message Test"
#                     }
#                     send_frame = f"SEND\ndestination:/pub/control.message.1\n\n{json.dumps(send_data)}\x00"  # 발신 대상 경로 일치
#                     ws.send(send_frame)
                    
#                     time.sleep(3)

#         thread = threading.Thread(target=run)
#         thread.daemon = True
#         thread.start()

#     def run_forever(self):
#         self.ws = websocket.WebSocketApp(self.url,
#                                          on_message=self.on_message,
#                                          on_error=self.on_error,
#                                          on_close=self.on_close)
#         self.ws.on_open = lambda ws: self.on_open(ws)
#         threading.Thread(target=self.ws.run_forever, daemon=True).start()

# def start_clients():
#     websocket.enableTrace(True)
#     ws_host = os.environ.get('LOG_RABBITMQ_HOST', 'localhost')

#     client_1 = WebSocketClient(f'wss://{ws_host}/api/ws', "Cactus", "a029", True)
#     time.sleep(2)
#     # client_2 = WebSocketClient(f'wss://{ws_host}/api/ws', "Receiver", "b029", False)

#     client_1.run_forever()
#     # client_2.run_forever()

#     # Keep the main thread running, otherwise signals are ignored.
#     while True:
#         time.sleep(1)

# if __name__ == "__main__":
#     start_clients()



import asyncio
import websockets
import stomper
import nest_asyncio
import json
import time

nest_asyncio.apply()

msg = {"type":"control", "sender":"user_1", "message":"msg"}

async def connect():
    ws_url = f"wss://j10a209.p.ssafy.io/api/ws"
    async with websockets.connect(ws_url) as websocket:
        await websocket.send("CONNECT\naccept-version:1.0,1.1,2.0\n\n\x00\n")

        sub_offer = stomper.subscribe("/exchange/control.exchange/user.1", "user.10")
        await websocket.send(sub_offer)

        # send = stomper.send("/pub/control.message.1", json.dumps(msg))
        # await websocket.send(send)
        
        while True:
            # print("try")
            # message = await websocket.recv()

            # print(f"Received message" + message)
            send = stomper.send("/pub/control.message.1", json.dumps(msg))
            await websocket.send(send)
            
            time.sleep(3)

if __name__ == '__main__':
    asyncio.get_event_loop().run_until_complete(connect())
