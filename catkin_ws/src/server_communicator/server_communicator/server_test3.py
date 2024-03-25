import websocket
import stomper
import queue
import json

class StompClient(object):
    def __init__(self, destinations=[]):
        self.NOTIFICATIONS = queue.Queue()
        # self.headers = {}  # 여기서 필요한 경우 JWT 토큰 등의 인증 헤더를 추가할 수 있습니다.
        self.ws_uri = "wss://j10a209.p.ssafy.io/api/ws"  # WebSocket Secure 연결
        self.destinations = destinations

    def on_open(self, ws):
        ws.send("CONNECT\naccept-version:1.0,1.1,2.0\n\n\x00\n")
        
        for destination in self.destinations:
            sub = stomper.subscribe(destination, "209", ack="auto")
            ws.send(sub)
        
        # 예시 메시지 전송 로직 추가
        send_data = {
            "type": "control",
            "sender": "##",
            "message": "@@@"
        }
        send_frame = stomper.send("/pub/control.message.209", json.dumps(send_data))
        ws.send(send_frame)

    def create_connection(self):
        ws = websocket.WebSocketApp(self.ws_uri, header=self.headers,
                                    on_message=self.on_msg,
                                    on_error=self.on_error,
                                    on_close=self.on_closed)
        ws.on_open = lambda ws_instance: self.on_open(ws_instance)
        ws.run_forever()

    def add_notifications(self, msg):
        self.NOTIFICATIONS.put(msg)

    def on_msg(self, ws, msg):
        frame = stomper.Frame()
        unpacked_msg = frame.unpack(msg)
        print("Received the message: " + str(unpacked_msg))
        self.add_notifications(unpacked_msg)

    def on_error(self, ws, err):
        print("The Error is:- ")
        print(err)

    def on_closed(self, ws):
        print("The websocket connection is closed.")

if __name__ == "__main__":
    destinations = ["/exchange/control.exchange/user.209"]
    client = StompClient(destinations)
    client.create_connection()
