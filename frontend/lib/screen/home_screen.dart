import 'package:flutter/material.dart';
import 'package:frontend/component/camera_screen.dart';
import 'package:frontend/component/map_screen.dart';
import 'package:frontend/component/weather_screen.dart';

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
    return const SafeArea(
      child: Column(
        children: [
          WeatherScreen(),
          Expanded(
            child: Column(
              children: [
                CameraScreen(),
                MapScreen(),
              ],
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
