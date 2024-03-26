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
    logger.d('Rendering Started at $startTime');

    double cellWidth = width / column;
    double cellHeight = height / row;

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

    // 렌더링 종료 시간 로깅
    final endTime = DateTime.now();
    logger.d('Rendering ended at $endTime');
    // 렌더링에 걸린 총 시간 로깅
    final duration = endTime.difference(startTime);
    logger.d('Total rendering time: ${duration.inMilliseconds} ms');
  }

  @override
  bool shouldRepaint(covariant CustomPainter oldDelegate) => false;
}

// class MapPainter extends CustomPainter {
//   final List<List<int>> mapData;
//   final double width;
//   final double height;

//   MapPainter(this.mapData, this.width, this.height);

//   @override
//   void paint(Canvas canvas, Size size) {
//     double cellWidth = width / 700;
//     double cellHeight = height / 700;

//     Paint paint = Paint();
//     for (int i = 0; i < 700; i++) {
//       for (int j = 0; j < 700; j++) {
//         if (mapData[i][j] <= 33) {
//           paint.color = Colors.white;
//         } else if (mapData[i][j] <= 66) {
//           paint.color = Colors.grey;
//         } else {
//           paint.color = Colors.black;
//         }
//         canvas.drawRect(
//           Rect.fromLTWH(j * cellWidth, i * cellHeight, cellWidth, cellHeight),
//           paint,
//         );
//       }
//     }
//   }

//   @override
//   bool shouldRepaint(covariant CustomPainter oldDelegate) => false;
// }
