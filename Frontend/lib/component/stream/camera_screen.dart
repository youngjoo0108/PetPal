import 'dart:typed_data';
import 'package:flutter/material.dart';
import 'package:frontend/const/colors.dart';
import 'package:get/get.dart';
import 'package:frontend/controller/camera_controller.dart'; // 경로 확인 필요

class CameraScreen extends StatefulWidget {
  const CameraScreen({super.key});

  @override
  CameraScreenState createState() => CameraScreenState();
}

class CameraScreenState extends State<CameraScreen> {
  late final CameraController cameraController;

  @override
  void initState() {
    super.initState();
    // CameraController 인스턴스를 찾거나, 없으면 생성
    cameraController = Get.put(CameraController());
    cameraController.initWebSocket();
    cameraController.startRendering();
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      backgroundColor: white,
      body: Center(
        child: Obx(() {
          Uint8List? currentImage = cameraController.currentImage.value;
          Uint8List? prevImage = cameraController.prevImage.value;
          return Padding(
            padding: const EdgeInsets.all(20.0),
            child: Stack(
              children: [
                if (prevImage != null)
                  Positioned.fill(
                    child: ClipRRect(
                      borderRadius: BorderRadius.circular(20), // 모서리 둥글게
                      child: Image.memory(
                        prevImage,
                        fit: BoxFit.fill, // 이미지를 화면에 꽉 채우도록 설정
                      ),
                    ),
                  ),
                if (currentImage != null)
                  Positioned.fill(
                    child: ClipRRect(
                      borderRadius: BorderRadius.circular(20), // 모서리 둥글게
                      child: Image.memory(
                        currentImage,
                        fit: BoxFit.fill, // 이미지를 화면에 꽉 채우도록 설정
                      ),
                    ),
                  ),
                if (prevImage != null && currentImage != null)
                  Positioned(
                    left: -30,
                    top: -50,
                    child: Image.asset('asset/img/live.png',
                        width: 150, height: 150), // 이미지 크기 조절
                  ),
                if (prevImage == null && currentImage == null)
                  const Center(
                    child: CircularProgressIndicator(),
                  ),
              ],
            ),
          );
        }),
      ),
    );
  }

  @override
  void dispose() {
    // CameraController의 구독 해지 로직을 호출
    logger.d("CameraScreenDispose");
    cameraController.unsubscribeFn(); // 구독 해지 함수 호출
    cameraController.imageQueue.clear();
    cameraController.renderTimer.cancel();
    super.dispose();
  }
}
