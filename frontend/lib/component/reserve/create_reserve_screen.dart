import 'package:flutter/material.dart';
import 'package:frontend/const/colors.dart';
import 'package:frontend/model/appliance.dart';
import 'package:frontend/model/room.dart';
import 'package:frontend/model/reservation.dart'; // 'Reservation' 클래스 경로

class CreateReservationScreen extends StatefulWidget {
  final List<Room> rooms;

  const CreateReservationScreen({super.key, required this.rooms});

  @override
  State<CreateReservationScreen> createState() =>
      _CreateReservationScreenState();
}

class _CreateReservationScreenState extends State<CreateReservationScreen> {
  DateTime selectedDate = DateTime.now();
  TimeOfDay selectedTime = TimeOfDay.now();
  Room? selectedRoom;
  Appliance? selectedAppliance;

  Future<void> _selectDate(BuildContext context) async {
    final DateTime? picked = await showDatePicker(
      context: context,
      initialDate: selectedDate,
      firstDate: DateTime.now(), // 현재 날짜를 최소 날짜로 설정
      lastDate: DateTime(2100), // 미래의 어떤 날짜를 최대 날짜로 설정
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
            // 방 선택
            buildDropdownButtonFormField<Room>(
              '방 선택',
              selectedRoom,
              widget.rooms,
              (Room? value) {
                setState(() {
                  selectedRoom = value;
                  selectedAppliance = null;
                });
              },
              (Room room) => room.name, // Room 객체의 name 속성을 문자열로 사용
            ),
            const SizedBox(height: 20), // 요소 사이의 간격
            // 가전 선택
            if (selectedRoom != null)
              buildDropdownButtonFormField<Appliance>(
                '가전 선택',
                selectedAppliance,
                selectedRoom!.appliances,
                (Appliance? value) {
                  setState(() {
                    selectedAppliance = value;
                  });
                },
                (Appliance appliance) =>
                    appliance.name, // Appliance 객체의 name 속성을 문자열로 사용
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

  void createReservation() {
    if (selectedRoom != null && selectedAppliance != null) {
      final Reservation newReservation = Reservation(
        room: selectedRoom!,
        appliance: selectedAppliance!,
        date: selectedDate,
        time: selectedTime,
        isActive: true,
      );

      /*
        ---------------------서버에 전달하는 로직 추가---------------------
       */
      Navigator.pop(context, newReservation); // 이전 화면으로 예약 정보 반환
    } else {
      // 방이나 가전이 선택되지 않았을 경우 사용자에게 알림
      showDialog(
        context: context,
        builder: (BuildContext context) {
          return AlertDialog(
            title: const Text('돌아가'),
            content: const Text('방과 가전을 모두 선택해주세요.'),
            actions: <Widget>[
              TextButton(
                child: const Text('확인'),
                onPressed: () {
                  Navigator.of(context).pop();
                },
              ),
            ],
          );
        },
      );
    }
  }
}
