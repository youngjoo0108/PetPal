# import asyncio << 오류난 코드
# import websockets
# import stomper
# import json

# async def stomp_over_websocket():
#     ws_url = "wss://j10a209.p.ssafy.io/api/ws"
#     async with websockets.connect(ws_url) as ws:
#         # STOMP CONNECT 프레임 전송
#         connect_frame = stomper.connect("user", "guest", "guest")  # 수정 필요
#         await ws.send(connect_frame)
        
#         # 구독
#         sub_frame = stomper.subscribe("/exchange/control.exchange/user.1", idx=1, ack=auto)
#         await ws.send(sub_frame)
        
#         # 메시지 전송
#         send_frame = stomper.send("/pub/control.message", json.dumps({"type": "control", "sender": "##", "message": "@@@"}))
#         await ws.send(send_frame)
        
#         # 메시지 수신 대기
#         message = await ws.recv()
#         print(f"Received message: {message}")

asyncio.get_event_loop().run_until_complete(stomp_over_websocket())


# from websocket import create_connection
# import json

# # 웹소켓 서버 URL
# ws_url = "wss://j10a209.p.ssafy.io/api/ws"

# # 구독할 주소 및 메시지 전송 (STOMP 프로토콜 형식에 맞춰 구성해야 함)
# # 예제에서는 STOMP over WebSocket을 직접 구현하는 것이 아니므로, 실제 메시지 형식과 프로토콜에 따라 조정해야 함
# # 웹소켓 연결 시 헤더 추가 예제
# # headers = {
# #     "Origin": "https://j10a209.p.ssafy.io",
# #     # 필요한 경우 추가 헤더를 여기에 추가
# # }
# # 웹소켓 연결
# # ws = create_connection(ws_url, header=headers)
# ws = create_connection(ws_url)

# # 이하 코드는 기존과 동일
# subscribe_message = json.dumps({
#     "type": "subscribe",
#     "destination": "/exchange/control.exchange/user.1"
# })
# ws.send(subscribe_message)

# # 메시지 수신 대기 및 처리
# while True:
#     result = ws.recv()
#     print("Received message: %s" % result)

# # 연결 종료
# ws.close()

import asyncio
import websockets
import stomper

class StompClient:
    def __init__(self, url):
        self.url = url
        self.ws = None

    async def connect(self):
        self.ws = await websockets.connect(self.url, max_size=None)
        connect_frame = stomper.connect("guest", "guest", host="")
        await self.ws.send(connect_frame)

    async def subscribe(self, destination):
        subscribe_frame = stomper.subscribe(destination, idx=1)
        await self.ws.send(subscribe_frame)

    async def receive(self):
        while True:
            message = await self.ws.recv()
            print(f"Received message: {message}")

    async def start(self):
        await self.connect()
        await self.subscribe("/exchange/control.exchange/user.1")
        await self.receive()

if __name__ == "__main__":
    stomp_client = StompClient("wss://j10a209.p.ssafy.io/api/ws")
    asyncio.get_event_loop().run_until_complete(stomp_client.start())


# import socket
# import json

# def send_stomp_message(host, port, subscription_url, destination_queue, message):
#     # STOMP 프레임 형식에 맞게 메시지 준비
#     connect_frame = f"CONNECT\naccept-version:1.2\nhost:{host}\n\n\x00".encode('utf-8')
#     subscribe_frame = f"SUBSCRIBE\nid:sub-0\ndestination:{subscription_url}\n\n\x00".encode('utf-8')
#     send_frame = f"SEND\ndestination:{destination_queue}\ncontent-type:application/json\n\n{message}\x00".encode('utf-8')
#     disconnect_frame = "DISCONNECT\n\n\x00".encode('utf-8')

#     with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
#         s.connect((host, port))
        
#         # STOMP 프로토콜을 통한 메시지 전송 순서
#         print("1")
#         s.sendall(connect_frame)
#         print("2")
#         s.sendall(subscribe_frame)
#         print("3")
#         s.sendall(send_frame)
#         print("4")
#         s.sendall(disconnect_frame)
#         print("5")
        
#         # 서버로부터의 응답 받기 (선택적)
#         # response = s.recv(1024)
#         # print('Received', repr(response))

# if __name__ == "__main__":
#     host = 'j10a209.p.ssafy.io'  # WebSocket 대신 사용할 서버의 실제 IP 혹은 도메인을 입력하세요.
#     port = 443  # STOMP 기본 포트는 61613입니다. 실제 환경에 맞게 조정하세요.
    
#     # 구독 및 대상 큐 URL
#     subscription_url = "/exchange/control.exchange/user.209"
#     destination_queue = "/pub/control.message.209"
    
#     # 보낼 메시지
#     message_dict = {
#         "type": "control",
#         "sender": "##",
#         "message": "@@@"
#     }
#     message_json = json.dumps(message_dict)
    
#     send_stomp_message(host, port, subscription_url, destination_queue, message_json)


# """
# Author: srinivas.kumarr

# Python client for interacting with a server via STOMP over websockets.
# """

# import websocket
# import stomper
# import queue

# # Since we are Using SockJS fallback on the server side we are directly subscribing to Websockets here.
# # Else the url up-till notifications would have been sufficient.

# class StompClient(object):
#     """Class containing methods for the Client."""

#     # Notifications queue, which will store all the mesaages we receive from the server.
#     NOTIFICATIONS = None

#     #Do note that in this case we use jwt_token for authentication hence we are 
#     #passing the same in the headers, else we can pass encoded passwords etc. 
#     def __init__(self, destinations=[]):
#         """
#         Initializer for the class.

#         Args:
#         jwt_token(str): JWT token to authenticate.
#         server_ip(str): Ip of the server.
#         port_number(int): port number through which we want to make the
#                             connection.
#         destinations(list): List of topics which we want to subscribe to.

#         """
#         self.NOTIFICATIONS = queue.Queue()
#         self.headers = {}
#         self.ws_uri = 'j10a209.p.ssafy.io/api/ws'
#         self.destinations = destinations

#     @staticmethod
#     def on_open(self, ws):
#         """
#         Handler when a websocket connection is opened.

#         Args:
#         ws(Object): Websocket Object.

#         """
#         #Iniitial CONNECT required to initialize the server's client registries.
#         ws.send("CONNECT\naccept-version:1.0,1.1,2.0\n\n\x00\n")
        
#         # Subscribing to all required desitnations. 
#         for destination in self.destinations:
#             sub = stomper.subscribe(destination, "209", ack="auto")
#             ws.send(sub)

#     def create_connection(self):
#         """
#         Method which starts of the long term websocket connection.
#         """

#         ws = websocket.WebSocketApp(self.ws_uri, header=self.headers,
#                                     on_message=self.on_msg,
#                                     on_error=self.on_error,
#                                     on_close=self.on_closed)
#         ws.on_open = self.on_open
        
#         # Run until interruption to client or server terminates connection. 
#         ws.run_forever()

#     def add_notifications(self, msg):
#         """
#         Method to add a message to the websocket queue.

#         Args:
#         msg(dict): Unpacked message received from stomp watches.

#         """
#         self.NOTIFICATIONS.put(msg)

#     def on_msg(self, msg):
#         """
#         Handler for receiving a message.

#         Args:
#         msg(str): Message received from stomp watches.

#         """
#         frame = stomper.Frame()
#         unpacked_msg = stomper.Frame.unpack(frame, msg)
#         print("Received the message: " + str(unpacked_msg))
#         self.add_notifications(unpacked_msg)

#     def on_error(self, err):
#         """
#         Handler when an error is raised.

#         Args:
#         err(str): Error received.

#         """
#         print("The Error is:- " + err)

#     def on_closed(self):
#         """
#         Handler when a websocket is closed, ends the client thread.
#         """
#         print("The websocket connection is closed.")
        
        
# if __name__ == "__main__":
#     myOne = StompClient(["/exchange/control.exchange/user.209"])



# import argparse
# import asyncio
# import websockets
# import stomper
# import json

# async def connect():
#     ws_url = "wss://j10a209.p.ssafy.io/api/ws"
#     async with websockets.connect(ws_url) as websocket:
#         connect_frame = stomper.connect("guest", "guest", host="")
#         await websocket.send(connect_frame)

#         sub_frame = stomper.subscribe("/exchange/control.exchange/user.1", id="sub-1")
#         await websocket.send(sub_frame)

#         while True:
#             message = await websocket.recv()
#             print(f"Received message: {message}")

#             # 메시지 전송
#             send_data = {
#                 "type": "control",
#                 "sender": "##",
#                 "message": "@@@"
#             }
#             send_frame = stomper.send("/pub/control.message.1", json.dumps(send_data))
#             await websocket.send(send_frame)

# if __name__ == '__main__':
#     asyncio.get_event_loop().run_until_complete(connect())