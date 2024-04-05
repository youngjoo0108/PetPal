import 'package:flutter/material.dart';
import 'package:frontend/const/colors.dart';
import 'package:frontend/controller/weather_controller.dart';
import 'package:get/get.dart';
import 'package:logger/logger.dart';

final Logger logger = Logger();

class OutdoorScreen extends StatefulWidget {
  const OutdoorScreen({super.key});

  @override
  State<OutdoorScreen> createState() => _OutdoorScreenState();
}

class _OutdoorScreenState extends State<OutdoorScreen> {
  late final WeatherController weatherController;

  @override
  void initState() {
    super.initState();
    weatherController = Get.put(WeatherController());
  }

  @override
  Widget build(BuildContext context) {
    return Padding(
      padding: const EdgeInsets.symmetric(horizontal: 16.0, vertical: 8.0),
      child: Obx(() => Container(
            height: MediaQuery.of(context).size.height / 10,
            decoration: BoxDecoration(
              boxShadow: [
                BoxShadow(
                  color: Colors.grey.withOpacity(0.5),
                  spreadRadius: 0,
                  blurRadius: 2,
                  offset: const Offset(0, 1),
                ),
              ],
              borderRadius: BorderRadius.circular(16),
              color: lightYellow,
            ),
            child: Row(
              mainAxisAlignment: MainAxisAlignment.spaceEvenly,
              crossAxisAlignment: CrossAxisAlignment.end,
              children: [
                _buildWeatherIcon(weatherController.weather.value),
                _buildOutdoorTemperature(weatherController.outTemp.value),
                _buildOutdoorHumidity(weatherController.outHum.value),
              ],
            ),
          )),
    );
  }

  Widget _buildWeatherIcon(String weatherType) {
    String imagePath;
    switch (weatherType) {
      case 'Cloudy':
        imagePath = 'asset/img/cloudy.png';
        break;
      case 'Snowy':
        imagePath = 'asset/img/snowy.png';
        break;
      case 'Foggy':
        imagePath = 'asset/img/foggy.png';
        break;
      case 'Stormy':
        imagePath = 'asset/img/stormy.png';
        break;
      case 'Sunny':
        imagePath = 'asset/img/sunny.png';
        break;
      case 'Rainy':
        imagePath = 'asset/img/rainy.png';
        break;
      default:
        imagePath = 'asset/img/loading.png';
    }
    return Image.asset(
      imagePath,
      width: MediaQuery.of(context).size.width / 18 * 2,
      height: MediaQuery.of(context).size.height / 10 * 2,
    );
  }

  Widget _buildOutdoorTemperature(int temperature) {
    return Column(
      mainAxisAlignment: MainAxisAlignment.center,
      crossAxisAlignment: CrossAxisAlignment.center,
      children: [
        const Text(
          '실외 온도',
          style: TextStyle(color: Colors.black, fontWeight: FontWeight.w700),
        ),
        Text(
          temperature != -100 ? '$temperature°C' : 'Loading...',
          style:
              const TextStyle(color: Colors.black, fontWeight: FontWeight.w700),
        ),
      ],
    );
  }

  Widget _buildOutdoorHumidity(int humidity) {
    return Column(
      mainAxisAlignment: MainAxisAlignment.center,
      crossAxisAlignment: CrossAxisAlignment.center,
      children: [
        const Text(
          '실외 습도',
          style: TextStyle(color: Colors.black, fontWeight: FontWeight.w700),
        ),
        Text(
          humidity != -100 ? '$humidity' : 'Loading...',
          style:
              const TextStyle(color: Colors.black, fontWeight: FontWeight.w700),
        ),
      ],
    );
  }
}
