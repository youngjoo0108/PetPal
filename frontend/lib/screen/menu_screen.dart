import 'package:flutter/material.dart';
import 'package:frontend/component/menu/room_management.dart';
import 'package:frontend/controller/menu_tab_controller.dart';
import 'package:frontend/const/colors.dart';
import 'login_screen.dart';

class MenuScreen extends StatefulWidget {
  const MenuScreen({super.key});

  @override
  State<MenuScreen> createState() => _MenuScreenState();
}

class _MenuScreenState extends State<MenuScreen> {
  MenuTabController menuTabController = MenuTabController();

  @override
  void initState() {
    super.initState();
    // 콜백 함수를 포함하여 MenuTabController 초기화
    menuTabController = MenuTabController(
      onAddRoom: () {
        Navigator.of(context).push(MaterialPageRoute(
          builder: (context) => const RoomManagement(), // '방 추가' 화면으로 전환
        ));
      },
      onLogout: () {
        Navigator.of(context).pushReplacement(MaterialPageRoute(
          builder: (context) => const LoginScreen(), // 로그아웃 후 로그인 화면으로 전환
        ));
      },
    );
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      body: Container(
        color: white, // 전체 배경색 설정
        padding: const EdgeInsets.only(top: 12), // 상단 padding 추가
        child: Container(
          padding: const EdgeInsets.all(15), // 전체적인 마진 설정
          decoration: BoxDecoration(
            color: Colors.white, // 배경색 설정
            boxShadow: [
              BoxShadow(
                color: Colors.grey.withOpacity(0.5),
                spreadRadius: 3,
                blurRadius: 4,
                offset: const Offset(0, 3), // 그림자 위치 조정
              ),
            ],
            borderRadius: const BorderRadius.only(
              topLeft: Radius.circular(20.0),
              topRight: Radius.circular(20.0),
            ), // 모서리 둥글게
          ),
          child: Column(
            children: [
              // 첫 번째 그룹: 기기 등록, 홈 스캔, 모드 변경
              Container(
                decoration: BoxDecoration(
                  color: Colors.grey[200],
                  borderRadius: BorderRadius.circular(10),
                  boxShadow: [
                    BoxShadow(
                      color: Colors.grey.withOpacity(0.5),
                      spreadRadius: 1,
                      blurRadius: 1,
                      offset: const Offset(0, 1), // 그림자 위치 조정
                    ),
                  ],
                ),
                child: Column(
                  children: [
                    _buildMenuItem(Icons.android, "기기 등록"),
                    _buildDivider(),
                    _buildMenuItem(Icons.home_outlined, "홈 스캔"),
                    _buildDivider(),
                    _buildMenuItem(Icons.meeting_room_outlined, "방 관리"),
                    _buildDivider(),
                    _buildMenuItem(Icons.cloud_download_outlined, "가전 관리"),
                  ],
                ),
              ),
              const SizedBox(height: 20),
              // 두 번째 그룹: 사물 등록, 사물 제어
              Container(
                decoration: BoxDecoration(
                  color: Colors.grey[200],
                  borderRadius: BorderRadius.circular(10),
                  boxShadow: [
                    BoxShadow(
                      color: Colors.grey.withOpacity(0.5),
                      spreadRadius: 1,
                      blurRadius: 1,
                      offset: const Offset(0, 1), // 그림자 위치 조정
                    ),
                  ],
                ),
                child: Column(
                  children: [
                    _buildMenuItem(Icons.camera_enhance, "사물 등록"),
                    _buildDivider(),
                    _buildMenuItem(Icons.control_camera, "사물 제어"),
                  ],
                ),
              ),
              const SizedBox(height: 20),
              // 세 번째 그룹: 로그아웃
              Container(
                decoration: BoxDecoration(
                  color: Colors.grey[200],
                  borderRadius: BorderRadius.circular(10),
                  boxShadow: [
                    BoxShadow(
                      color: Colors.grey.withOpacity(0.5),
                      spreadRadius: 1,
                      blurRadius: 1,
                      offset: const Offset(0, 1), // 그림자 위치 조정
                    ),
                  ],
                ),
                child: _buildMenuItem(Icons.exit_to_app, "로그아웃"),
              ),
            ],
          ),
        ),
      ),
    );
  }

  Widget _buildMenuItem(IconData icon, String title) {
    return ListTile(
      leading: Icon(icon),
      title: Text(title),
      onTap: () => menuTabController.tabItem(title),
    );
  }

  Widget _buildDivider() => const Divider(height: 1, thickness: 1);
}
