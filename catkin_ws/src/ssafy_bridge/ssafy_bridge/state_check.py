import os
import signal
import subprocess
import time

# 상태에 따른 런치 파일 매핑
state_launch_file_map = {
    'patrol': 'patrol.py',
    'idle': 'idle.py',
    'scan': 'scan.py'
}

current_process = None

def read_robot_state():
    # ROBOT_STATE 값을 파일로부터 읽어오는 코드 예시
    try:
        with open("robot_state.txt", "r") as file:
            return file.read().strip()
    except FileNotFoundError:
        return None

def launch_file_for_state(state):
    global current_process
    if current_process:
        # Windows에서 taskkill 명령을 사용하여 프로세스와 그 하위 프로세스를 종료
        subprocess.call(['taskkill', '/F', '/T', '/PID', str(current_process.pid)])
        current_process.terminate()
        current_process.wait()

    launch_file = state_launch_file_map.get(state)
    if launch_file:
        print(f"Launching {launch_file} for state '{state}'...")
        current_process = subprocess.Popen(["ros2", "launch", "test_209", launch_file])

def main():
    last_state = None
    while True:
        state = read_robot_state()
        if state != last_state:
            launch_file_for_state(state)
            last_state = state
        time.sleep(1)

if __name__ == '__main__':
    main()