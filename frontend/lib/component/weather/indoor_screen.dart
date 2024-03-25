import 'package:flutter/material.dart';
import 'package:frontend/service/fetch_weather.dart';
import 'package:frontend/const/colors.dart';

class IndoorScreen extends StatefulWidget {
  const IndoorScreen({super.key});

  @override
  State<IndoorScreen> createState() => _IndoorScreenState();
}

class _IndoorScreenState extends State<IndoorScreen> {
  int? inTemp;
  int? feelLike;

  @override
  void initState() {
    super.initState();
    // 비동기 작업을 initState 내에서 스케줄링
    WidgetsBinding.instance.addPostFrameCallback((_) {
      fetchWeather('Seoul').then((data) {
        if (mounted) {
          setState(() {
            // API에서 받은 데이터로 상태 업데이트
            feelLike =
                ((data['main']['feels_like'] as double) - 273.15).round();
            inTemp = 15;
          });
        }
      }).catchError((error) {
        // 오류 처리
        print("Error fetching weather data: $error");
      });
    });
  }

  @override
  Widget build(BuildContext context) {
    return Padding(
      padding: const EdgeInsets.symmetric(horizontal: 16.0, vertical: 8.0),
      child: Container(
          height: MediaQuery.of(context).size.height / 10,
          decoration: BoxDecoration(
            boxShadow: [
              BoxShadow(
                color: Colors.grey.withOpacity(0.5), // 그림자 색상 설정
                spreadRadius: 0, // 그림자가 퍼지는 범위 설정
                blurRadius: 3, // 그림자의 흐림 정도 설정
                offset: const Offset(0, 2), // 그림자의 위치 조정 (x, y)
              ),
            ],
            borderRadius: BorderRadius.circular(16),
            color: lightYellow,
          ),
          child: Row(
            mainAxisAlignment: MainAxisAlignment.spaceEvenly,
            crossAxisAlignment: CrossAxisAlignment.end,
            children: [
              Column(
                mainAxisAlignment: MainAxisAlignment.center,
                crossAxisAlignment: CrossAxisAlignment.center,
                children: [
                  const Text(
                    '체감 온도',
                    style: TextStyle(
                      color: Colors.black,
                      fontWeight: FontWeight.w700,
                    ),
                  ),
                  Text(
                    feelLike?.toString() ?? 'Loading...',
                    style: const TextStyle(
                      color: Colors.black,
                      fontWeight: FontWeight.w700,
                    ),
                  ),
                ],
              ),
              Column(
                mainAxisAlignment: MainAxisAlignment.center,
                crossAxisAlignment: CrossAxisAlignment.center,
                children: [
                  const Text(
                    '실내 온도',
                    style: TextStyle(
                      color: Colors.black,
                      fontWeight: FontWeight.w700,
                    ),
                  ),
                  Text(
                    inTemp?.toString() ?? 'Loading...',
                    style: const TextStyle(
                      color: Colors.black,
                      fontWeight: FontWeight.w700,
                    ),
                  ),
                ],
              ),
            ],
          )),
    );
  }
}
