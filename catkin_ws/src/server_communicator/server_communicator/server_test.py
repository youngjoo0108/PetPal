import websocket
import json
import asyncio
import websockets

def on_message(ws, message):
    print("Received: %s" % message)

def on_error(ws, error):
    print(error)

def on_close(ws, close_status_code, close_msg):
    print("### closed ###")

def on_open(ws):
    def run(*args):
        for i in range(3):
            message = json.dumps({'name': 'ROS2 User'})
            ws.send(message)
            print("Sent")
        ws.close()
    run()
    
async def hello():
    uri = "wss://j10a209.p.ssafy.io:8081"
    async with websockets.connect(uri) as websocket:
        await websocket.send("Hello world!")
        response = await websocket.recv()
        print(f"Received from server: {response}")

def main(args=None):
    try:
        asyncio.get_event_loop().run_until_complete(hello())
    except:
        print('websockets error')
        
    try:
        websocket.enableTrace(True)
        ws = websocket.WebSocketApp("ws://j10a209.p.ssafy.io:8081",
                                on_message = on_message,
                                on_error = on_error,
                                on_close = on_close)
        ws.on_open = on_open
        ws.run_forever()
    except:
        print('websocket error')
    
if __name__ == '__main__':
    main()