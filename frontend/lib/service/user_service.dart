import 'package:flutter_dotenv/flutter_dotenv.dart';
import 'package:flutter_secure_storage/flutter_secure_storage.dart';
import 'package:kakao_flutter_sdk_user/kakao_flutter_sdk_user.dart';
import 'package:http/http.dart' as http;
import 'dart:convert';
import 'package:logger/logger.dart';

var logger = Logger();

class UserService {
  final FlutterSecureStorage secureStorage = const FlutterSecureStorage();
  final baseUrl = dotenv.env['BASE_URL'];

  // 카카오톡 로그인
  Future<bool> loginWithKakao() async {
    try {
      OAuthToken token; // 카카오 로그인 성공 시 받은 토큰을 저장할 변수

      try {
        // 카카오톡을 통한 로그인 시도
        token = await UserApi.instance.loginWithKakaoTalk();
      } catch (error) {
        // 카카오톡 설치되어 있지 않거나 로그인 실패 시, 계정으로 로그인 시도
        logger.e("Fallback to Kakao Account Login: $error");
        token = await UserApi.instance.loginWithKakaoAccount();
      }

      // 로그인 성공 후, 토큰을 안전하게 저장하고 서버에 전송
      await secureStorage.write(key: "isLoggedIn", value: "true");
      await sendTokenToServer(token.accessToken); // 서버에 토큰 전송 로직 추가

      return true; // 로그인 성공 반환
    } catch (error) {
      logger.e(error.toString());
      return false; // 로그인 실패 반환
    }
  }

  // 로그아웃
  Future<void> logout() async {
    await secureStorage.delete(key: "isLoggedIn"); // 로그인 상태 삭제
    // 필요한 경우, 카카오 SDK를 사용하여 카카오 로그아웃 호출을 추가가능, ex. await UserApi.instance.logout();
  }

  Future<void> saveUserInfo(String accessToken) async {
    // 사용자 정보 불러오는 로직
    final Uri uri = Uri.parse('https://kapi.kakao.com/v2/user/me');

    final http.Response response = await http.get(
      uri,
      headers: {
        'Authorization': 'Bearer $accessToken',
      },
    );

    if (response.statusCode == 200) {
      // 사용자 정보를 성공적으로 가져온 경우
      final Map<String, dynamic> userInfo = json.decode(response.body);
      // final String userName = userInfo['properties']['nickname'];
      await secureStorage.write(
          key: "nickname", value: userInfo['properties']['nickname']);
      await secureStorage.write(
          key: "profileUrl",
          value: userInfo['properties'][
              'thumbnail_image_url']); // profile_image는 640x640, thumbnail_image는 110x110
      logger.d(
          '*********************************Succeeded in fetching userInfo: ${json.decode(response.body)}');
    } else {
      // 사용자 정보를 가져오는데 실패한 경우
      throw Exception('Failed to get user info: ${response.statusCode}');
    }

    // 토큰 유효성 검증
    // final Uri uri1 =
    //     Uri.parse('https://kapi.kakao.com/v1/user/access_token_info');

    // final http.Response response = await http.get(
    //   uri1,
    //   headers: {
    //     'Authorization': 'Bearer $accessToken',
    //   },
    // );

    // if (response.statusCode == 200) {
    //   // AccessToken이 유효한 경우
    //   print('Succeeded in validate access token: ${json.decode(response.body)}');
    // } else {
    //   // AccessToken이 유효하지 않은 경우
    //   throw Exception(
    //       'Failed to validate access token: ${response.statusCode}');
    // }
  }

  // 서버에 토큰을 전송하는 함수
  Future<void> sendTokenToServer(String accessToken) async {
    logger.d(accessToken);

    try {
      final response = await http.post(
        Uri.parse('$baseUrl/login/oauth/kakao'),
        headers: <String, String>{
          'Content-Type': 'application/json; charset=UTF-8',
        },
        body: jsonEncode(<String, String>{
          'accessToken': "Bearer $accessToken",
        }),
      );
      logger.d(
          "**********************************************response.statusCode: ${response.statusCode}");
      if (response.statusCode == 200) {
        // 서버로부터의 응답 처리
        logger.d('Token successfully sent to the server');

        // 응답 바디에서 accessToken & refreshToken 추출
        final Map<String, dynamic> responseData = json.decode(response.body);
        if (responseData.containsKey('accessToken') &&
            responseData.containsKey('refreshToken')) {
          final String serverAccessToken = responseData['accessToken'];
          final String serverRefreshToken = responseData['refreshToken'];
          // Token들을 FlutterSecureStorage에 저장
          await secureStorage.write(
              key: "accessToken", value: serverAccessToken);
          await secureStorage.write(
              key: "refreshToken", value: serverRefreshToken);
          logger.d('New Tokens from server stored successfully');
        } else {
          logger.w(
              'Failed to get Tokens, response does not contain Tokens: ${response.body}');
        }
      } else {
        // 서버 에러 처리
        logger.e('Failed to send token to the server: ${response.body}');
      }
    } catch (e) {
      logger.e('Error sending token to the server: $e');
    }
  }
}
