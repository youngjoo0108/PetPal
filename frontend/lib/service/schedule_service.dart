import 'dart:convert';
import 'package:flutter/material.dart';
import 'package:frontend/model/schedule.dart';
import 'package:http/http.dart' as http;
import 'package:frontend/model/appliance.dart';
import 'package:flutter_secure_storage/flutter_secure_storage.dart';
import 'package:flutter_dotenv/flutter_dotenv.dart';
import 'package:logger/logger.dart';

final Logger logger = Logger();

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
    required String taskType, // "ON" 또는 "OFF"
  }) async {
    // homeId 가져오기
    final String? homeIdString = await _storage.read(key: "homeId");
    // String을 int로 안전하게 변환
    final int? homeId = int.tryParse(homeIdString ?? '');

    if (homeId == null) {
      throw Exception('Invalid homeId');
    }

    // date를 YYYY-MM-DD 형식으로 변환
    String formattedDate =
        "${date.year}-${date.month.toString().padLeft(2, '0')}-${date.day.toString().padLeft(2, '0')}";

    // time을 HH-MM 형식으로 변환
    String formattedTime =
        "${time.hour.toString().padLeft(2, '0')}:${time.minute.toString().padLeft(2, '0')}";

    final uri = Uri.parse('$_baseUrl/schedules');
    final response = await http.post(uri,
        headers: {"Content-Type": "application/json"},
        body: jsonEncode({
          'roomId': appliance.roomId, // Appliance 객체에서 roomId를 가져옴
          'homeId': homeId, // homeId를 int로 변환
          'applianceId': appliance.applianceId,
          'day': formattedDate,
          'time': formattedTime,
          'taskType': taskType, // "ON" 또는 "OFF"
          'isActive': true, // 무조건 true로 설정
        }));

    return response.statusCode == 200;
  }

  Future<List<Schedule>> fetchSchedules() async {
    final String? homeIdString = await _storage.read(key: "homeId");
    // String을 int로 안전하게 변환
    final int? homeId = int.tryParse(homeIdString ?? '');

    if (homeId == null) {
      throw Exception('Invalid homeId');
    }

    final uri = Uri.parse('$_baseUrl/schedules/$homeId');
    final response =
        await http.get(uri, headers: {"Content-Type": "application/json"});

    if (response.statusCode == 200) {
      final responseBody = utf8.decode(response.bodyBytes);
      logger.d(responseBody);
      List<dynamic> body = jsonDecode(responseBody);
      List<Schedule> schedules =
          body.map((dynamic item) => Schedule.fromJson(item)).toList();
      return schedules;
    } else {
      throw Exception('Failed to load reservations');
    }
  }

  Future<bool> deleteSchedule(int scheduleId) async {
    final uri = Uri.parse('$_baseUrl/schedules/$scheduleId');
    final response =
        await http.delete(uri, headers: {"Content-Type": "application/json"});

    return response.statusCode == 200;
  }
}
