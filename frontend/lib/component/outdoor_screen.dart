import 'package:flutter/material.dart';
// import 'package:frontend/component/weather_screen.dart';
// import 'package:frontend/component/weather_text.dart';
import 'package:frontend/const/colors.dart';

class OutdoorScreen extends StatefulWidget {
  final int outTemp;
  final int outHum;
  final String weather;

  const OutdoorScreen(
      {required this.outTemp,
      required this.outHum,
      required this.weather,
      super.key});

  @override
  State<OutdoorScreen> createState() => _OutdoorScreenState();
}

class _OutdoorScreenState extends State<OutdoorScreen> {
  @override
  Widget build(BuildContext context) {
    return Padding(
      padding: const EdgeInsets.symmetric(horizontal: 16.0, vertical: 8.0),
      child: Container(
          height: MediaQuery.of(context).size.height / 10,
          decoration: BoxDecoration(
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
              const Column(
                mainAxisAlignment: MainAxisAlignment.center,
                crossAxisAlignment: CrossAxisAlignment.center,
                children: [
                  Text(
                    '외부 온도',
                    style: TextStyle(
                      color: Colors.black,
                      fontWeight: FontWeight.w700,
                    ),
                  ),
                  Text(
                    '18',
                    style: TextStyle(
                      color: Colors.black,
                      fontWeight: FontWeight.w700,
                    ),
                  ),
                ],
              ),
              const Column(
                mainAxisAlignment: MainAxisAlignment.center,
                crossAxisAlignment: CrossAxisAlignment.center,
                children: [
                  Text(
                    '외부 습도',
                    style: TextStyle(
                      color: Colors.black,
                      fontWeight: FontWeight.w700,
                    ),
                  ),
                  Text(
                    '60',
                    style: TextStyle(
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
