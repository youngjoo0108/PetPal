import 'package:flutter/material.dart';
import 'package:frontend/const/secure_storage.dart';
import 'package:frontend/service/room_service.dart';
import 'package:frontend/service/appliance_service.dart';
import 'package:frontend/model/room.dart';
import 'package:frontend/model/appliance.dart';

class RegisterAppliance extends StatefulWidget {
  const RegisterAppliance({super.key});

  @override
  RegisterApplianceState createState() => RegisterApplianceState();
}

class RegisterApplianceState extends State<RegisterAppliance> {
  final RoomService _roomService = RoomService();
  final ApplianceService _applianceService = ApplianceService();
  final SecureStorage _secureStorage = SecureStorage();

  List<Room> rooms = [];
  List<Appliance> appliances = [];
  Room? selectedRoom;
  Appliance? selectedAppliance;

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
    final homeId = await _secureStorage.getHomeId('homeId');
    if (selectedRoom == null || selectedAppliance == null || homeId == null) {
      ScaffoldMessenger.of(context).showSnackBar(
        const SnackBar(
            content: Text('Please select both a room and an appliance')),
      );
      return;
    }

    try {
      await _applianceService.registerAppliance(
          homeId, selectedRoom!.roomId, selectedAppliance!.applianceType);
      // 성공적으로 등록되었을 경우의 처리, 예: 사용자에게 성공 메시지 표시
    } catch (e) {
      // 에러 처리, 예: 사용자에게 에러 메시지 표시
    }
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: const Text('Register Appliance'),
      ),
      body: Padding(
        padding: const EdgeInsets.all(16.0),
        child: Column(
          crossAxisAlignment: CrossAxisAlignment.start,
          children: <Widget>[
            const Text('Select a Room:', style: TextStyle(fontSize: 16)),
            DropdownButton<Room>(
              hint: const Text("Select room"),
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
            const SizedBox(height: 20),
            const Text('Select an Appliance:', style: TextStyle(fontSize: 16)),
            DropdownButton<Appliance>(
              hint: const Text("Select appliance"),
              value: selectedAppliance,
              onChanged: (Appliance? newValue) {
                setState(() {
                  selectedAppliance = newValue;
                });
              },
              items: appliances.map((Appliance appliance) {
                return DropdownMenuItem<Appliance>(
                  value: appliance,
                  child: Text(appliance.applianceType),
                );
              }).toList(),
            ),
            const SizedBox(height: 40),
            Center(
              child: ElevatedButton(
                onPressed: registerAppliance,
                child: const Text('Register'),
              ),
            ),
          ],
        ),
      ),
    );
  }
}
