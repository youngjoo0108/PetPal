import json
import websocket
import threading
import uuid
import datetime
import os

def on_message(ws, message):
    print("Received:", message)
    if message:  # 메시지가 비어있지 않은지 확인
        try:
            recv = json.loads(message)
            print(recv)
        except json.JSONDecodeError:
            print("Received non-JSON message:", message)
    else:
        print("Received an empty message")


def on_error(ws, error):
    print("Error:", error)
    

def on_close(ws, close_status_code, close_msg):
    print("### closed ###")
    print("Close status code:", close_status_code)
    print("Close message:", close_msg)
    
    
def on_open(ws):
    def run(*args):
        print("WebSocket Connected")
        # STOMP CONNECT 프레임 전송
        ws.send("CONNECT\naccept-version:1.2\n\n\x00")
        
        # 메시지 구독
        subscribe_frame = "SUBSCRIBE\nid:sub-0\ndestination:/exchange/control.exchange/user.209\n\n\x00"
        ws.send(subscribe_frame)
        
        # 메시지 전송
        session_nickname = "your_nickname"  # 실제 값으로 대체
        room_id = 209  # 실제 값으로 대체
        send_frame = f"SEND\ndestination:/pub/chat/message\n\n{json.dumps({'msgId': str(uuid.uuid4()), 'type': 'JOIN', 'sender': session_nickname, 'msgContent': f'{session_nickname} joined!', 'roomId': room_id, 'timestamp': datetime.datetime.now().isoformat()})}\x00"
        ws.send(send_frame)
        
        while True:
            pass

    thread = threading.Thread(target=run)
    thread.start()

if __name__ == "__main__":
    websocket.enableTrace(True)
    ws = websocket.WebSocketApp('wss://{url}/api/ws'.format(
                                    url=os.environ.get('LOG_RABBITMQ_HOST')
                                ),
                                on_message=on_message,
                                on_error=on_error,
                                on_close=on_close)
    ws.on_open = on_open
    ws.run_forever()
