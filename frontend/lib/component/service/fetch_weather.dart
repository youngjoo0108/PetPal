import 'dart:convert';
import 'package:http/http.dart' as http;
import 'package:flutter_dotenv/flutter_dotenv.dart';

Future<Map<String, dynamic>> fetchWeather(String city) async {
  final apiKey = dotenv.env['OPENWEATHERMAP_API_KEY'];
  if (apiKey == null) {
    throw Exception('API key not found');
  }
  final requestUrl =
      'https://api.openweathermap.org/data/2.5/weather?q=$city&appid=$apiKey';
  final response = await http.get(Uri.parse(requestUrl));

  if (response.statusCode == 200) {
    return json.decode(response.body);
  } else {
    throw Exception('Failed to load weather data');
  }
}
