import 'dart:convert';
import 'package:http/http.dart' as http;
import 'package:flutter_dotenv/flutter_dotenv.dart';
import 'package:logger/logger.dart';

final Logger logger = Logger();
Future<Map<String, dynamic>> fetchWeatherByCity(String city) async {
  final apiKey = dotenv.env['OPENWEATHERMAP_API_KEY'];
  if (apiKey == null) {
    logger.e("WeatherAPI key not found");
    throw Exception('API key not found');
  }
  final requestUrl =
      'https://api.openweathermap.org/data/2.5/weather?q=$city&appid=$apiKey';
  final response = await http.get(Uri.parse(requestUrl));

  if (response.statusCode == 200) {
    logger.d("Succeed to fetch Weather data: ${json.decode(response.body)}");
    return json.decode(response.body);
  } else {
    throw Exception('Failed to load weather data');
  }
}
