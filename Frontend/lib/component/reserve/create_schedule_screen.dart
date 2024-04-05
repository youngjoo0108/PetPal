import 'package:flutter/material.dart';
import 'package:frontend/const/colors.dart';
import 'package:frontend/const/global_alert_dialog.dart';
import 'package:frontend/const/time_creator.dart';
import 'package:frontend/model/appliance.dart';
import 'package:frontend/model/room.dart';
import 'package:frontend/service/appliance_service.dart';
import 'package:frontend/service/room_service.dart';
import 'package:frontend/service/schedule_service.dart';
import 'package:logger/logger.dart'; // 'Reservation' 클래스 경로

Logger logger = Logger();

class CreateScheduleScreen extends StatefulWidget {
  const CreateScheduleScreen({super.key});
  @override
  State<CreateScheduleScreen> createState() => _CreateReservationScreenState();
}

class _CreateReservationScreenState extends State<CreateScheduleScreen> {
  DateTime selectedDate = TimeCreator.nowInKorea();
  TimeOfDay selectedTime = TimeCreator.timeOfDayInKorea();
  Room? selectedRoom;
  Appliance? selectedAppliance;
  String? selectedAction;
  List<Room> rooms = [];
  List<Appliance> appliances = [];

  @override
  void initState() {
    super.initState();
    loadInitialData();
  }

  void loadInitialData() async {
    rooms = await RoomService().getRooms();
    appliances = await ApplianceService().fetchAppliances();
    setState(() {});
  }

  Future<void> _selectDate(BuildContext context) async {
    final DateTime? picked = await showDatePicker(
      context: context,
      initialDate: selectedDate,
      firstDate: TimeCreator.nowInKorea(), // 현재 날짜를 최소 날짜로 설정
      lastDate:
          TimeCreator.specificDateInKorea(2100, 12, 31), // 미래의 어떤 날짜를 최대 날짜로 설정
    );
    if (picked != null && picked != selectedDate) {
      setState(() {
        selectedDate = picked;
      });
    }
  }

  Future<void> _selectTime(BuildContext context) async {
    final TimeOfDay? picked = await showTimePicker(
      context: context,
      initialTime: selectedTime,
    );
    if (picked != null && picked != selectedTime) {
      setState(() {
        selectedTime = picked;
      });
    }
  }

  @override
  Widget build(BuildContext context) {
    List<Appliance> filteredAppliances = selectedRoom != null
        ? appliances
            .where((appliance) => appliance.roomId == selectedRoom!.roomId)
            .toList()
        : [];

    return Scaffold(
      appBar: AppBar(
        title: const Text('예약 생성'),
        backgroundColor: white,
      ),
      body: Container(
        color: white, // 배경색을 흰색으로 설정
        padding: const EdgeInsets.all(16.0),
        child: Column(
          crossAxisAlignment: CrossAxisAlignment.start,
          children: [
            buildDropdownButtonFormField<Room>(
              '방 선택',
              selectedRoom,
              rooms,
              (Room? value) {
                setState(() {
                  selectedRoom = value;
                  selectedAppliance = null; // 방을 변경하면 가전 선택을 초기화
                });
              },
              (Room room) => room.roomName,
            ),
            const SizedBox(height: 20), // 요소 사이의 간격
            // 가전 선택
            if (selectedRoom != null)
              buildDropdownButtonFormField<Appliance>(
                '가전 선택',
                selectedAppliance,
                filteredAppliances,
                (Appliance? value) {
                  setState(() {
                    selectedAppliance = value;
                  });
                },
                (Appliance appliance) => appliance.applianceType,
              ),
            const SizedBox(height: 20), // 요소 사이의 간격
            if (selectedRoom != null && selectedAppliance != null)
              buildDropdownButtonFormField<String>(
                '동작 선택',
                selectedAction,
                ['on', 'off'], // 동작 선택 옵션
                (String? value) {
                  setState(() {
                    selectedAction = value;
                  });
                },
                (String action) =>
                    action.toUpperCase(), // 'on' 또는 'off'를 대문자로 표시
              ),
            const SizedBox(height: 20), // 요소 사이의 간격
            buildDateTimePicker(
                '날짜 선택',
                '${selectedDate.toLocal()}'.split(' ')[0],
                () => _selectDate(context)),
            const SizedBox(height: 20), // 요소 사이의 간격
            buildDateTimePicker('시간 선택', selectedTime.format(context),
                () => _selectTime(context)),
            const Spacer(), // 나머지 공간을 모두 채움
            Align(
              alignment: Alignment.bottomRight,
              child: ElevatedButton(
                onPressed: createReservation,
                child: const Text('저장'),
              ),
            ),
          ],
        ),
      ),
    );
  }

  DropdownButtonFormField<T> buildDropdownButtonFormField<T>(
      String label,
      T? selectedValue,
      List<T> items,
      ValueChanged<T?> onChanged,
      String Function(T) itemToString) {
    // 아이템을 문자열로 변환하는 함수 추가
    return DropdownButtonFormField<T>(
      decoration: InputDecoration(
        labelText: label,
        border: const OutlineInputBorder(),
        filled: true,
        fillColor: Colors.grey[200],
      ),
      value: selectedValue,
      onChanged: onChanged,
      items: items.map<DropdownMenuItem<T>>((T value) {
        return DropdownMenuItem<T>(
          value: value,
          child: Text(itemToString(value)), // 아이템을 문자열로 변환
        );
      }).toList(),
    );
  }

  Row buildDateTimePicker(String label, String value, VoidCallback onTap) {
    return Row(
      mainAxisAlignment: MainAxisAlignment.spaceBetween,
      children: [
        Expanded(
            child: Text(label, style: Theme.of(context).textTheme.titleMedium)),
        Expanded(
          child: TextButton(
            onPressed: onTap,
            child: Text(value),
          ),
        ),
      ],
    );
  }

  void createReservation() async {
    logger.e(
        "(${selectedAppliance!.applianceId})-($selectedDate)-($selectedTime)-($selectedAction)");
    if (selectedRoom == null ||
        selectedAppliance == null ||
        selectedAction == null) {
      GlobalAlertDialog.show(context, message: '모든 정보를 선택해주세요.');
      return;
    }

    // 서버로 예약 데이터 전송
    bool success = await ScheduleService().addSchedule(
      appliance: selectedAppliance!,
      date: selectedDate,
      time: selectedTime,
      taskType: selectedAction!,
    );

    if (success) {
      // 성공적으로 데이터를 전송했을 경우, 이전 화면으로 돌아감
      Navigator.pop(context, true);
    } else {
      // 서버로부터 실패 응답을 받았을 경우, 사용자에게 알림
      GlobalAlertDialog.show(context, message: '예약 생성에 실패했습니다.');
    }
  }
}
