import 'package:flutter/material.dart';
import 'package:frontend/const/colors.dart';

class MenuScreen extends StatelessWidget {
  const MenuScreen({super.key});

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
                    _buildMenuItem(Icons.swap_horiz, "모드 변경"),
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
      onTap: () {
        /**
         * 각 항목을 탭했을 때 로직 추가--------------------------
         */
      },
    );
  }

  Widget _buildDivider() => const Divider(height: 1, thickness: 1);
}
