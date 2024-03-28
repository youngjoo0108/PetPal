import 'package:firebase_core/firebase_core.dart';
import 'package:firebase_messaging/firebase_messaging.dart';
import 'package:flutter/material.dart';
import 'package:frontend/const/secure_storage.dart';
import 'package:frontend/screen/login_screen.dart';
import 'package:frontend/screen/main_screen.dart';
import 'package:kakao_flutter_sdk_user/kakao_flutter_sdk_user.dart';
import 'package:timezone/data/latest.dart' as tz;
import 'package:flutter_dotenv/flutter_dotenv.dart';
import 'package:logger/logger.dart';
import 'firebase_options.dart';

final Logger logger = Logger();
void main() async {
  WidgetsFlutterBinding.ensureInitialized();
  await dotenv.load(); // .env load
  tz.initializeTimeZones(); // init timeZone
  final kakaoApiKey = dotenv.env['KAKAO_API_KEY']; // load kakaoApiKey
  KakaoSdk.init(nativeAppKey: '$kakaoApiKey'); // KAKAO SDK init
  await Firebase.initializeApp(options: DefaultFirebaseOptions.currentPlatform);
  String? fcmToken = await FirebaseMessaging.instance.getToken();
  logger.e(fcmToken);
  runApp(MyApp());
}

class MyApp extends StatelessWidget {
  final SecureStorage secureStorage = SecureStorage();

  MyApp({super.key});

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      home: FutureBuilder(
        future: secureStorage.getLoginStatus("isLoggedIn"),
        builder: (context, snapshot) {
          if (snapshot.connectionState == ConnectionState.done) {
            if (snapshot.data == null) {
              return const LoginScreen();
            } else {
              return const MainScreen();
            }
          } else {
            return const CircularProgressIndicator();
          }
        },
      ),
    );
  }
}
