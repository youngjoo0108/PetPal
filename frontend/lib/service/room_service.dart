import 'dart:convert';
import 'package:http/http.dart' as http;
import 'package:frontend/model/room.dart';

class RoomService {
  static const String _baseUrl = "https://your.api/rooms"; // API 엔드포인트 주소 변경 필요

  // 서버로부터 전체 방 목록을 불러오는 메서드
  static Future<List<Room>> getRooms() async {
    final response = await http.get(Uri.parse(_baseUrl));
    if (response.statusCode == 200) {
      List<dynamic> body = jsonDecode(response.body);
      List<Room> rooms =
          body.map((dynamic item) => Room.fromJson(item)).toList();
      return rooms;
    } else {
      throw Exception('Failed to load rooms');
    }
  }

  // 서버로부터 등록 가능한 방 목록을 불러오는 메서드
  static Future<List<Room>> getAvailableRooms() async {
    final response = await http.get(Uri.parse("$_baseUrl/available"));
    if (response.statusCode == 200) {
      List<dynamic> body = jsonDecode(response.body);
      List<Room> rooms =
          body.map((dynamic item) => Room.fromJson(item)).toList();
      return rooms;
    } else {
      throw Exception('Failed to load available rooms');
    }
  }

  // 새로운 방을 등록하는 메서드 (예시)
  static Future<Room> registerRoom(Room room) async {
    final response = await http.post(
      Uri.parse(_baseUrl),
      headers: {'Content-Type': 'application/json'},
      body: jsonEncode(room.toJson()),
    );

    if (response.statusCode == 201) {
      return Room.fromJson(jsonDecode(response.body));
    } else {
      throw Exception('Failed to register room');
    }
  }
}
