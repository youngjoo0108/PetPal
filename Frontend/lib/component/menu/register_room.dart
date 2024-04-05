import 'package:flutter/material.dart';
import 'package:frontend/const/global_alert_dialog.dart';
import 'package:frontend/service/room_service.dart'; // RoomService import

class RegisterRoom extends StatefulWidget {
  const RegisterRoom({super.key});

  @override
  _RegisterRoomScreenState createState() => _RegisterRoomScreenState();
}

class _RegisterRoomScreenState extends State<RegisterRoom> {
  RoomService roomService = RoomService();
  List<String> availableRooms = [];

  @override
  void initState() {
    super.initState();
    _loadAvailableRooms();
  }

  void _loadAvailableRooms() async {
    // RoomService를 통해 서버로부터 등록 가능한 방 목록을 불러오는 로직
    List<String> fetchedRooms = await roomService.getAvailableRooms();
    setState(() {
      availableRooms = fetchedRooms;
    });
  }

  void _tryRegisterRoom(String roomName) async {
    int result = await roomService.registerRoom(context, roomName);
    if (result == 1) {
      GlobalAlertDialog.show(
        context,
        title: "성공",
        message: "방 등록에 성공했습니다.",
      ).then((_) {
        Navigator.pop(context, true); // 성공적으로 방 등록 후 true를 반환하며 이전 페이지로 돌아감
      });
    } else if (result == 2) {
      GlobalAlertDialog.show(
        context,
        title: "이미 등록된 방입니다.",
        message: "다시 시도해 주세요.",
      );
    } else {
      GlobalAlertDialog.show(
        context,
        title: "실패",
        message: "방 등록에 실패했습니다.",
      );
    }
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(title: const Text("방 등록")),
      body: ListView.builder(
        itemCount: availableRooms.length,
        itemBuilder: (context, index) {
          String roomName = availableRooms[index];
          return ListTile(
            title: Text(roomName),
            onTap: () => _tryRegisterRoom(roomName), // 탭 시 방 등록 로직 호출
          );
        },
      ),
    );
  }
}
