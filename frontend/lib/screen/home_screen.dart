import 'package:flutter/material.dart';
import 'package:flutter_secure_storage/flutter_secure_storage.dart';
import 'package:frontend/component/stream/camera_screen.dart';
import 'package:frontend/component/stream/map_screen.dart';
import 'package:frontend/component/weather/weather_screen.dart';
import 'package:frontend/const/colors.dart';
import 'package:frontend/socket/socket.dart';
import 'package:logger/logger.dart';

final Logger logger = Logger();

class HomeScreen extends StatefulWidget {
  const HomeScreen({super.key});

  @override
  State<HomeScreen> createState() => _HomeScreenState();
}

class _HomeScreenState extends State<HomeScreen> {
  bool isOn = false;
  bool isPatrollingMode = true;
  final FlutterSecureStorage secureStorage = const FlutterSecureStorage();
  SocketService socketService = SocketService();

  @override
  void initState() {
    socketService.initializeWebSocketConnection();
    super.initState();
  }

  @override
  Widget build(BuildContext context) {
    return SafeArea(
      child: Column(
        children: [
          const WeatherScreen(),
          Padding(
            padding: const EdgeInsets.symmetric(horizontal: 15),
            child: Row(
              mainAxisAlignment: MainAxisAlignment.spaceBetween,
              children: <Widget>[
                // ON/OFF 토글
                Row(
                  children: [
                    GestureDetector(
                      onTap: () async {
                        final String? homeId =
                            await secureStorage.read(key: "homeId");
                        if (homeId != null) {
                          // 메시지 전송 로직
                          socketService.sendMessage(
                            destination: '/pub/control.message.$homeId',
                            type: 'MODE',
                            messageContent: 'patrol',
                          );
                          // UI 상태 업데이트
                          setState(() {
                            isOn = true;
                          });
                        } else {
                          logger.e("Home ID not found");
                        }
                      },
                      child: Container(
                        padding: const EdgeInsets.symmetric(
                            vertical: 8.0, horizontal: 16.0),
                        decoration: BoxDecoration(
                          color: isOn ? deepYellow : Colors.grey[100],
                          borderRadius: const BorderRadius.only(
                            topLeft: Radius.circular(10.0),
                            bottomLeft: Radius.circular(10.0),
                          ),
                        ),
                        child: const Text(
                          'ON',
                          style: TextStyle(
                            color: black,
                            fontSize: 14.0,
                            fontWeight: FontWeight.w600,
                          ),
                        ),
                      ),
                    ),
                    GestureDetector(
                      onTap: () async {
                        final String? homeId =
                            await secureStorage.read(key: "homeId");
                        if (homeId != null) {
                          // 메시지 전송 로직
                          socketService.sendMessage(
                            destination: '/pub/control.message.$homeId',
                            type: 'MODE',
                            messageContent: 'stay',
                          );
                          // UI 상태 업데이트
                          setState(() {
                            isOn = false;
                          });
                        } else {
                          logger.e("Home ID not found");
                        }
                      },
                      child: Container(
                        padding: const EdgeInsets.symmetric(
                            vertical: 8.0, horizontal: 16.0),
                        decoration: BoxDecoration(
                          color: !isOn ? deepYellow : Colors.grey[100],
                          borderRadius: const BorderRadius.only(
                            topRight: Radius.circular(10.0),
                            bottomRight: Radius.circular(10.0),
                          ),
                        ),
                        child: const Text(
                          'OFF',
                          style: TextStyle(
                            color: black,
                            fontSize: 14.0,
                            fontWeight: FontWeight.w600,
                          ),
                        ),
                      ),
                    ),
                  ],
                ),
                // 트래킹모드/순찰 모드 토글
                if (isOn) ...[
                  SizedBox(
                    height: 36,
                    width: 110,
                    child: TextButton(
                      onPressed: () async {
                        final String? homeId =
                            await secureStorage.read(key: "homeId");
                        final String message =
                            isPatrollingMode ? "patrol" : "tracking";
                        if (homeId != null) {
                          // 메시지 전송 로직
                          socketService.sendMessage(
                            destination: '/pub/control.message.$homeId',
                            type: 'MODE',
                            messageContent: message,
                          );
                          // UI 상태 업데이트
                          setState(() {
                            isPatrollingMode = !isPatrollingMode;
                          });
                        } else {
                          logger.e("Home ID not found");
                        }
                      },
                      style: ButtonStyle(
                        backgroundColor: MaterialStateProperty.all(deepYellow),
                        shape:
                            MaterialStateProperty.all<RoundedRectangleBorder>(
                          RoundedRectangleBorder(
                            borderRadius: BorderRadius.circular(10.0),
                          ),
                        ),
                      ),
                      child: Text(
                        isPatrollingMode ? '트래킹 모드' : '순찰 모드',
                        style: const TextStyle(
                          color: black,
                          fontSize: 14.0,
                          fontWeight: FontWeight.bold,
                        ),
                      ),
                    ),
                  ),
                ],
              ],
            ),
          ),
          Expanded(
            child: SingleChildScrollView(
              child: Container(
                margin: const EdgeInsets.only(top: 10),
                decoration: BoxDecoration(
                  color: Colors.white, // 컨테이너 배경색
                  boxShadow: [
                    BoxShadow(
                      color: Colors.grey.withOpacity(0.5), // 그림자 색상
                      spreadRadius: 3, // 그림자 범위
                      blurRadius: 4, // 그림자 흐림 효과
                      offset: const Offset(0, 3), // 그림자 위치 조정
                    ),
                  ],
                  borderRadius: const BorderRadius.only(
                    topLeft: Radius.circular(20.0), // 상단 왼쪽 둥근 처리
                    topRight: Radius.circular(20.0), // 상단 오른쪽 둥근 처리
                  ),
                ),
                child: !isOn
                    ? _buildOffMessage()
                    : const Column(
                        mainAxisAlignment: MainAxisAlignment.start,
                        crossAxisAlignment: CrossAxisAlignment.stretch,
                        children: [
                          SizedBox(
                            height: 300, // CameraScreen 높이
                            child: CameraScreen(),
                          ),
                          SizedBox(
                            height: 420, // MapScreen 높이
                            child: MapScreen(),
                          ),
                        ],
                      ),
              ),
            ),
          ),
        ],
      ),
    );
  }

  Widget _buildOffMessage() {
    return const SizedBox(
      height: 500,
      child: Center(
        child: Text(
          '기기가 동작중이지 않습니다.',
          style: TextStyle(
            fontSize: 18.0,
            fontWeight: FontWeight.bold,
            color: black,
          ),
        ),
      ),
    );
  }
}
