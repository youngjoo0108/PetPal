import 'package:flutter/material.dart';
import 'package:frontend/const/colors.dart';
import 'package:frontend/controller/weather_controller.dart';
import 'package:get/get.dart';
import 'package:logger/logger.dart';

final Logger logger = Logger();

class IndoorScreen extends StatefulWidget {
  const IndoorScreen({super.key});

  @override
  State<IndoorScreen> createState() => _IndoorScreenState();
}

class _IndoorScreenState extends State<IndoorScreen> {
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
                  blurRadius: 3,
                  offset: const Offset(0, 2),
                ),
              ],
              borderRadius: BorderRadius.circular(16),
              color: lightYellow,
            ),
            child: Row(
              mainAxisAlignment: MainAxisAlignment.spaceEvenly,
              crossAxisAlignment: CrossAxisAlignment.end,
              children: [
                _buildTemperatureWidget(
                    '체감 온도', weatherController.feelLike.value),
                _buildTemperatureWidget(
                    '실내 온도', weatherController.inTemp.value),
              ],
            ),
          )),
    );
  }

  Widget _buildTemperatureWidget(String title, int value) {
    return Column(
      mainAxisAlignment: MainAxisAlignment.center,
      crossAxisAlignment: CrossAxisAlignment.center,
      children: [
        Text(
          title,
          style: const TextStyle(
            color: Colors.black,
            fontWeight: FontWeight.w700,
          ),
        ),
        Text(
          value != -100 ? '$value°C' : 'Loading...',
          style: const TextStyle(
            color: Colors.black,
            fontWeight: FontWeight.w700,
          ),
        ),
      ],
    );
  }
}
