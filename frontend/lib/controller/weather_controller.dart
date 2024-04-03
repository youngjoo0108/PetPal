import 'dart:convert';
import 'package:flutter_secure_storage/flutter_secure_storage.dart';
import 'package:frontend/service/fetch_weather.dart';
import 'package:frontend/socket/socket.dart';
import 'package:get/get.dart';
import 'package:logger/logger.dart';

final Logger logger = Logger();

class WeatherController extends GetxController {
  final FlutterSecureStorage _secureStorage = const FlutterSecureStorage();
  final SocketController _socketController = Get.find<SocketController>();
  dynamic unsubscribeFn;
  Rx<String> weather = Rx<String>("Sunny");
  Rx<int> outHum = Rx<int>(-100);
  Rx<int> inTemp = Rx<int>(-100);
  Rx<int> outTemp = Rx<int>(-100);
  Rx<int> feelLike = Rx<int>(-100);

  @override
  void onInit() {
    logger.d("WeatherControllerInit");
    super.onInit();
  }

  Future<void> _waitForSocketInitialization() async {
    // SocketController의 StompClient 초기화를 기다림
    while (!_socketController.isInitialized.value) {
      await Future.delayed(const Duration(milliseconds: 100));
    }
  }

  void initWebSocket() async {
    await Future.wait<void>([_waitForSocketInitialization()]);
    final String? homeId = await _secureStorage.read(key: "homeId");

    if (homeId != null) {
      unsubscribeFn = _socketController.stompClient.subscribe(
        destination: '/exchange/control.exchange/home.$homeId',
        callback: (frame) {
          if (frame.body != null) {
            logger.e("일단 오긴 오나?");
            final data = json.decode(frame.body!);
            if (data['type'] == "WEATHER") {}
          }
        },
      );
    }
  }

  void fetchWeather() async {
    await fetchWeatherByCity('Seoul').then((data) {
      feelLike.value =
          ((data['main']['feels_like'] as double) - 273.15).round();
      outTemp.value = ((data['main']['temp'] as double) - 273.15).round();
      outHum.value = data['main']['humidity'] as int;
      feelLike.refresh();
      outTemp.refresh();
      outHum.refresh();
    });
  }
}
