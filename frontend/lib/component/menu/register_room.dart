import 'package:flutter/material.dart';
import 'package:frontend/model/room.dart'; // Room 모델 import
import 'package:frontend/service/room_service.dart'; // RoomService import

class RegisterRoom extends StatefulWidget {
  const RegisterRoom({super.key});

  @override
  _RegisterRoomScreenState createState() => _RegisterRoomScreenState();
}

class _RegisterRoomScreenState extends State<RegisterRoom> {
  List<Room> availableRooms = [];

  @override
  void initState() {
    super.initState();
    _loadAvailableRooms();
  }

  void _loadAvailableRooms() async {
    // RoomService를 통해 서버로부터 등록 가능한 방 목록을 불러오는 로직
    List<Room> fetchedRooms = await RoomService.getAvailableRooms();
    setState(() {
      availableRooms = fetchedRooms;
    });
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(title: const Text("방 등록")),
      body: ListView.builder(
        itemCount: availableRooms.length,
        itemBuilder: (context, index) {
          Room room = availableRooms[index];
          return ListTile(
            title: Text(room.name),
            onTap: () {
              // 여기에서 방을 등록하는 로직을 추가하고, 성공적으로 등록되면 이전 화면으로 방 객체를 반환합니다.
              Navigator.pop(context, room);
            },
          );
        },
      ),
    );
  }
}
