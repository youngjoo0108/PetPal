import 'package:flutter/material.dart';
import 'package:frontend/const/global_alert_dialog.dart';
import 'package:frontend/service/user_service.dart';
import 'package:frontend/const/colors.dart';
import 'package:frontend/screen/main_screen.dart';

class LoginScreen extends StatefulWidget {
  const LoginScreen({super.key});

  @override
  LoginScreenState createState() => LoginScreenState();
}

class LoginScreenState extends State<LoginScreen> {
  UserService userService = UserService();

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      // 전체 배경색 설정
      backgroundColor: lightYellow,
      body: Center(
        child: Column(
          mainAxisAlignment: MainAxisAlignment.center,
          children: [
            // 로고 이미지를 추가합니다.
            Image.asset(
              'asset/img/logo.png',
              width: MediaQuery.of(context).size.width / 3,
            ),
            const Text(
              'PETPAL',
              style: TextStyle(
                fontSize: 24, // 글자 크기를 조정합니다.
                fontWeight: FontWeight.bold, // 글자를 굵게 표시합니다.
              ),
            ),
            const SizedBox(height: 10), // 로고와 로그인 버튼 사이의 간격을 조정합니다.
            // 카카오 로그인 이미지 버튼
            GestureDetector(
              onTap: () async {
                bool isSuccess = await userService.loginWithKakao();
                if (isSuccess) {
                  // 로그인 성공 알림
                  GlobalAlertDialog.show(
                    context,
                    title: "로그인 성공",
                    message: "환영합니다!",
                  ).then((_) {
                    Navigator.of(context).pushReplacement(
                      MaterialPageRoute(
                          builder: (context) => const MainScreen()),
                    );
                  });
                } else {
                  // 로그인 실패 알림
                  GlobalAlertDialog.show(
                    context,
                    title: "로그인 실패",
                    message: "다시 시도해주세요.",
                  );
                }
              },
              child: Image.asset('asset/img/kakaoLogin.png'),
            ),
          ],
        ),
      ),
    );
  }
}
