import 'package:flutter/material.dart';
import 'package:frontend/component/stream/camera_screen.dart';
import 'package:frontend/component/stream/map_screen.dart';
import 'package:frontend/component/weather/weather_screen.dart';

class HomeScreen extends StatefulWidget {
  const HomeScreen({super.key});

  @override
  State<HomeScreen> createState() => _HomeScreenState();
}

class _HomeScreenState extends State<HomeScreen> {
  @override
  void initState() {
    super.initState();
  }

  @override
  Widget build(BuildContext context) {
    return SafeArea(
      child: Column(
        children: [
          const WeatherScreen(),
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
              child: const Column(
                mainAxisAlignment: MainAxisAlignment.start,
                crossAxisAlignment: CrossAxisAlignment.stretch,
                children: [
                  CameraScreen(),
                  MapScreen(),
                ],
              ),
            ),
          ),
          // WeatherScreen(
          //     out_temp: widget.out_temp,
          //     in_temp: widget.in_temp,
          //     in_hum: widget.in_hum,
          //     out_hum: widget.out_hum,
          //     environment: widget.environment),
          // Expanded(
          //     child: MainAppliance(
          //       air:widget.air,
          //   aplicancestatus: widget.aplicancestatus,
          // ))
        ],
      ),
    );
  }
}
