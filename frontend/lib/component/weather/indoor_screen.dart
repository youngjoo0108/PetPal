import 'package:flutter/material.dart';
import 'package:frontend/const/colors.dart';
import 'package:logger/logger.dart';

final Logger logger = Logger();

class IndoorScreen extends StatefulWidget {
  final int? inTemp;
  final int? feelLike;
  const IndoorScreen({super.key, required this.inTemp, required this.feelLike});

  @override
  State<IndoorScreen> createState() => _IndoorScreenState();
}

class _IndoorScreenState extends State<IndoorScreen> {
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
                    widget.feelLike != null
                        ? '${widget.feelLike}°C'
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
                    '실내 온도',
                    style: TextStyle(
                      color: Colors.black,
                      fontWeight: FontWeight.w700,
                    ),
                  ),
                  Text(
                    widget.inTemp.toString(),
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
