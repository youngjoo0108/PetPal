import 'dart:convert';

import 'package:flutter/material.dart';
import 'package:flutter_secure_storage/flutter_secure_storage.dart';
import 'package:frontend/component/weather/indoor_screen.dart';
import 'package:frontend/component/weather/outdoor_screen.dart';
import 'package:frontend/service/fetch_weather.dart';
import 'package:frontend/socket/socket.dart';
import 'package:get/get.dart';
import 'package:logger/logger.dart';
import 'package:stomp_dart_client/stomp_frame.dart';

final Logger logger = Logger();

class WeatherScreen extends StatefulWidget {
  const WeatherScreen({super.key});

  @override
  State<WeatherScreen> createState() => _WeatherScreenState();
}

class _WeatherScreenState extends State<WeatherScreen> {
  int? outTemp;
  int? inTemp;
  int? outHum;
  int? feelLike;
  String? weather;
  final SocketController socketController = Get.find<SocketController>();
  final FlutterSecureStorage secureStorage = const FlutterSecureStorage();

  @override
  void initState() {
    super.initState();
    initWebSocket();
    WidgetsBinding.instance.addPostFrameCallback((_) {
      fetchWeather('Seoul').then((data) {
        if (mounted) {
          setState(() {
            // API에서 받은 데이터로 상태 업데이트
            feelLike =
                ((data['main']['feels_like'] as double) - 273.15).round();
            inTemp = 15;
            outTemp = ((data['main']['temp'] as double) - 273.15).round();
            outHum = data['main']['humidity'] as int;
          });
        }
      }).catchError((error) {
        // 오류 처리
        logger.e("Error fetching weather data: $error");
      });
    });
  }

  void initWebSocket() async {
    final String? homeId = await secureStorage.read(key: "homeId");
    socketController.initializeWebSocketConnection(
      destination: '/exchange/control.exchange/home.$homeId',
      onMessageReceived: _onMessageReceived,
    );
  }

  void _onMessageReceived(StompFrame frame) {
    if (frame.body != null) {
      final data = json.decode(frame.body!);
      if (data['type'] == "weather") {
        /*
        날씨 data + 실내 온도 data 받아서 처리
         */
      }
    }
  }

  @override
  Widget build(BuildContext context) {
    return Column(
      mainAxisAlignment: MainAxisAlignment.center,
      crossAxisAlignment: CrossAxisAlignment.stretch,
      children: [
        OutdoorScreen(
          outTemp: outTemp,
          outHum: outHum,
          weather: 'Sunny',
        ),
        IndoorScreen(
          inTemp: 15,
          feelLike: feelLike,
        )
      ],
    );
  }
}
