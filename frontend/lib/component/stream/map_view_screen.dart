import 'package:flutter/material.dart';
import 'package:flutter/services.dart' show rootBundle;
import 'package:frontend/const/map_painter.dart';

class MapView extends StatefulWidget {
  const MapView({super.key});

  @override
  State<MapView> createState() => _MapViewState();
}

class _MapViewState extends State<MapView> {
  Future<List<List<int>>>? mapDataFuture;

  @override
  void initState() {
    super.initState();
    mapDataFuture = loadMapData();
  }

  Future<List<List<int>>> loadMapData() async {
    final String fileString = await rootBundle.loadString('asset/test/tt.txt');

    // 줄바꿈(\n)을 제거
    String noNewLines = fileString.replaceAll('\n', ' ');
    // 공백 제거
    List<String> elements = noNewLines.split(' ');

    // 마지막 두 요소(좌표) 제거
    // elements.removeLast(); // 첫 번째 좌표 제거
    // elements.removeLast(); // 두 번째 좌표 제거

    // 문자열 요소들을 int로 변환
    List<int> intElements = [];
    try {
      intElements = elements
          .map((e) {
            try {
              return double.parse(e).toInt();
            } catch (e) {
              print("Parsing error for value: $e"); // 오류 발생시 로그 출력
              return null; // 오류가 발생한 경우 null 반환 (또는 적절한 기본값 설정)
            }
          })
          .where((e) => e != null)
          .cast<int>()
          .toList(); // null이 아닌 요소만 필터링
    } catch (e) {
      print("Error converting elements to integers: $e");
    }

    // 700x700 크기의 2차원 정수 리스트로 변환
    List<List<int>> matrix70x70 =
        List.generate(70, (i) => List.generate(70, (j) => 0));

    for (int i = 0; i < 70; i++) {
      for (int j = 0; j < 70; j++) {
        int idx = i * 70 + j;
        if (idx < intElements.length) {
          matrix70x70[i][j] = intElements[idx];
        }
      }
    }
    print(matrix70x70[0][0]);

    return matrix70x70;
  }

  // Future<List<List<int>>> loadMapData() async {
  //   final String fileString =
  //       await rootBundle.loadString('asset/test/home3.txt');

  //   // 줄바꿈(\n)을 제거
  //   String noNewLines = fileString.replaceAll('\n', ' ');
  //   // 공백 제거
  //   List<String> elements = noNewLines.split(' ');

  //   // 마지막 두 요소(좌표) 제거
  //   elements.removeLast(); // 첫 번째 좌표 제거
  //   elements.removeLast(); // 두 번째 좌표 제거

  //   // 문자열 요소들을 int로 변환
  //   List<int> intElements = [];
  //   try {
  //     intElements = elements
  //         .map((e) {
  //           try {
  //             return int.parse(e);
  //           } catch (e) {
  //             print("Parsing error for value: $e"); // 오류 발생시 로그 출력
  //             return null; // 오류가 발생한 경우 null 반환 (또는 적절한 기본값 설정)
  //           }
  //         })
  //         .where((e) => e != null)
  //         .cast<int>()
  //         .toList(); // null이 아닌 요소만 필터링
  //   } catch (e) {
  //     print("Error converting elements to integers: $e");
  //   }

  //   // 700x700 크기의 2차원 정수 리스트로 변환
  //   List<List<int>> matrix700x700 =
  //       List.generate(700, (i) => List.generate(700, (j) => 0));

  //   for (int i = 0; i < 700; i++) {
  //     for (int j = 0; j < 700; j++) {
  //       int idx = i * 700 + j;
  //       if (idx < intElements.length) {
  //         matrix700x700[i][j] = intElements[idx];
  //       }
  //     }
  //   }
  //   print(matrix700x700[0][0]);

  //   return matrix700x700;
  // }

  @override
  Widget build(BuildContext context) {
    // 화면 너비를 가져옵니다.
    double screenWidth = MediaQuery.of(context).size.width;

    return FutureBuilder<List<List<int>>>(
      future: mapDataFuture,
      builder: (context, snapshot) {
        if (snapshot.connectionState == ConnectionState.done &&
            snapshot.hasData) {
          return CustomPaint(
            // 화면 크기에 맞게 CustomPaint의 크기를 조정합니다.
            size: Size(screenWidth, screenWidth), // 정사각형 형태로 조정
            painter: MapPainter(snapshot.data!, screenWidth, screenWidth),
          );
        } else {
          return const Center(child: CircularProgressIndicator());
        }
      },
    );
  }
}
