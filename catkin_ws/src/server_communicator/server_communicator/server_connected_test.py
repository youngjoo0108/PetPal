import json
import websocket
import threading
import os
import time

class WebSocketClient:
    def __init__(self, url, username, password, isSendMessage=True):
        self.url = url
        self.username = username
        self.password = password
        self.isSendMessage = isSendMessage
        self.ws = None

    def on_message(self, ws, message):
        print(f"---Received by {self.username}:", message)
        if message:
            try:
                recv = json.loads(message)
                print(recv, "\n\n")
            except json.JSONDecodeError:
                print("Received non-JSON message:", message)
        else:
            print("Received an empty message")

    def on_error(self, ws, error):
        print("Error:", error)

    def on_close(self, ws, close_status_code, close_msg):
        print(f"### closed {self.username} ###")
        print("Close status code:", close_status_code)
        print("Close message:", close_msg)

    def on_open(self, ws):
        def run(*args):
            print(f"WebSocket Connected: {self.username}")
            # STOMP CONNECT 프레임 전송
            host = ""
            cx, cy = 0, 0
            ws.send(f"CONNECT\naccept-version:1.1\nhost:{host}\nheart-beat:{cx},{cy}\nlogin:{self.username}\npasscode:{self.password}\n\n\x00\n")
            
            # 메시지 구독
            subscribe_frame = "SUBSCRIBE\nid:subscription-{self.username}\ndestination:/exchange/control.exchange/user.209\n\n\x00"
            ws.send(subscribe_frame)
            
            if self.isSendMessage:
                while True:
                    # 메시지 전송
                    send_data = {
                        "type": "control",
                        "sender": self.username,
                        "message": "Send Message Test"
                    }
                    send_frame = f"SEND\ndestination:/pub/control.message.209\n\n{json.dumps(send_data)}\x00"
                    ws.send(send_frame)
                    
                    time.sleep(3)

        thread = threading.Thread(target=run)
        thread.daemon = True
        thread.start()

    def run_forever(self):
        self.ws = websocket.WebSocketApp(self.url,
                                         on_message=self.on_message,
                                         on_error=self.on_error,
                                         on_close=self.on_close)
        self.ws.on_open = lambda ws: self.on_open(ws)
        threading.Thread(target=self.ws.run_forever, daemon=True).start()

def start_clients():
    # websocket.enableTrace(True)
    ws_host = os.environ.get('LOG_RABBITMQ_HOST', 'localhost')

    client_1 = WebSocketClient(f'wss://{ws_host}/api/ws', "Cactus", "a029", True)
    client_2 = WebSocketClient(f'wss://{ws_host}/api/ws', "Receiver", "b029", False)

    client_1.run_forever()
    client_2.run_forever()

    # Keep the main thread running, otherwise signals are ignored.
    while True:
        time.sleep(1)

if __name__ == "__main__":
    start_clients()
