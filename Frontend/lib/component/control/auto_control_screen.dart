import 'dart:math';

import 'package:flutter/material.dart';
import 'package:flutter_secure_storage/flutter_secure_storage.dart';
import 'package:frontend/const/colors.dart';
import 'package:frontend/const/global_alert_dialog.dart';
// import 'package:frontend/const/colors.dart';
import 'package:frontend/model/appliance.dart';
import 'package:frontend/model/room.dart';
import 'package:frontend/service/appliance_service.dart';
import 'package:frontend/service/room_service.dart';
import 'package:frontend/socket/socket.dart';
import 'package:get/get.dart';
import 'package:logger/logger.dart';

final Logger logger = Logger();

class AutoControlScreen extends StatefulWidget {
  const AutoControlScreen({super.key});

  @override
  State<AutoControlScreen> createState() => _AutoControlScreenState();
}

class _AutoControlScreenState extends State<AutoControlScreen> {
  int _selectedRoomIndex = 0;
  List<Room> rooms = [];
  List<Appliance> appliances = [];
  RoomService roomService = RoomService();
  ApplianceService applianceService = ApplianceService();
  final FlutterSecureStorage secureStorage = const FlutterSecureStorage();
  final SocketController socketController = Get.find<SocketController>();

  @override
  void initState() {
    super.initState();
    _loadRoomsAndAppliances();
  }

  void _loadRoomsAndAppliances() async {
    try {
      // 가정: RoomService와 ApplianceService는 싱글톤이거나 인스턴스화가 필요 없음
      List<Room> fetchedRooms = await roomService.getRooms();
      List<Appliance> fetchedAppliances =
          await applianceService.fetchAppliances();
      setState(() {
        rooms = fetchedRooms;
        appliances = fetchedAppliances;
      });
    } catch (e) {
      // 에러 처리: 실패 시 로그 찍기, 사용자에게 메시지 보여주기 등
      logger.e("Error fetching data: $e");
    }
  }

  @override
  Widget build(BuildContext context) {
    // 현재 선택된 방의 가전제품 목록
    List<Appliance> currentRoomAppliances = appliances
        .where(
            (appliance) => appliance.roomId == rooms[_selectedRoomIndex].roomId)
        .toList();
    const int itemsPerPage = 4;
    final int pageCount = (currentRoomAppliances.length / itemsPerPage).ceil();
    bool hasAppliances = currentRoomAppliances.isNotEmpty;

    return Column(
      crossAxisAlignment: CrossAxisAlignment.start,
      children: [
        Container(
          margin: const EdgeInsets.only(left: 30),
          width: 100,
          child: DropdownButton<int>(
            isExpanded: true,
            value: _selectedRoomIndex,
            items: rooms.map<DropdownMenuItem<int>>((Room room) {
              return DropdownMenuItem<int>(
                value: rooms.indexOf(room),
                child: Text(room.roomName),
              );
            }).toList(),
            onChanged: (int? newIndex) {
              if (newIndex != null) {
                setState(() {
                  _selectedRoomIndex = newIndex;
                });
              }
            },
          ),
        ),
        Expanded(
          child: hasAppliances
              ? PageView.builder(
                  itemCount: pageCount,
                  itemBuilder: (context, pageIndex) {
                    final int pageStartIndex = pageIndex * itemsPerPage;
                    final int pageEndIndex = min(pageStartIndex + itemsPerPage,
                        currentRoomAppliances.length);

                    return GridView.builder(
                      gridDelegate:
                          const SliverGridDelegateWithFixedCrossAxisCount(
                        crossAxisCount: 2, // 한 줄에 2개씩
                      ),
                      itemCount: pageEndIndex - pageStartIndex,
                      itemBuilder: (context, itemIndex) {
                        final appliance =
                            currentRoomAppliances[pageStartIndex + itemIndex];
                        return Padding(
                          padding: const EdgeInsets.all(8.0),
                          child: buildApplianceCard(appliance),
                        );
                      },
                    );
                  },
                )
              : const Center(
                  // 가전제품이 없을 때의 표시
                  child: SizedBox(
                    height: 500,
                    child: Center(
                      child: Text(
                        '등록된 가전이 없습니다.',
                        style: TextStyle(
                          fontSize: 18.0,
                          fontWeight: FontWeight.bold,
                          color: black,
                        ),
                      ),
                    ),
                  ),
                ),
        ),
      ],
    );
  }

  Widget buildApplianceCard(Appliance appliance) {
    return Card(
      color: appliance.applianceStatus == "ON" ? lightYellow : Colors.grey[100],
      child: Stack(
        children: [
          Center(
            child: FractionallySizedBox(
              widthFactor: 3 / 7,
              heightFactor: 3 / 7,
              child: Image.asset(appliance.imagePath, fit: BoxFit.contain),
            ),
          ),
          Positioned(
            bottom: 10,
            left: 0,
            right: 0,
            child: Text(
              appliance.applianceType,
              textAlign: TextAlign.center,
              style: const TextStyle(fontSize: 17, fontWeight: FontWeight.w600),
            ),
          ),
          Positioned(
            top: 10,
            right: 10,
            child: Switch(
              value: appliance.applianceStatus == "ON",
              onChanged: (bool newValue) async {
                final String? homeId = await secureStorage.read(key: "homeId");

                if (homeId != null) {
                  // 메시지 전송 로직
                  final String messageStatus = newValue ? "ON" : "OFF";
                  socketController.sendMessage(
                    destination: '/pub/control.message.$homeId',
                    type: 'IOT',
                    messageContent: '${appliance.applianceUUID}/$messageStatus',
                  );
                  String message = messageStatus == "ON" ? "켭" : "끕";
                  GlobalAlertDialog.show(
                    context,
                    title: "알림",
                    message:
                        "${appliance.roomName}-${appliance.applianceType}을(를) $message니다.",
                  );
                  // UI 상태 업데이트
                  setState(() {
                    appliance.applianceStatus = newValue ? "ON" : "OFF";
                  });
                } else {
                  logger.e("Home ID not found");
                }
              },
            ),
          ),
        ],
      ),
    );
  }
}
