def write_robot_state(state):
    # ROBOT_STATE 값을 파일로 기록하는 코드 예시
    with open("robot_state.txt", "w") as file:
        file.write(state)

def main():
    while True:
        print("Enter new state ('patrol', 'idle', 'scan'): ", end="")
        state = input().strip()
        if state in ['patrol', 'idle', 'scan']:
            write_robot_state(state)
        else:
            print("Invalid state. Please enter 'patrol', 'idle', or 'scan'.")

if __name__ == '__main__':
    main()