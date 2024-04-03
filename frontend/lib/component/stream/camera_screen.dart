import 'dart:typed_data';
import 'package:flutter/material.dart';
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
      body: Center(
        child: Obx(() {
          Uint8List? currentImage = cameraController.currentImage.value;
          Uint8List? prevImage = cameraController.prevImage.value;
          return Stack(
            children: [
              if (prevImage != null)
                Positioned.fill(
                  child: Image.memory(prevImage),
                ),
              if (currentImage != null)
                Positioned.fill(
                  child: Image.memory(currentImage),
                ),
              if (prevImage == null && currentImage == null)
                const Positioned.fill(
                  child: Text("Data Loading . . ."),
                ),
            ],
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
