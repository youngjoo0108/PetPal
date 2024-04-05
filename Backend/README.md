# Ref
## Python Websocket Client Test Code

    import asyncio
    import websockets
    import stomper
    import nest_asyncio
    import json

    nest_asyncio.apply()
    # 메시지 타입
    msg = {"type":"control", "sender":"user_1", "message":"msg"}

    async def connect():
        # url 넣기
        ws_url = f"wss://{petpal_url}"
        async with websockets.connect(ws_url) as websocket:
            await websocket.send("CONNECT\naccept-version:1.0,1.1,2.0\n\n\x00\n")

            sub_offer = stomper.subscribe("/exchange/control.exchange/user.1", "user.1")
            await websocket.send(sub_offer)

            send = stomper.send("/pub/control.message.1", json.dumps(msg))
            await websocket.send(send)
            
            while True:
                print("try")
                message = await websocket.recv()

                print(f"Received message" + message)

    if __name__ == '__main__':
        asyncio.get_event_loop().run_until_complete(connect())
