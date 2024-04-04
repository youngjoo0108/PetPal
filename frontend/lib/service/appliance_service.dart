import 'dart:convert';
import 'package:flutter_secure_storage/flutter_secure_storage.dart';
import 'package:http/http.dart' as http;
import 'package:frontend/model/appliance.dart';
import 'package:flutter_dotenv/flutter_dotenv.dart';
import 'package:logger/logger.dart';

final Logger logger = Logger();

class ApplianceService {
  final _baseUrl = dotenv.env['BASE_URL'];
  final FlutterSecureStorage _storage = const FlutterSecureStorage();

  Future<List<Appliance>> fetchAppliances() async {
    final String? homeIdString = await _storage.read(key: 'homeId');
    final int? homeId =
        homeIdString != null ? int.tryParse(homeIdString) : null;

    if (homeId == null) {
      throw Exception('Invalid or missing homeId');
    }

    final uri = Uri.parse('$_baseUrl/appliances/home/$homeId');
    final response =
        await http.get(uri, headers: {"Content-Type": "application/json"});

    if (response.statusCode == 200) {
      final responseBody = utf8.decode(response.bodyBytes);
      logger.d(responseBody);
      List<dynamic> body = jsonDecode(responseBody);
      List<Appliance> appliances =
          body.map((dynamic item) => Appliance.fromJson(item)).toList();
      return appliances;
    } else {
      // 에러 처리: 서버로부터 오류 응답을 받았을 때, 예외를 던집니다.
      throw Exception('Failed to load appliances from the server');
    }
  }

  // ApplianceService 클래스 내부에 추가
  Future<List<String>> fetchAvailableAppliances() async {
    final uri = Uri.parse('$_baseUrl/appliances/default');
    final response =
        await http.get(uri, headers: {"Content-Type": "application/json"});

    if (response.statusCode == 200) {
      final responseBody = utf8.decode(response.bodyBytes);
      logger.d(responseBody);
      List<dynamic> decodedList = jsonDecode(responseBody);
      List<String> applianceTypes = decodedList.cast<String>();

      return applianceTypes;
    } else {
      throw Exception('Failed to load available appliances from the server');
    }
  }

  Future<int> registerAppliance(
      int roomId, String applianceType, String applianceUUID) async {
    final String? homeIdString = await _storage.read(key: 'homeId');
    final int? homeId =
        homeIdString != null ? int.tryParse(homeIdString) : null;

    if (homeId == null) {
      throw Exception('Invalid or missing homeId');
    }
    logger.e("$homeId-$roomId-$applianceType");
    final uri = Uri.parse('$_baseUrl/appliances');
    final response = await http.post(
      uri,
      headers: {"Content-Type": "application/json"},
      body: json.encode({
        'applianceType': applianceType,
        "applianceUUID": applianceUUID,
        "coordinate": {"x": 37.422, "y": -122.084},
        'homeId': homeId,
        'roomId': roomId,
      }),
    );
    logger.d('Register Appliance response.statusCode : ${response.statusCode}');
    if (response.statusCode == 200) {
      return 1;
    } else if (response.statusCode == 409) {
      return 2;
    } else {
      return 0;
    }
    // 성공적으로 등록되었을 경우 추가로 처리할 사항이 있다면 여기에 코드를 추가합니다.
  }

  Future<bool> deleteAppliance(int applianceId) async {
    final uri = Uri.parse('$_baseUrl/appliances/$applianceId');
    final response =
        await http.delete(uri, headers: {"Content-Type": "application/json"});

    if (response.statusCode == 200) {
      logger.d('Appliance deleted successfully');
      return true;
    } else {
      // 에러 로그를 남깁니다. 실제 구현에서는 에러 처리 방법을 더 세분화할 수 있습니다.
      logger
          .e('Failed to delete appliance. StatusCode: ${response.statusCode}');
      return false;
    }
  }
}
