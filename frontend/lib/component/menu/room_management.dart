import 'package:flutter/material.dart';
import 'package:frontend/model/room.dart'; // Room 모델 import
import 'package:frontend/service/room_service.dart'; // RoomService import
import 'register_room.dart'; // RegisterRoomScreen import

class RoomManagement extends StatefulWidget {
  const RoomManagement({super.key});

  @override
  State<RoomManagement> createState() => _RoomManagementScreenState();
}

class _RoomManagementScreenState extends State<RoomManagement> {
  RoomService roomService = RoomService();
  List<Room> rooms = [];

  @override
  void initState() {
    super.initState();
    _loadRooms();
  }

  void _loadRooms() async {
    // RoomService를 통해 서버로부터 방 정보를 불러오는 로직
    List<Room> fetchedRooms = await roomService.getRooms();
    setState(() {
      rooms = fetchedRooms;
    });
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(title: const Text("방 관리")),
      body: ListView.builder(
        itemCount: rooms.length,
        itemBuilder: (context, index) {
          Room room = rooms[index];
          return ListTile(
            title: Text(room.roomName),
            // 여기에 각 방에 대한 추가적인 정보를 표시할 수 있습니다.
          );
        },
      ),
      floatingActionButton: FloatingActionButton(
        onPressed: () async {
          final result = await Navigator.push(
            context,
            MaterialPageRoute(builder: (context) => const RegisterRoom()),
          );
          if (result == true) {
            // 방 등록 성공 시
            _loadRooms(); // 방 목록을 다시 불러옵니다.
          }
        },
        child: const Icon(Icons.add),
      ),
    );
  }
}
