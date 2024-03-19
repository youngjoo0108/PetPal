import 'package:flutter/material.dart';
import 'package:frontend/component/reserve/create_reserve_screen.dart';
import 'package:frontend/const/colors.dart';
import 'package:frontend/model/appliance.dart';
import 'package:frontend/model/reservation.dart';
import 'package:frontend/model/room.dart';

class ReserveScreen extends StatefulWidget {
  const ReserveScreen({super.key});

  @override
  State<ReserveScreen> createState() => _ReserveScreenState();
}

class _ReserveScreenState extends State<ReserveScreen> {
  // 예약 목록을 저장할 리스트
  List<Reservation> reservations = [];

  // 방과 가전의 예시 데이터
  final List<Room> rooms = [
    Room(
      name: '거실',
      appliances: [
        Appliance(name: '전등', imagePath: 'asset/img/light.png'),
        Appliance(name: '커튼', imagePath: 'asset/img/curtains.png'),
        Appliance(name: 'TV', imagePath: 'asset/img/tv.png'),
        Appliance(name: '에어컨', imagePath: 'asset/img/airConditioner.png'),
        Appliance(name: '공기청정기', imagePath: 'asset/img/purifier.png'),
      ],
    ),
    Room(
      name: '주방',
      appliances: [
        Appliance(name: '전등', imagePath: 'asset/img/light.png'),
        Appliance(name: '커튼', imagePath: 'asset/img/curtains.png'),
        Appliance(name: '세탁기', imagePath: 'asset/img/washingMachine.png'),
      ],
    ),
    Room(
      name: '침실',
      appliances: [
        Appliance(name: '전등', imagePath: 'asset/img/light.png'),
        Appliance(name: '커튼', imagePath: 'asset/img/curtains.png'),
        Appliance(name: 'TV', imagePath: 'asset/img/tv.png'),
        Appliance(name: '에어컨', imagePath: 'asset/img/airConditioner.png'),
        Appliance(name: '공기청정기', imagePath: 'asset/img/purifier.png'),
      ],
    ),
  ];

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      body: Container(
        color: white, // 전체 배경색 설정
        child: Column(
          children: [
            Expanded(
              child: Container(
                margin: const EdgeInsets.only(top: 12),
                decoration: BoxDecoration(
                  color: Colors.white,
                  boxShadow: [
                    BoxShadow(
                      color: Colors.grey.withOpacity(0.5),
                      spreadRadius: 3,
                      blurRadius: 4,
                      offset: const Offset(0, 3),
                    ),
                  ],
                  borderRadius: const BorderRadius.only(
                    topLeft: Radius.circular(20.0),
                    topRight: Radius.circular(20.0),
                  ),
                ),
                child: ListView.builder(
                  padding: const EdgeInsets.only(top: 10),
                  itemCount: reservations.length,
                  itemBuilder: (context, index) {
                    final reservation = reservations[index];
                    return Container(
                      margin: const EdgeInsets.all(12.0),
                      padding: const EdgeInsets.all(16.0),
                      decoration: BoxDecoration(
                        color: reservation.isActive
                            ? lightYellow
                            : Colors.grey[100],
                        borderRadius: BorderRadius.circular(10.0),
                      ),
                      child: Row(
                        mainAxisAlignment: MainAxisAlignment.spaceBetween,
                        children: [
                          Text(
                            reservation.time.format(context),
                            style: const TextStyle(fontSize: 16.0),
                          ),
                          Text(
                            reservation.room.name,
                            style: const TextStyle(fontSize: 16.0),
                          ),
                          Text(
                            reservation.appliance.name,
                            style: const TextStyle(fontSize: 16.0),
                          ),
                          Switch(
                            value: reservation.isActive,
                            onChanged: (bool value) {
                              setState(() {
                                reservation.isActive = value;
                              });
                            },
                          ),
                        ],
                      ),
                    );
                  },
                ),
              ),
            ),
          ],
        ),
      ),
      floatingActionButton: FloatingActionButton(
        onPressed: () async {
          final result = await Navigator.push(
            context,
            MaterialPageRoute(
                builder: (context) => CreateReservationScreen(rooms: rooms)),
          );
          if (result is Reservation) {
            setState(() {
              reservations.add(result);
            });
          }
        },
        backgroundColor: lightYellow,
        child: const Icon(Icons.add, color: black), // '+' 아이콘만 표시
      ),
      floatingActionButtonLocation: FloatingActionButtonLocation.endFloat,
    );
  }
}
