import 'package:flutter/material.dart';
import 'package:flutter_secure_storage/flutter_secure_storage.dart';
import 'package:frontend/component/weather/indoor_screen.dart';
import 'package:frontend/component/weather/outdoor_screen.dart';
import 'package:frontend/controller/weather_controller.dart';
import 'package:frontend/socket/socket.dart';
import 'package:get/get.dart';
import 'package:logger/logger.dart';

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
  late final WeatherController weatherController;
  final SocketController socketController = Get.find<SocketController>();
  final FlutterSecureStorage secureStorage = const FlutterSecureStorage();

  @override
  void initState() {
    super.initState();
    weatherController = Get.put(WeatherController());
    weatherController.initWebSocket();
    weatherController.fetchWeather();
  }

  @override
  Widget build(BuildContext context) {
    return const Column(
      mainAxisAlignment: MainAxisAlignment.center,
      crossAxisAlignment: CrossAxisAlignment.stretch,
      children: [OutdoorScreen(), IndoorScreen()],
    );
  }

  @override
  void dispose() {
    // if (weatherController.unsubscribeFn != null) {
    //   weatherController.unsubscribeFn();
    // }
    super.dispose();
  }
}
