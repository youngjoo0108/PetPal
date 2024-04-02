import 'package:flutter/material.dart';
// import 'package:frontend/component/weather_screen.dart';
// import 'package:frontend/component/weather_text.dart';
import 'package:frontend/const/colors.dart';
import 'package:logger/logger.dart';

final Logger logger = Logger();

class OutdoorScreen extends StatefulWidget {
  final int? outTemp;
  final int? outHum;
  final String? weather;
  const OutdoorScreen(
      {super.key,
      required this.outTemp,
      required this.outHum,
      required this.weather});

  @override
  State<OutdoorScreen> createState() => _OutdoorScreenState();
}

class _OutdoorScreenState extends State<OutdoorScreen> {
  @override
  void initState() {
    super.initState();
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
              widget.weather == 'Cloudy'
                  ? Image.asset(
                      'asset/img/cloudy.png',
                      width: MediaQuery.of(context).size.width / 18 * 2,
                      height: MediaQuery.of(context).size.height / 10 * 2,
                    )
                  : widget.weather == "Snowy"
                      ? Image.asset(
                          'asset/img/snowy.png',
                          width: MediaQuery.of(context).size.width / 18 * 2,
                          height: MediaQuery.of(context).size.height / 10 * 2,
                        )
                      : widget.weather == "Foggy"
                          ? Image.asset(
                              'asset/img/foggy.png',
                              width: MediaQuery.of(context).size.width / 18 * 2,
                              height:
                                  MediaQuery.of(context).size.height / 10 * 2,
                            )
                          : widget.weather == "Stormy"
                              ? Image.asset(
                                  'asset/img/stormy.png',
                                  width: MediaQuery.of(context).size.width /
                                      18 *
                                      2,
                                  height: MediaQuery.of(context).size.height /
                                      10 *
                                      2,
                                )
                              : widget.weather == "Sunny"
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
                                  : widget.weather == "Rainy"
                                      ? Image.asset(
                                          'asset/img/rainy.png',
                                          width: MediaQuery.of(context)
                                                  .size
                                                  .width /
                                              18 *
                                              2,
                                          height: MediaQuery.of(context)
                                                  .size
                                                  .height /
                                              10 *
                                              2,
                                        )
                                      : Image.asset(
                                          'asset/img/loading.png',
                                          width: MediaQuery.of(context)
                                                  .size
                                                  .width /
                                              18 *
                                              2,
                                          height: MediaQuery.of(context)
                                                  .size
                                                  .height /
                                              10 *
                                              2,
                                        ),
              Column(
                mainAxisAlignment: MainAxisAlignment.center,
                crossAxisAlignment: CrossAxisAlignment.center,
                children: [
                  const Text(
                    '실외 온도',
                    style: TextStyle(
                      color: Colors.black,
                      fontWeight: FontWeight.w700,
                    ),
                  ),
                  Text(
                    widget.outTemp != null
                        ? '${widget.outTemp}°C'
                        : 'Loading...',
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
                    '실외 습도',
                    style: TextStyle(
                      color: Colors.black,
                      fontWeight: FontWeight.w700,
                    ),
                  ),
                  Text(
                    widget.outHum != null
                        ? widget.outHum.toString()
                        : 'Loading...',
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
