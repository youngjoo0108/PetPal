import 'package:flutter/material.dart';
import 'package:frontend/component/indoor_screen.dart';
import 'package:frontend/component/outdoor_screen.dart';

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
          OutdoorScreen(
            outTemp: outHum,
            outHum: outTemp,
            weather: weather,
          ),
          IndoorScreen(
            inTemp: inTemp,
            inHum: inHum,
          )
        ],
      ),
    );
  }
}
