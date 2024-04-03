import 'package:flutter/material.dart';
import 'package:frontend/const/map_painter.dart';
import 'package:frontend/controller/map_data_controller.dart';
import 'package:get/get.dart';
import 'package:logger/logger.dart';

final Logger logger = Logger();

class MapScreen extends StatefulWidget {
  const MapScreen({super.key});

  @override
  State<MapScreen> createState() => _MapScreenState();
}

class _MapScreenState extends State<MapScreen> {
  late final MapDataController mapDataController;

  @override
  void initState() {
    super.initState();
    mapDataController = Get.put(MapDataController());
    if (mapDataController.mapData.value.isEmpty) {
      mapDataController.fetchMapData();
    }
    mapDataController.initWebSocket();
  }

  @override
  Widget build(BuildContext context) {
    return Padding(
      padding: const EdgeInsets.all(20.0),
      child: ClipRRect(
        borderRadius: BorderRadius.circular(10.0),
        child: LayoutBuilder(
          builder: (BuildContext context, BoxConstraints constraints) {
            final screenWidth = constraints.maxWidth;
            final screenHeight = constraints.maxHeight;

            return Stack(
              children: [
                Obx(() {
                  if (mapDataController.mapData.value.isNotEmpty) {
                    return RepaintBoundary(
                      child: CustomPaint(
                        size: Size(screenWidth, screenHeight),
                        painter: MapPainter(
                          mapDataController.mapData.value,
                          screenWidth,
                          screenHeight,
                          mapDataController.row.value,
                          mapDataController.column.value,
                        ),
                      ),
                    );
                  } else {
                    // mapData가 없을 때의 대체 위젯
                    return const Center(
                      child: CircularProgressIndicator(),
                    );
                  }
                }),
                Obx(() {
                  final targetX = mapDataController.turtleX.value;
                  final targetY = mapDataController.turtleY.value;

                  // targetX와 targetY가 0이 아닐 때만 렌더링
                  if (targetX > 0 && targetY > 0) {
                    const double imageWidth = 25.0;
                    const double imageHeight = 25.0;
                    final double imageX = mapDataController.column.value > 0
                        ? (screenWidth / mapDataController.column.value) *
                                targetX -
                            (imageWidth / 2)
                        : 0;
                    final double imageY = mapDataController.row.value > 0
                        ? (screenHeight / mapDataController.row.value) *
                                targetY -
                            (imageHeight / 2)
                        : 0;

                    return Positioned(
                      left: imageX,
                      top: imageY,
                      child: Image.asset(
                        'asset/img/turtle.png',
                        width: imageWidth,
                        height: imageHeight,
                      ),
                    );
                  } else {
                    // targetX와 targetY가 0일 때의 대체 위젯
                    return const Center(
                      child: CircularProgressIndicator(),
                    );
                  }
                }),
              ],
            );
          },
        ),
      ),
    );
  }

  @override
  void dispose() {
    logger.d("MapScreenDispose");
    mapDataController.unsubscribeFn(); // 구독 해지 함수 호출
    super.dispose();
  }
}
