import 'package:flutter/material.dart';
import 'package:flutter/widgets.dart';
import 'package:flutter_secure_storage/flutter_secure_storage.dart';
import 'package:frontend/const/map_painter.dart';
import 'package:frontend/socket/socket.dart';
import 'package:get/get.dart';
import 'package:logger/logger.dart';

final Logger logger = Logger();

class MapView extends StatefulWidget {
  final List<List<int>> mapData;

  const MapView({
    super.key,
    required this.mapData,
  });

  @override
  State<MapView> createState() => _MapViewState();
}

class _MapViewState extends State<MapView> {
  final double targetX = 200;
  final double targetY = 300;
  late final MapPainter _mapPainter;
  final SocketController socketController = Get.find<SocketController>();
  final FlutterSecureStorage secureStorage = const FlutterSecureStorage();

  @override
  void initState() {
    super.initState();
    // 맵 페인터 초기화는 크기 정보 없이 여기서 수행
    _mapPainter = MapPainter(widget.mapData, 400, 400, 304, 250);
  }

  @override
  Widget build(BuildContext context) {
    logger.d("Rebuilding MapView");
    // LayoutBuilder를 사용하여 부모 위젯의 크기에 따라 적응적으로 레이아웃 구성
    return LayoutBuilder(
      builder: (BuildContext context, BoxConstraints constraints) {
        // constraints에서 부모의 최대 크기를 얻음
        final double screenWidth = constraints.maxWidth;
        final double screenHeight = constraints.maxHeight;

        // 맵 데이터의 행과 열에 따라 셀의 크기를 계산
        double cellWidth = screenWidth / widget.mapData[0].length;
        double cellHeight = screenHeight / widget.mapData.length;

        // 이미지를 맵의 지정된 위치에 위치시키기 위한 계산
        const double imageWidth = 25.0;
        const double imageHeight = 25.0;
        final double imageX =
            cellWidth * targetX - (imageWidth / 2); // 이미지 중앙 정렬
        final double imageY =
            cellHeight * targetY - (imageHeight / 2); // 이미지 중앙 정렬

        return Stack(
          children: [
            RepaintBoundary(
              child: CustomPaint(
                size: Size(screenWidth, screenHeight),
                painter: _mapPainter,
              ),
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
      },
    );
  }

  @override
  void dispose() {
    super.dispose();
  }
}
