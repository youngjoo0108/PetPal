import 'package:flutter/material.dart';
import 'package:frontend/component/weather/indoor_screen.dart';
import 'package:frontend/component/weather/outdoor_screen.dart';

class WeatherScreen extends StatefulWidget {
  const WeatherScreen({super.key});

  @override
  State<WeatherScreen> createState() => _WeatherScreenState();
}

class _WeatherScreenState extends State<WeatherScreen> {
  int outTemp = 18;
  int inTemp = 20;
  int outHum = 50;
  int inHum = 60;
  String weather = "sunny";

  @override
  Widget build(BuildContext context) {
    return Container(
      child: Column(
        mainAxisAlignment: MainAxisAlignment.center,
        crossAxisAlignment: CrossAxisAlignment.stretch,
        children: [
          OutdoorScreen(),
          IndoorScreen(
            inTemp: inTemp,
            inHum: inHum,
          )
        ],
      ),
    );
  }
}
