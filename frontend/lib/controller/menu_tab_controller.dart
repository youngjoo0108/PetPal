// import 'package:frontend/screen/login_screen.dart';
import 'package:frontend/service/user_service.dart';
// import 'package:flutter/material.dart';

class MenuTabController {
  final Function? onLogout;
  final Function? onAddRoom; // '방 추가'에 대한 콜백 함수

  MenuTabController({this.onLogout, this.onAddRoom});

  UserService userService = UserService();

  void tabItem(String item) {
    switch (item) {
      case "기기 등록":
        break;
      case "홈 스캔":
        break;
      case "방 추가":
        onAddRoom?.call(); // '방 추가' 콜백 함수 호출
        break;
      case "가전 추가":
        break;
      case "사물 등록":
        break;
      case "사물 제어":
        break;
      case "로그아웃":
        userService.logout().then((_) => onLogout?.call());
        break;
      default:
        break;
    }
  }
}
