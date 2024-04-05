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
  Rx<String> weather = Rx<String>("Cloudy");
  Rx<int> outHum = Rx<int>(-100);
  Rx<int> inTemp = Rx<int>(18);
  Rx<int> outTemp = Rx<int>(-100);
  Rx<int> feelLike = Rx<int>(-100);

  @override
  void onInit() {
    logger.d("WeatherControllerInit");
    super.onInit();
  }

  Future<void> _waitForSocketInitialization() async {
    // SocketController의 StompClient 초기화를 기다
    _socketController.isInitialized.value = false;
    while (!_socketController.isInitialized.value) {
      await Future.delayed(const Duration(milliseconds: 100));
    }
  }

  void initWebSocket() async {
    await Future.wait<void>([_waitForSocketInitialization()]);
    logger.e("InitWeatherFetching");
    final String? homeId = await _secureStorage.read(key: "homeId");

    if (homeId != null) {
      unsubscribeFn = _socketController.stompClient.subscribe(
        destination: '/exchange/control.exchange/home.$homeId',
        callback: (frame) {
          if (frame.body != null) {
            final data = json.decode(frame.body!);
            if (data['type'] == "WEATHER") {
              inTemp.value = (data['message']['temp'] as num).toInt();
              weather.value = data['message']['weather'];
              logger.e("${inTemp.value}, ${weather.value}");
              inTemp.refresh();
              weather.refresh();
            }
          }
        },
      );
    }
  }

  void fetchWeather() async {
    await fetchWeatherByCity('Seoul').then((data) {
      // JSON에서 값 추출
      var feelsLikeRaw = data['main']['feels_like'];
      // double로 변환
      var feelsLike =
          feelsLikeRaw is int ? feelsLikeRaw.toDouble() : feelsLikeRaw;
      // Kelvin에서 Celsius로 변환 후 값 설정
      feelLike.value = (feelsLike - 273.15).round();

      var tempRaw = data['main']['temp'];
      var temp = tempRaw is int ? tempRaw.toDouble() : tempRaw;
      outTemp.value = (temp - 273.15).round();

      outHum.value = data['main']['humidity'] as int;

      // 상태 업데이트
      feelLike.refresh();
      outTemp.refresh();
      outHum.refresh();
    });
  }
}
