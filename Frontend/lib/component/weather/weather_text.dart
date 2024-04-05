import 'package:flutter/material.dart';

class WeatherText extends StatelessWidget {
  final int? temp;
  final String? content;
  const WeatherText.content({super.key, required String? content})
      : content = content,
        temp = null;
  const WeatherText.temp({super.key, required int? temp})
      : content = null,
        temp = temp;

  @override
  Widget build(BuildContext context) {
    return Column(
      mainAxisAlignment: MainAxisAlignment.center,
      crossAxisAlignment: CrossAxisAlignment.center,
      children: [
        Text(temp != null ? '$temp도' : '$content',
            style: const TextStyle(
                color: Colors.white, fontWeight: FontWeight.w700)),
      ],
    );
  }
}
