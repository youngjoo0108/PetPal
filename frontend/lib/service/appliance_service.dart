import 'dart:convert';
import 'package:http/http.dart' as http;
import 'package:frontend/model/appliance.dart';
import 'package:flutter_dotenv/flutter_dotenv.dart';

class ApplianceService {
  final _baseUrl = dotenv.env['BASE_URL'];

  Future<List<Appliance>> fetchAppliances() async {
    final uri = Uri.parse('$_baseUrl/appliances');
    final response =
        await http.get(uri, headers: {"Content-Type": "application/json"});

    if (response.statusCode == 200) {
      List jsonResponse = json.decode(response.body);
      return jsonResponse
          .map<Appliance>((json) => Appliance.fromJson(json))
          .toList();
    } else {
      // 에러 처리: 서버로부터 오류 응답을 받았을 때, 예외를 던집니다.
      throw Exception('Failed to load appliances from the server');
    }
  }

  // ApplianceService 클래스 내부에 추가
  Future<List<Appliance>> fetchAvailableAppliances() async {
    final uri = Uri.parse('$_baseUrl/availableAppliances');
    final response =
        await http.get(uri, headers: {"Content-Type": "application/json"});

    if (response.statusCode == 200) {
      List jsonResponse = json.decode(response.body);
      return jsonResponse
          .map<Appliance>((json) => Appliance.fromJson(json))
          .toList();
    } else {
      throw Exception('Failed to load available appliances from the server');
    }
  }

  Future<void> registerAppliance(
      String homeId, int roomId, String applianceType) async {
    final uri = Uri.parse('$_baseUrl/registerAppliance');
    final response = await http.post(
      uri,
      headers: {"Content-Type": "application/json"},
      body: json.encode({
        'homeId': homeId,
        'roomId': roomId,
        'applianceType': applianceType,
      }),
    );

    if (response.statusCode != 200) {
      throw Exception('Failed to register appliance');
    }
    // 성공적으로 등록되었을 경우 추가로 처리할 사항이 있다면 여기에 코드를 추가합니다.
  }
}
