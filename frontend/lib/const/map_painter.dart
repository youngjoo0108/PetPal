import 'package:flutter/material.dart';

class MapPainter extends CustomPainter {
  final List<List<int>> mapData;
  final double width;
  final double height;

  MapPainter(this.mapData, this.width, this.height);

  @override
  void paint(Canvas canvas, Size size) {
    double cellWidth = width / 70;
    double cellHeight = height / 70;

    Paint paint = Paint();
    for (int i = 0; i < 70; i++) {
      for (int j = 0; j < 70; j++) {
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
