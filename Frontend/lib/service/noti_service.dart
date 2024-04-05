import 'dart:convert';
import 'package:flutter_dotenv/flutter_dotenv.dart';
import 'package:flutter_secure_storage/flutter_secure_storage.dart';
import 'package:frontend/model/notification.dart';
import 'package:http/http.dart' as http;
import 'package:logger/logger.dart';

final Logger logger = Logger();

class NotificationService {
  final _baseUrl = dotenv.env['BASE_URL'];
  FlutterSecureStorage secureStorage = const FlutterSecureStorage();

  Future<List<Noti>> fetchNotifications() async {
    final String? userIdString = await secureStorage.read(key: "userId");
    // String을 int로 안전하게 변환
    final int? userId = int.tryParse(userIdString ?? '');

    if (userId == null) {
      throw Exception('Invalid userId');
    }
    final response =
        await http.get(Uri.parse('$_baseUrl/notifications/$userId'));
    if (response.statusCode == 200) {
      final responseBody = utf8.decode(response.bodyBytes);
      logger.d(responseBody);
      List<dynamic> body = jsonDecode(responseBody);
      List<Noti> notis =
          body.map((dynamic item) => Noti.fromJson(item)).toList();
      return notis;
    } else {
      throw Exception('Failed to load notifications');
    }
  }

  Future<bool> deleteNotification(int notiId) async {
    final uri = Uri.parse('$_baseUrl/notifications/$notiId');
    final response =
        await http.delete(uri, headers: {"Content-Type": "application/json"});

    if (response.statusCode == 200) {
      logger.d('Notification deleted successfully');
      return true;
    } else {
      logger.e(
          'Failed to delete Notification. StatusCode: ${response.statusCode}');
      return false;
    }
  }
}
