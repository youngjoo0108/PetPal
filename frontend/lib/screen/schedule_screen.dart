import 'package:collection/collection.dart';
import 'package:flutter/material.dart';
import 'package:frontend/component/reserve/create_schedule_screen.dart';
import 'package:frontend/const/colors.dart';
import 'package:frontend/const/global_alert_dialog.dart';
import 'package:frontend/const/time_creator.dart';
import 'package:frontend/model/schedule.dart';
import 'package:frontend/model/room.dart';
import 'package:frontend/service/schedule_service.dart';
// import 'package:intl/intl.dart';
import 'package:logger/logger.dart';

final Logger logger = Logger();

class ScheduleScreen extends StatefulWidget {
  const ScheduleScreen({super.key});

  @override
  State<ScheduleScreen> createState() => _ScheduleScreenState();
}

class _ScheduleScreenState extends State<ScheduleScreen> {
  List<Schedule> schedules = [];
  @override
  void initState() {
    fetchSchedules();
    super.initState();
  }

  void fetchSchedules() async {
    try {
      schedules = await ScheduleService().fetchSchedules();
      setState(() {});
    } catch (e) {
      // 오류 처리
      logger.e(e);
    }
  }

  // 방과 가전의 예시 데이터
  final List<Room> rooms = [];

  @override
  Widget build(BuildContext context) {
    // isActive가 true인 예약 중 첫 번째 예약 찾기
    Schedule? activeReservation = schedules.firstWhereOrNull(
      (reservation) => reservation.isActive,
    );

    // 예약이 있고, isActive가 true인 경우에 대한 문구 생성
    String message = schedules.isEmpty
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
                  itemCount: schedules.length,
                  itemBuilder: (context, index) {
                    final schedule = schedules[index];
                    // 서버 응답에 따른 날짜 및 시간 포맷팅
                    // final formattedDay =
                    //     DateFormat('yyyy-MM-dd').format(schedule.day);
                    final formattedTime = schedule.time.format(context);
                    return Dismissible(
                      key: Key(schedule.hashCode.toString()), // 고유한 키로 각 항목을 식별
                      onDismissed: (direction) async {
                        final scheduleId = schedules[index].scheduleId;
                        // 서버에서 스케줄 삭제 시도
                        bool success =
                            await ScheduleService().deleteSchedule(scheduleId);
                        if (!success) {
                          // 삭제 실패 시 GlobalAlertDialog로 실패 알림
                          GlobalAlertDialog.show(
                            context,
                            title: "서버 에러",
                            message: "예약 삭제에 실패했습니다.",
                          );
                          // 실패한 스케줄을 다시 리스트에 추가 (UI 업데이트)
                          setState(() {
                            schedules.insert(index, schedule);
                          });
                        } else {
                          // 삭제 성공 시 스케줄 리스트에서 해당 스케줄 제거
                          setState(() {
                            schedules.removeAt(index);
                          });
                          GlobalAlertDialog.show(
                            context,
                            title: "알림",
                            message: "예약을 삭제했습니다.",
                          );
                        }
                      },
                      background: Container(
                        alignment: Alignment.centerRight,
                        padding: const EdgeInsets.symmetric(horizontal: 20.0),
                        color: white,
                        child: const Icon(Icons.delete_forever,
                            color: Colors.white),
                      ),
                      child: Container(
                        margin: const EdgeInsets.symmetric(
                            vertical: 4.0, horizontal: 8.0),
                        decoration: BoxDecoration(
                          color: schedule.isActive
                              ? lightYellow
                              : Colors.grey[200],
                          borderRadius: BorderRadius.circular(8.0),
                        ),
                        child: ListTile(
                          leading: const Icon(Icons.event_available,
                              color: Colors.black54),
                          title: Row(
                            mainAxisAlignment: MainAxisAlignment.spaceEvenly,
                            children: [
                              Text(
                                "${schedule.roomName} - ${schedule.applianceType}",
                                overflow: TextOverflow.ellipsis,
                              ),
                              Text(
                                formattedTime,
                                style: const TextStyle(color: Colors.black54),
                              ),
                              Text(
                                schedule.taskType.toUpperCase(),
                                style: const TextStyle(color: Colors.black54),
                              ),
                            ],
                          ),
                          trailing: Switch(
                            value: schedule.isActive,
                            onChanged: (bool value) {
                              setState(() {
                                schedule.isActive = value;
                                // 스케줄 활성/비활성화 상태 업데이트 로직 추가
                              });
                            },
                          ),
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
        onPressed: () {
          // CreateScheduleScreen으로 이동하고, 복귀했을 때 서버로부터 스케줄 리스트를 다시 불러옵니다.
          Navigator.push(
            context,
            MaterialPageRoute(
                builder: (context) => const CreateScheduleScreen()),
          ).then((result) {
            // 예약 생성 화면에서 true가 반환된 경우, 최신 예약 리스트를 불러옵니다.
            if (result == true) {
              fetchSchedules(); // 예약 리스트를 새로 불러오는 메서드
            }
          });
        },
        backgroundColor: lightYellow,
        child: const Icon(Icons.add, color: black), // '+' 아이콘만 표시
      ),
      floatingActionButtonLocation: FloatingActionButtonLocation.endFloat,
    );
  }

  String getTimeDifferenceMessage(Schedule reservation) {
    DateTime now = TimeCreator.nowInKorea();
    DateTime reservationDateTime = DateTime(
      reservation.day.year,
      reservation.day.month,
      reservation.day.day,
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
        '후에\n${reservation.roomName}-${reservation.applianceType} 을(를)\n 동작시킵니다.';
    return message;
  }
}
