import 'dart:convert';
import 'package:flutter/material.dart';
import 'package:frontend/const/secure_storage.dart';
import 'package:http/http.dart' as http;
import 'package:frontend/model/room.dart';
import 'package:flutter_dotenv/flutter_dotenv.dart';
import 'package:logger/logger.dart';

Logger logger = Logger();

class RoomService {
  final _baseUrl = dotenv.env['BASE_URL'];
  final _storage = SecureStorage();

  // 서버로부터 전체 방 목록을 불러오는 메서드
  Future<List<Room>> getRooms() async {
    final String? homeIdString = await _storage.getHomeId("homeId");
    // String을 int로 안전하게 변환
    final int? homeId = int.tryParse(homeIdString ?? '');

    if (homeId == null) {
      throw Exception('Invalid homeId');
    }
    final response = await http.get(Uri.parse("$_baseUrl/rooms/$homeId"));
    if (response.statusCode == 200) {
      final responseBody = utf8.decode(response.bodyBytes);
      logger.d(responseBody);
      List<dynamic> body = jsonDecode(responseBody);
      List<Room> rooms =
          body.map((dynamic item) => Room.fromJson(item)).toList();
      return rooms;
    } else {
      throw Exception('Failed to load rooms');
    }
  }

  // 서버로부터 등록 가능한 방 목록을 불러오는 메서드
  Future<List<String>> getAvailableRooms() async {
    final response = await http.get(Uri.parse("$_baseUrl/rooms/default"));
    if (response.statusCode == 200) {
      final responseBody = utf8.decode(response.bodyBytes);
      logger.d(responseBody);
      List<dynamic> decodedList = jsonDecode(responseBody);
      List<String> roomNames = decodedList.cast<String>();

      return roomNames;
    } else {
      throw Exception('Failed to load available rooms');
    }
  }

  // 방 등록
  Future<int> registerRoom(BuildContext context, String roomName) async {
    final String? homeIdString = await _storage.getHomeId('homeId');
    final int? homeId =
        homeIdString != null ? int.tryParse(homeIdString) : null;

    if (homeId == null) {
      throw Exception('Invalid or missing homeId');
    }

    final response = await http.post(
      Uri.parse("$_baseUrl/rooms"),
      headers: {'Content-Type': 'application/json'},
      // Room 객체 대신 직접 생성한 JSON 객체를 전송
      body: jsonEncode({
        'roomName': roomName,
        'homeId': homeId,
      }),
    );
    logger.d('Register Room response.statusCode : ${response.statusCode}');
    if (response.statusCode == 200) {
      return 1;
    } else if (response.statusCode == 409) {
      return 2;
    } else {
      return 0;
    }
  }
}
