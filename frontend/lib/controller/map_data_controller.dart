import 'package:flutter_dotenv/flutter_dotenv.dart';
import 'package:flutter_secure_storage/flutter_secure_storage.dart';
import 'package:frontend/socket/socket.dart';
import 'package:get/get.dart';
import 'package:http/http.dart' as http;
import 'dart:convert';
import 'package:logger/logger.dart';

Logger logger = Logger();

class MapDataController extends GetxController {
  // mapData 상태를 관리합니다. 여기서는 2차원 정수 리스트로 관리됩니다.
  var mapData = Rx<List<List<int>>>([]);
  final _baseUrl = dotenv.env['BASE_URL'];
  final FlutterSecureStorage _secureStorage = const FlutterSecureStorage();
  final SocketController socketController = Get.find<SocketController>();
  dynamic unsubscribeFn;
  Rx<int> row = Rx<int>(0);
  Rx<int> column = Rx<int>(0);
  Rx<int> turtleX = Rx<int>(0);
  Rx<int> turtleY = Rx<int>(0);

  void initWebSocket() async {
    final String? homeId = await _secureStorage.read(key: "homeId");

    if (homeId != null) {
      unsubscribeFn = socketController.stompClient.subscribe(
        destination: '/exchange/control.exchange/home.$homeId',
        callback: (frame) {
          if (frame.body != null) {
            final data = json.decode(frame.body!);
            if (data['type'] == "TURTLE") {
              if (column.value != 0) {
                turtleX.value =
                    column.value - (data['message']['x'] as num).toInt();
                turtleY.value = (data['message']['y'] as num).toInt();
                logger.e("${turtleX.value}, ${turtleY.value}");
                turtleX.refresh();
                turtleY.refresh();
              }
            }
          }
        },
      );
    }
  }

  // 서버로부터 mapData를 가져오는 메서드
  Future<void> fetchMapData() async {
    final String? homeIdString = await _secureStorage.read(key: "homeId");
    final int? homeId = int.tryParse(homeIdString ?? '');

    if (homeId == null) {
      logger.e('Invalid homeId');
      return;
    }

    try {
      final response = await http.get(Uri.parse("$_baseUrl/maps/$homeId"));
      if (response.statusCode == 200) {
        logger.d("mapData.value.isEmpty: ${mapData.value.isEmpty}");
        final responseBody = utf8.decode(response.bodyBytes);
        // 서버로부터 받은 데이터를 2차원 정수 리스트로 변환합니다.
        final data = jsonDecode(responseBody);
        logger.d(data);
        // 예시 응답: "10 10 1 1 1 1 1 1 1 1 1 1 ..."
        // 첫 두 요소는 각각 N(행)과 M(열)을 나타냅니다.
        List<String> elements = [];
        try {
          // 줄바꿈(\n)을 제거
          String noNewLines = data["data"].replaceAll('\n', ' ');
          // 공백 제거
          elements = noNewLines.split(' ');
        } catch (e) {
          logger.e(e);
        }
        final int N = int.parse(elements[0]);
        row.value = N;
        final int M = int.parse(elements[1]);
        column.value = M;
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
        List<List<int>> newMapData =
            List.generate(N, (_) => List.generate(M, (_) => 0));

        for (int i = 0; i < N; i++) {
          for (int j = 0; j < M; j++) {
            int idx = i * M + j; // M을 곱해주어야 올바른 인덱스 계산
            if (idx < intElements.length) {
              newMapData[i][j] = intElements[idx];
            }
          }
        }
        List<List<int>> flippedMapData =
            newMapData.map((row) => row.reversed.toList()).toList();
        mapData.value = flippedMapData;

        logger.d("Succeed to fetch and parse map data");
      } else {
        logger.e('Failed to fetch mapdata: ${response.statusCode}');
      }
    } catch (e) {
      logger.e('Exception caught: $e');
    }
  }
}
