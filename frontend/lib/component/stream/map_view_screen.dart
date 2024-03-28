import 'package:flutter/material.dart';
import 'package:frontend/const/map_painter.dart';

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

  @override
  Widget build(BuildContext context) {
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
          painter:
              MapPainter(widget.mapData, screenWidth, screenHeight, 304, 250),
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
