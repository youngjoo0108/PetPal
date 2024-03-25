import 'package:flutter/material.dart';
import 'package:frontend/const/secure_storage.dart';
import 'package:frontend/screen/login_screen.dart';
// import 'package:frontend/screen/login_screen.dart';
import 'package:frontend/screen/main_screen.dart';
import 'package:kakao_flutter_sdk_user/kakao_flutter_sdk_user.dart';
import 'package:timezone/data/latest.dart' as tz;

void main() async {
  tz.initializeTimeZones();
  KakaoSdk.init(nativeAppKey: 'ade5c985e60c36e2dd8215574c94f246');
  runApp(MyApp());
}

class MyApp extends StatelessWidget {
  // flutter_secure_storage 인스턴스 생성
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

// -------------------------------------Map Rendering Test
// import 'dart:ui' as ui;
// import 'package:flutter/material.dart';
// import 'package:flutter/services.dart' show rootBundle;

// void main() {
//   runApp(const MaterialApp(home: MapView()));
// }

// class MapView extends StatefulWidget {
//   const MapView({super.key});

//   @override
//   MapViewState createState() => MapViewState();
// }

// class MapViewState extends State<MapView> {
//   Future<List<List<int>>>? mapDataFuture;

//   @override
//   void initState() {
//     super.initState();
//     mapDataFuture = loadMapData();
//   }

//   Future<List<List<int>>> loadMapData() async {
//     final String fileString =
//         await rootBundle.loadString('asset/test/home3.txt');
//     final lines = fileString.split('\n');
//     return lines.map((line) {
//       return line.split(' ').map(int.parse).toList();
//     }).toList();
//   }

//   @override
//   Widget build(BuildContext context) {
//     return Column(
//       children: [
//         const Text("CheckPoint"),
//         Expanded(
//           child: FutureBuilder<List<List<int>>>(
//             future: mapDataFuture,
//             builder: (context, snapshot) {
//               if (snapshot.connectionState == ConnectionState.done) {
//                 if (snapshot.hasError) {
//                   return Center(child: Text('Error: ${snapshot.error}'));
//                 }
//                 return CustomPaint(
//                   size: Size.infinite,
//                   painter: MapPainter(mapData: snapshot.data ?? []),
//                 );
//               }
//               return const Center(child: CircularProgressIndicator());
//             },
//           ),
//         ),
//       ],
//     );
//   }
// }

// class MapPainter extends CustomPainter {
//   final List<List<int>> mapData;

//   MapPainter({required this.mapData});

//   @override
//   void paint(ui.Canvas canvas, ui.Size size) {
//     final paint = Paint();
//     final cellWidth = size.width / mapData.length;
//     final cellHeight = size.height / mapData[0].length;

//     for (var i = 0; i < mapData.length; i++) {
//       for (var j = 0; j < mapData[i].length; j++) {
//         switch (mapData[i][j]) {
//           case 0:
//           case 1:
//           case 33:
//             paint.color = Colors.white;
//             break;
//           case 50:
//           case 34:
//           case 66:
//             paint.color = Colors.grey;
//             break;
//           case 100:
//           case 67:
//           case 99:
//             paint.color = Colors.black;
//             break;
//           default:
//             paint.color = Colors.grey[300]!;
//         }
//         canvas.drawRect(
//           Rect.fromLTWH(j * cellWidth, i * cellHeight, cellWidth, cellHeight),
//           paint,
//         );
//       }
//     }
//   }

//   @override
//   bool shouldRepaint(covariant CustomPainter oldDelegate) {
//     return false;
//   }
// }
