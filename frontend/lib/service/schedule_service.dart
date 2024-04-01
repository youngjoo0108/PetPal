import 'dart:convert';
import 'package:flutter/material.dart';
import 'package:frontend/model/schedule.dart';
import 'package:http/http.dart' as http;
import 'package:frontend/model/appliance.dart';
import 'package:flutter_secure_storage/flutter_secure_storage.dart';
import 'package:flutter_dotenv/flutter_dotenv.dart';

class ScheduleService {
  final _storage = const FlutterSecureStorage();
  final _baseUrl = dotenv.env['BASE_URL'];

  Future<String?> getHomeId() async {
    return await _storage.read(key: 'homeId');
  }

  Future<bool> addSchedule({
    required Appliance appliance,
    required DateTime date,
    required TimeOfDay time,
    required String action,
    required bool isActive,
  }) async {
    final uri = Uri.parse('$_baseUrl/reservations'); // 예약을 처리하는 서버의 엔드포인트
    final response = await http.post(uri,
        headers: {"Content-Type": "application/json"},
        body: jsonEncode({
          'applianceId':
              appliance.applianceId, // 예: Appliance 모델에 id 프로퍼티가 있다고 가정
          'date': date.toIso8601String(),
          'time': '${time.hour}:${time.minute}',
          'action': action,
          'isActive': isActive,
        }));

    if (response.statusCode == 200) {
      // 서버로부터 성공적인 응답을 받음
      return true;
    } else {
      // 실패 응답 처리
      return false;
    }
  }

  Future<List<Schedule>> fetchSchedules() async {
    String? homeId = await getHomeId();
    if (homeId == null) {
      throw Exception('Home ID not found');
    }

    final uri = Uri.parse('$_baseUrl/reservations/$homeId');
    final response =
        await http.get(uri, headers: {"Content-Type": "application/json"});

    if (response.statusCode == 200) {
      List jsonResponse = json.decode(response.body);
      return jsonResponse
          .map((reservation) => Schedule.fromJson(reservation))
          .toList();
    } else {
      throw Exception('Failed to load reservations');
    }
  }

  Future<bool> deleteSchedule(int scheduleId) async {
    final uri = Uri.parse('$_baseUrl/reservations/$scheduleId');
    final response =
        await http.delete(uri, headers: {"Content-Type": "application/json"});

    return response.statusCode == 200;
  }
}
