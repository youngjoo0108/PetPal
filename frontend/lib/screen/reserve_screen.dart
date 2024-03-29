import 'package:collection/collection.dart';
import 'package:flutter/material.dart';
import 'package:frontend/component/reserve/create_reserve_screen.dart';
import 'package:frontend/const/colors.dart';
import 'package:frontend/const/time_creator.dart';
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
  @override
  void initState() {
    /*
    --------------DB에서 예약 가져오는 로직 추가
     */
    super.initState();
  }

  // 방과 가전의 예시 데이터
  final List<Room> rooms = [
    // Room(
    //   name: '거실',
    //   appliances: [
    //     Appliance(name: '전등', imagePath: 'asset/img/light.png'),
    //     Appliance(name: '커튼', imagePath: 'asset/img/curtains.png'),
    //     Appliance(name: 'TV', imagePath: 'asset/img/tv.png'),
    //     Appliance(name: '에어컨', imagePath: 'asset/img/airConditioner.png'),
    //     Appliance(name: '공기청정기', imagePath: 'asset/img/purifier.png'),
    //   ],
    // ),
    // Room(
    //   name: '주방',
    //   appliances: [
    //     Appliance(name: '전등', imagePath: 'asset/img/light.png'),
    //     Appliance(name: '커튼', imagePath: 'asset/img/curtains.png'),
    //     Appliance(name: '세탁기', imagePath: 'asset/img/washingMachine.png'),
    //   ],
    // ),
    // Room(
    //   name: '침실',
    //   appliances: [
    //     Appliance(name: '전등', imagePath: 'asset/img/light.png'),
    //     Appliance(name: '커튼', imagePath: 'asset/img/curtains.png'),
    //     Appliance(name: 'TV', imagePath: 'asset/img/tv.png'),
    //     Appliance(name: '에어컨', imagePath: 'asset/img/airConditioner.png'),
    //     Appliance(name: '공기청정기', imagePath: 'asset/img/purifier.png'),
    //   ],
    // ),
  ];

  @override
  Widget build(BuildContext context) {
    // isActive가 true인 예약 중 첫 번째 예약 찾기
    Reservation? activeReservation = reservations.firstWhereOrNull(
      (reservation) => reservation.isActive,
    );

    // 예약이 있고, isActive가 true인 경우에 대한 문구 생성
    String message = reservations.isEmpty
        ? '설정된 예약이\n 없습니다.'
        : activeReservation != null
            ? getTimeDifferenceMessage(activeReservation)
            : '활성화된 예약이\n 없습니다.';

    return Scaffold(
      body: Container(
        color: white, // 전체 배경색 설정
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
          child: Column(
            mainAxisSize: MainAxisSize.min,
            children: <Widget>[
              Padding(
                padding: const EdgeInsets.all(60.0),
                child: Text(
                  message,
                  style: const TextStyle(fontSize: 25),
                ),
              ),
              Flexible(
                fit: FlexFit.loose,
                child: ListView.builder(
                  padding: const EdgeInsets.only(top: 10),
                  itemCount: reservations.length,
                  itemBuilder: (context, index) {
                    final reservation = reservations[index];
                    return Dismissible(
                      key: Key(
                          reservation.hashCode.toString()), // 고유한 키로 각 항목을 식별
                      onDismissed: (direction) {
                        // 항목 삭제
                        setState(() {
                          /*
                          ---------------------- 서버와 통신하는 로직 추가
                           */
                          reservations.removeAt(index);
                        });
                      },
                      background: Container(
                        alignment: Alignment.centerRight,
                        color: white,
                        child: const Icon(Icons.delete, color: Colors.white),
                      ),
                      child: Container(
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
                            SizedBox(
                              width: 60,
                              height: 30,
                              child: DecoratedBox(
                                decoration: BoxDecoration(
                                  color: deepYellow,
                                  borderRadius: BorderRadius.circular(10),
                                ),
                                child: Center(
                                  child: Text(
                                    reservation.action.toUpperCase(),
                                    style: const TextStyle(
                                      color: black,
                                      fontWeight: FontWeight.bold,
                                    ),
                                  ),
                                ),
                              ),
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
                      ),
                    );
                  },
                ),
              ),
            ],
          ),
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

  String getTimeDifferenceMessage(Reservation reservation) {
    DateTime now = TimeCreator.nowInKorea();
    DateTime reservationDateTime = DateTime(
      reservation.date.year,
      reservation.date.month,
      reservation.date.day,
      reservation.time.hour,
      reservation.time.minute,
    );
    Duration difference = reservationDateTime.difference(now);

    String message = '';
    if (difference.inDays > 0) {
      message += '${difference.inDays}일 ';
    }
    int hours = difference.inHours % 24;
    if (hours > 0) {
      message += '$hours시간 ';
    }
    int minutes = difference.inMinutes % 60;
    if (minutes > 0) {
      message += '$minutes분 ';
    }

    if (message.isEmpty) {
      message = '바로 ';
    }

    message +=
        '후에\n${reservation.room.name}-${reservation.appliance.name} 을(를) 동작시킵니다.';
    return message;
  }
}
