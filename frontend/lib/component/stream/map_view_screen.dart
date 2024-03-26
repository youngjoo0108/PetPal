import 'package:flutter/material.dart';
import 'package:flutter/services.dart' show rootBundle;
import 'package:frontend/const/map_painter.dart';
import 'package:frontend/service/user_service.dart';

// ROS에서 가져오는 맵 데이터 연산 및 map_painter를 호출해서 화면에 렌더링

class MapView extends StatefulWidget {
  const MapView({super.key});

  @override
  State<MapView> createState() => _MapViewState();
}

class _MapViewState extends State<MapView> {
  Future<List<List<int>>>? mapDataFuture;
  late final int row;
  late final int column;

  @override
  void initState() {
    super.initState();
    mapDataFuture = loadMapData();
  }

  Future<List<List<int>>> loadMapData() async {
    logger.d("checkPoint1");
    final String fileString =
        await rootBundle.loadString('asset/test/newMap.txt');
    logger.d("checkPoint2");

    List<String> elements = [];
    try {
      // 줄바꿈(\n)을 제거
      String noNewLines = fileString.replaceAll('\n', ' ');
      // 공백 제거
      elements = noNewLines.split(' ');
    } catch (e) {
      logger.e(e);
    }

    // 첫 번째와 두 번째 요소를 N과 M으로 변환
    int N = int.parse(elements[0]);
    row = N;
    int M = int.parse(elements[1]);
    column = M;
    logger.d("checkPoint3");
    // 나머지 요소들을 int로 변환
    // List<int> intElements =
    //     elements.sublist(2).map((e) => int.parse(e)).toList();
    List<int> intElements = [];
    try {
      intElements = elements
          .sublist(2)
          .map((e) {
            try {
              return int.parse(e);
            } catch (e) {
              logger.e("Parsing error for value: $e"); // 오류 발생시 로그 출력
              return null; // 오류가 발생한 경우 null 반환 (또는 적절한 기본값 설정)
            }
          })
          .where((e) => e != null)
          .cast<int>()
          .toList(); // null이 아닌 요소만 필터링
    } catch (e) {
      logger.e("Error converting elements to integers: $e");
    }

    // NxM 크기의 2차원 정수 리스트로 변환
    List<List<int>> mapData =
        List.generate(N, (_) => List.generate(M, (_) => 0));

    for (int i = 0; i < N; i++) {
      for (int j = 0; j < M; j++) {
        int idx = i * M + j; // M을 곱해주어야 올바른 인덱스 계산
        if (idx < intElements.length) {
          mapData[i][j] = intElements[idx];
        }
      }
    }

    return mapData;
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
            painter: MapPainter(
                snapshot.data!, screenWidth, screenWidth, row, column),
          );
        } else {
          return const Center(child: CircularProgressIndicator());
        }
      },
    );
  }
}
