// import 'package:frontend/screen/login_screen.dart';
import 'package:frontend/service/user_service.dart';
// import 'package:flutter/material.dart';

class MenuTabController {
  final Function? onLogout;
  final Function? onManageRoom; // '방 관리'에 대한 콜백 함수
  final Function? onManageAppliance; // '가전 관리'에 대한 콜백 함수
  final Function? onHomeScan;
  final Function? onHelp;

  MenuTabController({
    this.onLogout,
    this.onManageRoom,
    this.onManageAppliance,
    this.onHomeScan,
    this.onHelp,
  });

  UserService userService = UserService();

  void tabItem(String item) {
    switch (item) {
      case "기기 등록":
        break;
      case "홈 스캔":
        onHomeScan?.call();
        break;
      case "방 관리":
        onManageRoom?.call(); // '방 관리' 콜백 함수 호출
        break;
      case "가전 관리":
        onManageAppliance?.call(); // '가전 관리' 콜백 함수 호출
        break;
      case "도움말":
        onHelp?.call();
        break;
      case "로그아웃":
        userService.logout().then((_) => onLogout?.call());
        break;
      default:
        break;
    }
  }
}
