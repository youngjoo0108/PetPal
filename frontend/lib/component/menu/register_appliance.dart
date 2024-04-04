import 'package:flutter/material.dart';
import 'package:frontend/const/colors.dart';
import 'package:frontend/const/global_alert_dialog.dart';
import 'package:frontend/service/room_service.dart';
import 'package:frontend/service/appliance_service.dart';
import 'package:frontend/model/room.dart';

class RegisterAppliance extends StatefulWidget {
  final String applianceUUID;
  const RegisterAppliance({super.key, required this.applianceUUID});

  @override
  RegisterApplianceState createState() => RegisterApplianceState();
}

class RegisterApplianceState extends State<RegisterAppliance> {
  final RoomService _roomService = RoomService();
  final ApplianceService _applianceService = ApplianceService();

  List<Room> rooms = [];
  List<String> appliances = [];
  Room? selectedRoom;
  String? selectedAppliance;

  @override
  void initState() {
    super.initState();
    _loadRooms();
    _loadAppliances();
  }

  _loadRooms() async {
    final roomList = await _roomService.getRooms();
    setState(() {
      rooms = roomList;
    });
  }

  _loadAppliances() async {
    final applianceList = await _applianceService.fetchAvailableAppliances();
    setState(() {
      appliances = applianceList;
    });
  }

  registerAppliance() async {
    if (selectedRoom == null || selectedAppliance == null) {
      // GlobalAlertDialog 사용하여 메시지 표시
      GlobalAlertDialog.show(context,
          message: 'Please select both a room and an appliance');
      return;
    }
    int result = await _applianceService.registerAppliance(
        selectedRoom!.roomId, selectedAppliance!, widget.applianceUUID);
    if (result == 1) {
      GlobalAlertDialog.show(
        context,
        title: "성공",
        message: "가전 등록에 성공했습니다.",
      ).then((_) {
        Navigator.pop(context, true); // 성공적으로 방 등록 후 true를 반환하며 이전 페이지로 돌아감
      });
    } else if (result == 2) {
      GlobalAlertDialog.show(
        context,
        title: "이미 등록된 가전입니다.",
        message: "다시 시도해 주세요.",
      );
    } else {
      GlobalAlertDialog.show(
        context,
        title: "실패",
        message: "가전 등록에 실패했습니다.",
      );
    }
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: const Text('가전 등록'),
      ),
      body: Padding(
        padding: const EdgeInsets.all(16.0),
        child: Column(
          crossAxisAlignment: CrossAxisAlignment.start,
          children: <Widget>[
            Row(
              mainAxisAlignment: MainAxisAlignment.spaceBetween,
              children: [
                const Expanded(
                    child: Text('방', style: TextStyle(fontSize: 16))),
                Expanded(
                  child: DropdownButton<Room>(
                    hint: const Text("방 선택"),
                    value: selectedRoom,
                    onChanged: (Room? newValue) {
                      setState(() {
                        selectedRoom = newValue;
                      });
                    },
                    items: rooms.map((Room room) {
                      return DropdownMenuItem<Room>(
                        value: room,
                        child: Text(room.roomName),
                      );
                    }).toList(),
                  ),
                ),
              ],
            ),
            const SizedBox(height: 20),
            Row(
              mainAxisAlignment: MainAxisAlignment.spaceBetween,
              children: [
                const Expanded(
                    child: Text('가전', style: TextStyle(fontSize: 16))),
                Expanded(
                  child: DropdownButton<String>(
                    hint: const Text("가전 선택"),
                    value: selectedAppliance,
                    onChanged: (String? newValue) {
                      setState(() {
                        selectedAppliance = newValue;
                      });
                    },
                    items: appliances.map((String applianceType) {
                      return DropdownMenuItem<String>(
                        value: applianceType,
                        child: Text(applianceType),
                      );
                    }).toList(),
                  ),
                ),
              ],
            ),
          ],
        ),
      ),
      floatingActionButtonLocation: FloatingActionButtonLocation.endFloat,
      floatingActionButton: ElevatedButton(
        onPressed: registerAppliance,
        style: ElevatedButton.styleFrom(
          foregroundColor: black,
          backgroundColor: lightYellow, // 버튼 텍스트 색상
        ),
        child: const Text('등록하기'),
      ),
    );
  }
}
