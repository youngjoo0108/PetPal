import 'package:flutter/material.dart';
// import 'package:frontend/const/colors.dart';
import 'package:frontend/model/appliance.dart';
import 'package:frontend/model/room.dart';
import 'package:frontend/service/appliance_service.dart';
import 'package:frontend/service/room_service.dart';
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

    return Column(
      crossAxisAlignment: CrossAxisAlignment.start,
      children: [
        Container(
          margin: const EdgeInsets.only(left: 30),
          width: 60,
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
          child: PageView.builder(
            itemCount: currentRoomAppliances.length,
            itemBuilder: (context, pageIndex) {
              return GridView.builder(
                gridDelegate: const SliverGridDelegateWithFixedCrossAxisCount(
                  crossAxisCount: 2, // 한 줄에 2개씩
                ),
                itemCount: 1,
                itemBuilder: (context, itemIndex) {
                  final appliance = currentRoomAppliances[pageIndex];
                  return Padding(
                    padding: const EdgeInsets.all(8.0),
                    child: Card(
                      color: appliance.applianceStatus == 1
                          ? Colors.lightGreenAccent
                          : Colors.grey[100],
                      child: Stack(
                        children: [
                          Center(
                            child: FractionallySizedBox(
                              widthFactor: 3 / 7, // 카드 너비의 약 2/3만큼 차지
                              heightFactor: 3 / 7, // 카드 높이의 약 2/3만큼 차지
                              child: Image.asset(appliance.imagePath,
                                  fit: BoxFit.contain),
                            ),
                          ),
                          Positioned(
                            bottom: 10,
                            left: 0,
                            right: 0,
                            child: Text(
                              appliance.applianceType,
                              textAlign: TextAlign.center,
                              style: const TextStyle(
                                fontSize: 17,
                                fontWeight: FontWeight.w600,
                              ),
                            ),
                          ),
                          Positioned(
                            top: 10,
                            right: 10,
                            child: Switch(
                              value: appliance.applianceStatus == 1,
                              onChanged: (bool newValue) {
                                setState(() {
                                  appliance.applianceStatus = newValue ? 1 : 0;
                                });
                              },
                            ),
                          ),
                        ],
                      ),
                    ),
                  );
                },
              );
            },
          ),
        ),
      ],
    );
  }
}
