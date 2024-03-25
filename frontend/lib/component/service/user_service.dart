import 'package:flutter_secure_storage/flutter_secure_storage.dart';
import 'package:kakao_flutter_sdk_user/kakao_flutter_sdk_user.dart';
import 'package:http/http.dart' as http;
import 'dart:convert';

class UserService {
  final FlutterSecureStorage secureStorage = const FlutterSecureStorage();

  // 카카오톡 로그인
  Future<void> loginWithKakao() async {
    try {
      try {
        // 카카오톡을 통한 로그인 시도
        await UserApi.instance.loginWithKakaoTalk();
      } catch (error) {
        // 카카오톡 설치되어 있지 않거나 로그인 실패 시, 계정으로 로그인 시도
        print("Fallback to Kakao Account Login: $error");
        await UserApi.instance.loginWithKakaoAccount();
      }

      /*
      --------------------사용자 정보 받아와서 저장하는 로직 추가
       */

      await secureStorage.write(key: "isLoggedIn", value: "true");
      // 추가적으로 사용자 정보를 받아와서 처리하는 로직을 여기에 구현할 수 있습니다.
    } catch (error) {
      print(error.toString());
    }
  }

  // 로그아웃
  Future<void> logout() async {
    await secureStorage.delete(key: "isLoggedIn"); // 로그인 상태 삭제
    // 필요한 경우, 카카오 SDK를 사용하여 카카오 로그아웃 호출을 추가할 수 있습니다.
    // 예: await UserApi.instance.logout();
  }

  // 서버에 토큰을 전송하는 함수
  Future<void> sendTokenToServer(String accessToken) async {
    try {
      final response = await http.post(
        Uri.parse('https://yourserver.com/api/login'),
        headers: <String, String>{
          'Content-Type': 'application/json; charset=UTF-8',
        },
        body: jsonEncode(<String, String>{
          'token': accessToken,
        }),
      );

      if (response.statusCode == 200) {
        // 서버로부터의 응답 처리
        print('Token successfully sent to the server');
      } else {
        // 서버 에러 처리
        print('Failed to send token to the server');
      }
    } catch (e) {
      print('Error sending token to the server: $e');
    }
  }
}
