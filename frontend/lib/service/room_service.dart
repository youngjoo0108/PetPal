import 'dart:convert';
import 'package:frontend/const/secure_storage.dart';
import 'package:http/http.dart' as http;
import 'package:frontend/model/room.dart';
import 'package:flutter_dotenv/flutter_dotenv.dart';

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
      List<dynamic> body = jsonDecode(response.body);
      List<Room> rooms =
          body.map((dynamic item) => Room.fromJson(item)).toList();
      return rooms;
    } else {
      throw Exception('Failed to load rooms');
    }
  }

  // 서버로부터 등록 가능한 방 목록을 불러오는 메서드
  Future<List<Room>> getAvailableRooms() async {
    final response = await http.get(Uri.parse("$_baseUrl/rooms/default"));
    if (response.statusCode == 200) {
      List<dynamic> body = jsonDecode(response.body);
      List<Room> rooms =
          body.map((dynamic item) => Room.fromJson(item)).toList();
      return rooms;
    } else {
      throw Exception('Failed to load available rooms');
    }
  }

  // 방 등록
  Future<Room> registerRoom(Room room) async {
    final response = await http.post(
      Uri.parse("$_baseUrl/rooms"),
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
