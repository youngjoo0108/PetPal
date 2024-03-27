# import json
# import base64

# # 주어진 JSON 문자열
# json_str = {"type": "video_streaming", "sender": "user_1", "message": "/9j/4AAQSkZJRgABAQAAAQABAAD/2wBDAAEBAQEBAQEBAQEBAQEBAQEBAQEBAQEBAQEBAQEBAQEBAQEBAQEBAQEBAQEBAQEBAQEBAQEBAQEBAQEBAQEBAQH/2wBDAQEBAQEBAQEBAQEBAQEBAQEBAQEBAQEBAQEBAQEBAQEBAQEBAQEBAQEBAQEBAQEBAQEBAQEBAQEBAQEBAQEBAQH/wAARCADwAUADASIAAhEBAxEB/8QAHwAAAQUBAQEBAQEAAAAAAAAAAAECAwQFBgcICQoL/Z"}

# # # JSON 문자열을 파이썬 객체로 변환
# # data = json.loads(json_str)

# # Base64 인코딩된 이미지 데이터 추출
# base64_image_data = json_str['message']

# print(base64_image_data)

# # Base64 데이터 디코딩
# image_data = base64.b64decode(base64_image_data)

# # # 이미지 파일로 저장
# # with open('output_image.jpg', 'wb') as file:
# #     file.write(image_data)

# print("이미지 파일이 저장되었습니다.")

import json
import time

# JSON 문자열
json_string = '{"type":"control","sender":"user_1","message":"Hello Buddy CActus"}'

# 문자열을 파이썬 딕셔너리로 파싱
parsed_data = json.loads(json_string)
print(type(parsed_data))

print(parsed_data['type'])

now = time.localtime()
print(time.strftime('%X', now))