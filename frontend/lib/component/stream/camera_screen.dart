import 'package:flutter/material.dart';

class CameraScreen extends StatelessWidget {
  const CameraScreen({super.key});

  @override
  Widget build(BuildContext context) {
    // 이미지의 경로는 예시이며, 실제 앱의 에셋 경로에 맞게 조정해야 합니다.
    String imagePath = 'asset/img/camera.jpg';

    return Padding(
      padding: const EdgeInsets.only(top: 20, right: 20, left: 20),
      child: Container(
        width: 320, // 이미지의 너비 설정
        height: 240, // 이미지의 높이 설정
        decoration: BoxDecoration(
          // 이미지를 BoxDecoration의 decorationImage로 설정
          image: DecorationImage(
            image: AssetImage(imagePath),
            fit: BoxFit.cover, // 이미지가 컨테이너 영역을 꽉 채우도록 설정
          ),
          boxShadow: [
            BoxShadow(
              color: Colors.grey.withOpacity(0.5),
              spreadRadius: 3,
              blurRadius: 4,
              offset: const Offset(0, 3),
            ),
          ],
          borderRadius: const BorderRadius.all(Radius.circular(20)), // 둥근 모서리
        ),
      ),
    );
  }
}
