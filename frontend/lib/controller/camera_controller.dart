import 'package:get/get.dart';
// import 'dart:convert';
import 'dart:typed_data';

class CameraController extends GetxController {
  var currentImage = Rxn<Uint8List>(); // 현재 이미지를 관리하는 반응형 변수

  void updateImage(Uint8List newImage) {
    currentImage.value = newImage; // 새 이미지로 업데이트
  }
}
