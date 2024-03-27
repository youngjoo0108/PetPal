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

  /*
  turtle 봇의 위치좌표, fetching 로직 추가
   */
  final double targetX = 100;
  final double targetY = 100;

  @override
  void initState() {
    super.initState();
    mapDataFuture = loadMapData();
  }

  Future<List<List<int>>> loadMapData() async {
    final String fileString =
        await rootBundle.loadString('asset/test/newMap.txt');

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

  @override
  Widget build(BuildContext context) {
    // 화면 너비를 가져옵니다.
    double screenWidth = MediaQuery.of(context).size.width;
    double screenHeight = MediaQuery.of(context).size.height;

    return FutureBuilder<List<List<int>>>(
      future: mapDataFuture,
      builder: (context, snapshot) {
        if (snapshot.connectionState == ConnectionState.done &&
            snapshot.hasData) {
          // 맵 데이터의 행과 열에 따라 셀의 크기를 계산
          double cellWidth = screenWidth / column;
          double cellHeight = screenWidth / row;
          // 이미지를 맵의 중앙에 위치시키기 위한 계산
          const double imageWidth = 25.0;
          const double imageHeight = 25.0; // 이미지 크기, 동적으로 조정 가능
          final double imageX = cellWidth * targetX;
          final double imageY = cellHeight * targetY;

          return Stack(
            children: [
              CustomPaint(
                size: Size(screenWidth, screenHeight),
                painter: MapPainter(snapshot.data!, screenWidth, screenWidth,
                    row, column), // MapPainter 구현 필요
              ),
              Positioned(
                left: imageX,
                top: imageY,
                child: Image.asset(
                  'asset/img/turtle.png',
                  width: imageWidth,
                  height: imageHeight,
                ),
              ),
            ],
          );
        } else {
          return const Center(child: CircularProgressIndicator());
        }
      },
    );
  }
}
