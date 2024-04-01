import 'package:collection/collection.dart';
import 'package:flutter/material.dart';
import 'package:frontend/component/reserve/create_schedule_screen.dart';
import 'package:frontend/const/colors.dart';
import 'package:frontend/const/time_creator.dart';
import 'package:frontend/model/schedule.dart';
import 'package:frontend/model/room.dart';
import 'package:frontend/service/schedule_service.dart';
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
                    return Dismissible(
                      key: Key(schedule.hashCode.toString()), // 고유한 키로 각 항목을 식별
                      onDismissed: (direction) async {
                        final scheduleId = schedules[index].scheduleId;
                        final removedSchedule = schedules[index];
                        // 우선 스케줄을 목록에서 제거
                        setState(() {
                          schedules.removeAt(index);
                        });
                        // 서버에서 스케줄 삭제 시도
                        bool success =
                            await ScheduleService().deleteSchedule(scheduleId);
                        if (!success) {
                          // 삭제 실패 시 스케줄을 목록에 다시 추가
                          setState(() {
                            schedules.insert(index, removedSchedule);
                          });
                          // 실패 메시지와 함께 재시도 옵션 제공
                          ScaffoldMessenger.of(context).showSnackBar(
                            SnackBar(
                              content: const Text(
                                  "Failed to delete the schedule. Try again."),
                              action: SnackBarAction(
                                label: "RETRY",
                                onPressed: () async {
                                  // 재시도 로직: 사용자가 스낵바의 재시도를 탭했을 때 다시 시도
                                  bool retrySuccess = await ScheduleService()
                                      .deleteSchedule(scheduleId);
                                  if (retrySuccess) {
                                    setState(() {
                                      schedules.removeWhere((schedule) =>
                                          schedule.scheduleId == scheduleId);
                                    });
                                    ScaffoldMessenger.of(context).showSnackBar(
                                      const SnackBar(
                                          content: Text(
                                              "Schedule deleted successfully")),
                                    );
                                  } else {
                                    ScaffoldMessenger.of(context).showSnackBar(
                                      const SnackBar(
                                          content: Text(
                                              "Retry failed. Check your connection.")),
                                    );
                                  }
                                },
                              ),
                            ),
                          );
                        }
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
                          color: schedule.isActive
                              ? lightYellow
                              : Colors.grey[100],
                          borderRadius: BorderRadius.circular(10.0),
                        ),
                        child: Row(
                          mainAxisAlignment: MainAxisAlignment.spaceBetween,
                          children: [
                            Text(
                              schedule.time.format(context),
                              style: const TextStyle(fontSize: 16.0),
                            ),
                            Text(
                              schedule.appliance.roomName,
                              style: const TextStyle(fontSize: 16.0),
                            ),
                            Text(
                              schedule.appliance.applianceType,
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
                                    schedule.action.toUpperCase(),
                                    style: const TextStyle(
                                      color: black,
                                      fontWeight: FontWeight.bold,
                                    ),
                                  ),
                                ),
                              ),
                            ),
                            Switch(
                              value: schedule.isActive,
                              onChanged: (bool value) {
                                setState(() {
                                  schedule.isActive = value;
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
        onPressed: () {
          // CreateScheduleScreen으로 이동하고, 복귀했을 때 서버로부터 스케줄 리스트를 다시 불러옵니다.
          Navigator.push(
            context,
            MaterialPageRoute(
                builder: (context) => const CreateScheduleScreen()),
          ).then((_) {
            fetchSchedules();
            // 복귀 시 서버로부터 스케줄 리스트를 새로고침
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
        '후에\n${reservation.appliance.roomName}-${reservation.appliance.applianceType} 을(를) 동작시킵니다.';
    return message;
  }
}
