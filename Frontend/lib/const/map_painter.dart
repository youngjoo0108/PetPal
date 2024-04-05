import 'package:flutter/material.dart';
import 'package:logger/logger.dart';

class MapPainter extends CustomPainter {
  final List<List<int>> mapData;
  final double width;
  final double height;
  final int row;
  final int column;
  final Logger logger = Logger();

  MapPainter(this.mapData, this.width, this.height, this.row, this.column);

  @override
  void paint(Canvas canvas, Size size) {
    final startTime = DateTime.now();
    // logger.d('Rendering Started at $startTime');

    // 캔버스 실제 높이와 너비에 맞게 cell size 조정
    double cellWidth = size.width / column;
    double cellHeight = size.height / row;

    Paint paint = Paint();
    for (int i = 0; i < row; i++) {
      for (int j = 0; j < column; j++) {
        if (mapData[i][j] <= 33) {
          paint.color = Colors.white;
        } else if (mapData[i][j] <= 66) {
          paint.color = Colors.grey;
        } else {
          paint.color = Colors.black;
        }
        canvas.drawRect(
          Rect.fromLTWH(j * cellWidth, i * cellHeight, cellWidth, cellHeight),
          paint,
        );
      }
    }
    logger.e("Recalling Map_Painter");

    // 렌더링 종료 시간 로깅
    final endTime = DateTime.now();
    // logger.d('Rendering ended at $endTime');
    // 렌더링에 걸린 총 시간 로깅
    final duration = endTime.difference(startTime);
    logger.d('Total rendering time: ${duration.inMilliseconds} ms');
  }

  @override
  bool shouldRepaint(covariant MapPainter oldDelegate) {
    // 여기서는 mapData의 참조가 변경되었는지를 확인하지만, 실제로는
    // 내용이 변경되었는지까지 확인해야 할 수도 있습니다.
    // mapData의 내용이 매우 자주 변경되지 않는다면, 다른 식별자를 사용하는 것을 고려하세요.
    if (mapData == oldDelegate.mapData) {
      logger.e("checkPoint1");
    } else {
      logger.e("checkPoint2");
    }

    return mapData != oldDelegate.mapData;
  }
}
