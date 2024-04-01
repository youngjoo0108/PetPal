import os
import random

# 대상 폴더 지정
target_folder = r'C:\Users\SSAFY\images_data'

# 폴더 내의 모든 파일 목록 가져오기
files = os.listdir(target_folder)

def RandomName():
    name_list = []
    for i in range(len(files)):
        name_list.append(i + 1)
    
    for file in files:
        # 파일의 전체 경로 구성
        file_path = os.path.join(target_folder, file)
        
        # 파일 확장자 유지
        extension = os.path.splitext(file)[1]
        
        new_name = name_list.pop(random.randrange(0, len(name_list)))
        
        # 새 파일 이름 설정 (예: "1.jpg")
        new_file_name = f"000{new_name}{extension}"
        new_file_path = os.path.join(target_folder, new_file_name)
        
        # 파일 이름 변경
        os.rename(file_path, new_file_path)
    
        
def Rename_normal():
    # 파일 이름을 숫자로 변경하기 시작
    start_number = 1

    for file in files:
        # 파일의 전체 경로 구성
        file_path = os.path.join(target_folder, file)
        
        # 파일 확장자 유지
        extension = os.path.splitext(file)[1]
        
        # 새 파일 이름 설정 (예: "1.jpg")
        new_file_name = f"{start_number}{extension}"
        new_file_path = os.path.join(target_folder, new_file_name)
        
        # 파일 이름 변경
        os.rename(file_path, new_file_path)
        
        # 숫자 증가
        start_number += 1
        
        
if __name__=="__main__":
    #Rename_normal()
    
    # print(type(files))
    # print(len(files))
    # print(files)
    
    RandomName()
    
    print("All files have been renamed.")