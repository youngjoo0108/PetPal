import 'dart:async';
import 'dart:collection';
import 'dart:convert';
import 'dart:typed_data';
import 'package:flutter_secure_storage/flutter_secure_storage.dart';
import 'package:get/get.dart';
import 'package:logger/logger.dart';
import 'package:frontend/socket/socket.dart';

final Logger logger = Logger();

class CameraController extends GetxController {
  // Rx<Uint8List?> 타입으로 변경하여 관찰 가능한 상태로 만듭니다.
  final Rx<Uint8List?> prevImage = Rx<Uint8List?>(null);
  final Rx<Uint8List?> currentImage = Rx<Uint8List?>(null);

  final Queue<Uint8List> imageQueue = Queue<Uint8List>();
  late Timer renderTimer;
  final int _frameDelay = 30; // 15fps에 해당하는 프레임 지연 시간
  final SocketController _socketController = Get.find<SocketController>();
  final FlutterSecureStorage _secureStorage = const FlutterSecureStorage();
  dynamic unsubscribeFn;

  @override
  void onInit() {
    logger.d("CameraControllerInit");
    super.onInit();
  }

  void initWebSocket() async {
    final String? homeId = await _secureStorage.read(key: "homeId");

    if (homeId != null) {
      unsubscribeFn = _socketController.stompClient.subscribe(
        destination: '/exchange/control.exchange/home.$homeId.images',
        callback: (frame) {
          if (frame.body != null) {
            // logger.e("이미지 데이터 수신");
            final data = json.decode(frame.body!);
            if (data['type'] == "video_streaming") {
              final String? imageBase64 = data['message'];
              if (imageBase64 != null) {
                imageQueue.add(base64Decode(imageBase64));
              }
            }
          }
        },
      );
    }
  }

  void startRendering() {
    renderTimer = Timer.periodic(Duration(milliseconds: _frameDelay), (timer) {
      if (imageQueue.isNotEmpty) {
        prevImage.value = currentImage.value;
        currentImage.value = imageQueue.removeFirst();
        // 상태 업데이트를 강제로 트리거합니다.
        prevImage.refresh();
        currentImage.refresh();
      }
    });
  }
}
