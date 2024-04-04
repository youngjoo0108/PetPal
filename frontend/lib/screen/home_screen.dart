import 'package:flutter/material.dart';
import 'package:flutter_secure_storage/flutter_secure_storage.dart';
import 'package:frontend/component/stream/camera_screen.dart';
import 'package:frontend/component/stream/map_screen.dart';
import 'package:frontend/component/weather/weather_screen.dart';
import 'package:frontend/const/colors.dart';
import 'package:frontend/const/global_alert_dialog.dart';
import 'package:frontend/controller/device_controller.dart';
import 'package:frontend/socket/socket.dart';
import 'package:get/get.dart';
import 'package:logger/logger.dart';

final Logger logger = Logger();

class HomeScreen extends StatefulWidget {
  const HomeScreen({super.key});

  @override
  State<HomeScreen> createState() => _HomeScreenState();
}

class _HomeScreenState extends State<HomeScreen> {
  final FlutterSecureStorage secureStorage = const FlutterSecureStorage();
  final SocketController socketController = Get.find<SocketController>();
  bool isShowingMapScreen = true; // 현재 화면 상태를 추적하는 변수
  String currentScreen = '맵'; // 현재 선택된 화면을 나타내는 상태 변수
  final deviceController = Get.put(DeviceController());
  // 드롭다운 메뉴의 선택 가능한 항목 목록
  final List<String> screenOptions = ['맵', '카메라'];
  // int _currentPageIndex = 0;
  // PageController 인스턴스
  final PageController _pageController = PageController(initialPage: 0);

  @override
  void initState() {
    super.initState();
  }

  @override
  Widget build(BuildContext context) {
    return SafeArea(
        child: Obx(
      () => Column(
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
                        if (deviceController.isOn.value) return;
                        final String? homeId =
                            await secureStorage.read(key: "homeId");
                        if (homeId != null) {
                          // 메시지 전송 로직
                          socketController.sendMessage(
                            destination: '/pub/control.message.$homeId',
                            type: 'MODE',
                            messageContent: 'patrol',
                          );
                          GlobalAlertDialog.show(
                            context,
                            title: "알림",
                            message: "기기 동작을 시작합니다.",
                          );
                          // UI 상태 업데이트
                          deviceController.toggleDevice();
                        } else {
                          logger.e("Home ID not found");
                        }
                      },
                      child: Container(
                        padding: const EdgeInsets.symmetric(
                            vertical: 8.0, horizontal: 16.0),
                        decoration: BoxDecoration(
                          color: deviceController.isOn.value
                              ? deepYellow
                              : Colors.grey[100],
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
                        if (!deviceController.isOn.value) return;
                        final String? homeId =
                            await secureStorage.read(key: "homeId");
                        if (homeId != null) {
                          // 메시지 전송 로직
                          socketController.sendMessage(
                            destination: '/pub/control.message.$homeId',
                            type: 'MODE',
                            messageContent: 'stay',
                          );
                          GlobalAlertDialog.show(
                            context,
                            title: "알림",
                            message: "기기 동작을 종료합니다.",
                          );
                          // UI 상태 업데이트
                          deviceController.toggleDevice();
                        } else {
                          logger.e("Home ID not found");
                        }
                      },
                      child: Container(
                        padding: const EdgeInsets.symmetric(
                            vertical: 8.0, horizontal: 16.0),
                        decoration: BoxDecoration(
                          color: !deviceController.isOn.value
                              ? deepYellow
                              : Colors.grey[100],
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
                if (deviceController.isOn.value) ...[
                  SizedBox(
                    height: 36,
                    width: 110,
                    child: TextButton(
                      onPressed: () async {
                        final String? homeId =
                            await secureStorage.read(key: "homeId");
                        final String message =
                            deviceController.isPatrollingMode.value
                                ? "patrol"
                                : "tracking";
                        String messageInDialog =
                            message == "patrol" ? "순찰" : "트래킹";
                        if (homeId != null) {
                          // 메시지 전송 로직
                          socketController.sendMessage(
                            destination: '/pub/control.message.$homeId',
                            type: 'MODE',
                            messageContent: message,
                          );
                          GlobalAlertDialog.show(
                            context,
                            title: "알림",
                            message: "$messageInDialog모드로 전환합니다.",
                          );
                          // UI 상태 업데이트
                          deviceController.toggleMode();
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
                        deviceController.isPatrollingMode.value
                            ? '순찰 모드'
                            : '트래킹 모드',
                        style: const TextStyle(
                          color: black,
                          fontSize: 15.0,
                          fontWeight: FontWeight.w700,
                        ),
                      ),
                    ),
                  ),
                ],
              ],
            ),
          ),
          Expanded(
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
              child: !deviceController.isOn.value
                  ? _buildOffMessage()
                  : Column(
                      children: [
                        Expanded(
                          child: PageView(
                            controller: _pageController,
                            children: const [
                              MapScreen(),
                              CameraScreen(),
                            ],
                          ),
                        ),
                      ],
                    ),
            ),
          ),
        ],
      ),
    ));
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

  @override
  void dispose() {
    _pageController.dispose();
    super.dispose();
  }
}
