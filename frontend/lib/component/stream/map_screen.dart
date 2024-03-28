import 'package:flutter/material.dart';
import 'package:flutter/services.dart';
import 'package:frontend/component/stream/map_view_screen.dart';
import 'package:logger/logger.dart';

final Logger logger = Logger();

class MapScreen extends StatelessWidget {
  const MapScreen({super.key});

  // 맵 데이터를 로드
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
    int M = int.parse(elements[1]);
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
    return Padding(
      padding: const EdgeInsets.all(20.0),
      child: ClipRRect(
        borderRadius: BorderRadius.circular(10.0),
        child: FutureBuilder<List<List<int>>>(
          future: loadMapData(), // 비동기적으로 맵 데이터를 로드
          builder: (context, snapshot) {
            if (snapshot.connectionState == ConnectionState.waiting) {
              return const Center(
                  child: CircularProgressIndicator()); // 데이터 로딩 중 표시
            } else if (snapshot.hasError) {
              return Center(
                  child: Text('Error: ${snapshot.error}')); // 오류 발생시 표시
            } else if (snapshot.hasData) {
              // 데이터 로딩 완료, MapView에 데이터 전달
              return MapView(
                  mapData: snapshot.data!); // MapView 생성자에 mapData 매개변수 추가 필요
            } else {
              return const Center(child: Text('No data')); // 데이터 없음 표시
            }
          },
        ),
      ),
    );
  }
}
