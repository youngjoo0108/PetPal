import 'package:flutter/material.dart';
import 'package:frontend/const/map_painter.dart';
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
  final double targetX = 100;
  final double targetY = 100;
  // late double screenWidth;
  // late double screenHeight;
  late final MapPainter _mapPainter;

  @override
  void initState() {
    super.initState();
    _mapPainter = MapPainter(widget.mapData, 400, 400, 304, 250);
  }

  @override
  Widget build(BuildContext context) {
    logger.d("Rebuilding MapView");
    // 화면 너비와 높이를 계산
    double screenWidth = MediaQuery.of(context).size.width;
    double screenHeight = MediaQuery.of(context).size.height;

    // 맵 데이터의 행과 열에 따라 셀의 크기를 계산
    double cellWidth = screenWidth / widget.mapData[0].length;
    double cellHeight = screenHeight / widget.mapData.length;

    // 이미지를 맵의 중앙에 위치시키기 위한 계산
    const double imageWidth = 25.0;
    const double imageHeight = 25.0;
    final double imageX = cellWidth * targetX;
    final double imageY = cellHeight * targetY;

    return Stack(
      children: [
        CustomPaint(
          size: Size(screenWidth, screenHeight),
          painter: _mapPainter,
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
  }
}
