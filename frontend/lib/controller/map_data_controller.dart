import 'package:flutter_dotenv/flutter_dotenv.dart';
import 'package:frontend/const/secure_storage.dart';
import 'package:get/get.dart';
import 'package:http/http.dart' as http;
import 'dart:convert';
import 'package:logger/logger.dart';

Logger logger = Logger();

class MapDataController extends GetxController {
  // mapData 상태를 관리합니다. GetX의 RxString을 사용하여 반응형 상태 관리를 합니다.
  var mapData = ''.obs;
  final _baseUrl = dotenv.env['BASE_URL'];
  final _storage = SecureStorage();

  // 서버로부터 mapData를 가져오는 메서드
  Future<void> fetchMapData() async {
    final String? homeIdString = await _storage.getHomeId("homeId");
    // String을 int로 안전하게 변환
    final int? homeId = int.tryParse(homeIdString ?? '');

    if (homeId == null) {
      throw Exception('Invalid homeId');
    }
    final response = await http.get(Uri.parse("$_baseUrl/maps/$homeId"));
    if (response.statusCode == 200) {
      final responseBody = utf8.decode(response.bodyBytes);
      // 서버로부터 받은 mapData를 업데이트합니다.
      mapData.value = jsonDecode(responseBody);
    } else {
      // 요청 실패 처리
      logger.e('Failed to fetch mapdata'); // 실제 앱에서는 logger 등을 사용할 수 있습니다.
    }
  }
}
