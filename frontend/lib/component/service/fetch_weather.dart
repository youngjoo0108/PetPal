import 'dart:convert';
import 'package:http/http.dart' as http;

Future<Map<String, dynamic>> fetchWeather(String city) async {
  const apiKey = '64fe59603aa2261ee6110c1e5521c971';
  final requestUrl =
      'https://api.openweathermap.org/data/2.5/weather?q=$city&appid=$apiKey';
  final response = await http.get(Uri.parse(requestUrl));

  if (response.statusCode == 200) {
    return json.decode(response.body);
  } else {
    throw Exception('Failed to load weather data');
  }
}
