import 'package:flutter/material.dart';
import 'package:frontend/component/control/auto_control_screen.dart';
import 'package:frontend/component/control/manual_screen.dart';
import 'package:frontend/component/weather/weather_screen.dart';
import 'package:frontend/const/colors.dart';

class ControlScreen extends StatefulWidget {
  const ControlScreen({super.key});

  @override
  State<ControlScreen> createState() => _ControlScreenState();
}

class _ControlScreenState extends State<ControlScreen> {
  bool isAuto = true;

  @override
  Widget build(BuildContext context) {
    return SafeArea(
      child: Column(
        children: [
          const WeatherScreen(),
          Padding(
            padding: const EdgeInsets.only(left: 15.0),
            child: Row(
              children: <Widget>[
                // "자동" 버튼
                GestureDetector(
                  onTap: () {
                    // setState(() {
                    //   isAuto = true;
                    // });
                  },
                  child: Container(
                    padding: const EdgeInsets.symmetric(
                        vertical: 8.0, horizontal: 16.0),
                    decoration: BoxDecoration(
                      color: isAuto ? deepYellow : Colors.grey[100],
                      borderRadius: const BorderRadius.only(
                        topLeft: Radius.circular(10.0),
                        bottomLeft: Radius.circular(10.0),
                      ),
                    ),
                    child: const Text(
                      '자동',
                      style: TextStyle(
                        color: black,
                        fontSize: 14.0,
                        fontWeight: FontWeight.w600,
                      ),
                    ),
                  ),
                ),
                // "수동" 버튼
                GestureDetector(
                  onTap: () {
                    // setState(() {
                    //   isAuto = false;
                    // });
                  },
                  child: Container(
                    padding: const EdgeInsets.symmetric(
                        vertical: 8.0, horizontal: 16.0),
                    decoration: BoxDecoration(
                      color: !isAuto ? deepYellow : Colors.grey[100],
                      borderRadius: const BorderRadius.only(
                        topRight: Radius.circular(10.0),
                        bottomRight: Radius.circular(10.0),
                      ),
                    ),
                    child: const Text(
                      '수동',
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
              child: Row(
                mainAxisAlignment: MainAxisAlignment.start,
                crossAxisAlignment: CrossAxisAlignment.stretch,
                children: [
                  Expanded(
                    child: isAuto
                        ? const AutoControlScreen()
                        : const ManualControlScreen(),
                  ),
                ],
              ),
            ),
          ),
        ],
      ),
    );
  }
}
