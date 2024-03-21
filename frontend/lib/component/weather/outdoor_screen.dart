import 'package:flutter/material.dart';
import 'package:frontend/component/service/fetch_weather.dart';
// import 'package:frontend/component/weather_screen.dart';
// import 'package:frontend/component/weather_text.dart';
import 'package:frontend/const/colors.dart';

class OutdoorScreen extends StatefulWidget {
  const OutdoorScreen({super.key});

  @override
  State<OutdoorScreen> createState() => _OutdoorScreenState();
}

class _OutdoorScreenState extends State<OutdoorScreen> {
  int? outTemp;
  int? outHum;
  String? weather;

  @override
  void initState() {
    super.initState();
    weather = 'Sunny';
    // 비동기 작업을 initState 내에서 스케줄링
    WidgetsBinding.instance.addPostFrameCallback((_) {
      fetchWeather('Seoul').then((data) {
        if (mounted) {
          setState(() {
            // API에서 받은 데이터로 상태 업데이트
            outTemp = ((data['main']['temp'] as double) - 273.15).round();
            outHum = data['main']['humidity'] as int;
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
                blurRadius: 2, // 그림자의 흐림 정도 설정
                offset: const Offset(0, 1), // 그림자의 위치 조정 (x, y)
              ),
            ],
            borderRadius: BorderRadius.circular(16),
            color: lightYellow,
          ),
          child: Row(
            mainAxisAlignment: MainAxisAlignment.spaceEvenly,
            crossAxisAlignment: CrossAxisAlignment.end,
            children: [
              weather == 'Cloudy'
                  ? Image.asset(
                      'asset/img/cloudy.png',
                      width: MediaQuery.of(context).size.width / 18 * 2,
                      height: MediaQuery.of(context).size.height / 10 * 2,
                    )
                  : weather == "Snowy"
                      ? Image.asset(
                          'asset/img/snowy.png',
                          width: MediaQuery.of(context).size.width / 18 * 2,
                          height: MediaQuery.of(context).size.height / 10 * 2,
                        )
                      : weather == "Foggy"
                          ? Image.asset(
                              'asset/img/foggy.png',
                              width: MediaQuery.of(context).size.width / 18 * 2,
                              height:
                                  MediaQuery.of(context).size.height / 10 * 2,
                            )
                          : weather == "Stormy"
                              ? Image.asset(
                                  'asset/img/stormy.png',
                                  width: MediaQuery.of(context).size.width /
                                      18 *
                                      2,
                                  height: MediaQuery.of(context).size.height /
                                      10 *
                                      2,
                                )
                              : weather == "Sunny"
                                  ? Image.asset(
                                      'asset/img/sunny.png',
                                      width: MediaQuery.of(context).size.width /
                                          18 *
                                          2,
                                      height:
                                          MediaQuery.of(context).size.height /
                                              10 *
                                              2,
                                    )
                                  : Image.asset(
                                      'asset/img/rainy.png',
                                      width: MediaQuery.of(context).size.width /
                                          18 *
                                          2,
                                      height:
                                          MediaQuery.of(context).size.height /
                                              10 *
                                              2,
                                    ),
              Column(
                mainAxisAlignment: MainAxisAlignment.center,
                crossAxisAlignment: CrossAxisAlignment.center,
                children: [
                  const Text(
                    '외부 온도',
                    style: TextStyle(
                      color: Colors.black,
                      fontWeight: FontWeight.w700,
                    ),
                  ),
                  Text(
                    outTemp?.toString() ?? 'Loading...',
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
                    '외부 습도',
                    style: TextStyle(
                      color: Colors.black,
                      fontWeight: FontWeight.w700,
                    ),
                  ),
                  Text(
                    outHum?.toString() ?? 'Loading...',
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
