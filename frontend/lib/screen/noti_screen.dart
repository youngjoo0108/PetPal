import 'package:flutter/material.dart';
import 'package:frontend/const/colors.dart';
import 'package:frontend/const/global_alert_dialog.dart';
import 'package:frontend/model/notification.dart';
import 'package:frontend/service/noti_service.dart';
import 'package:intl/intl.dart'; // intl 패키지 임포트

class NotiScreen extends StatefulWidget {
  const NotiScreen({super.key});

  @override
  NotiScreenState createState() => NotiScreenState();
}

class NotiScreenState extends State<NotiScreen> {
  String? displayImageUrl;
  List<Noti> notifications = [];

  @override
  void initState() {
    super.initState();
    fetchNotifications();
  }

  void fetchNotifications() async {
    // 임시로 사용자 ID를 1로 설정, 실제 앱에서는 동적으로 설정할 필요가 있음
    final fetchedNotifications =
        await NotificationService().fetchNotifications();
    setState(() {
      notifications.addAll(fetchedNotifications);
    });
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      body: Container(
        color: white, // 전체 배경색 설정
        padding: const EdgeInsets.only(top: 12), // 상단 padding 추가
        child: Container(
          padding: const EdgeInsets.all(15), // 전체적인 마진 설정
          decoration: BoxDecoration(
            color: Colors.white, // 배경색 설정
            boxShadow: [
              BoxShadow(
                color: Colors.grey.withOpacity(0.5),
                spreadRadius: 3,
                blurRadius: 4,
                offset: const Offset(0, 3), // 그림자 위치 조정
              ),
            ],
            borderRadius: const BorderRadius.only(
              topLeft: Radius.circular(20.0),
              topRight: Radius.circular(20.0),
            ), // 모서리 둥글게
          ),
          child: Column(
            children: [
              if (displayImageUrl != null)
                Container(
                  height: 240,
                  width: 320,
                  decoration: BoxDecoration(
                    image: DecorationImage(
                      image: NetworkImage(displayImageUrl!),
                      fit: BoxFit.cover,
                    ),
                    borderRadius: BorderRadius.circular(12), // 이미지 테두리 둥글게
                  ),
                  margin: const EdgeInsets.only(top: 20, bottom: 20),
                ),
              Expanded(
                child: ListView.builder(
                  itemCount: notifications.length,
                  itemBuilder: (context, index) {
                    final notification = notifications[index];
                    // 변환된 시간 문자열을 DateTime 객체로 파싱
                    final dateTime =
                        DateTime.parse(convertToIso8601(notification.time));
                    // DateFormat을 사용해 원하는 형식의 문자열로 변환
                    final formattedTime =
                        DateFormat('MM월 dd일 HH:mm').format(dateTime);

                    return Dismissible(
                      key: Key(notification.hashCode
                          .toString()), // 알림을 구별할 수 있는 고유 키
                      onDismissed: (direction) async {
                        final notificationId = notifications[index].id;
                        bool success = await NotificationService()
                            .deleteNotification(notificationId);
                        if (!success) {
                          // 삭제 실패 시 GlobalAlertDialog로 실패 알림
                          GlobalAlertDialog.show(
                            context,
                            title: "서버 에러",
                            message: "알림 삭제에 실패했습니다.",
                          );
                          // 실패한 스케줄을 다시 리스트에 추가 (UI 업데이트)
                          setState(() {
                            notifications.insert(index, notification);
                          });
                        } else {
                          // 삭제 성공 시 스케줄 리스트에서 해당 스케줄 제거
                          setState(() {
                            displayImageUrl = "";
                            fetchNotifications();
                          });
                          GlobalAlertDialog.show(
                            context,
                            title: "알림",
                            message: "알림을 삭제했습니다.",
                          );
                        }
                      },
                      background: Container(
                        color: white, // 스와이프 시 보여줄 배경 색상
                        alignment: Alignment.centerRight,
                        child: const Padding(
                          padding: EdgeInsets.only(right: 20.0),
                          child: Icon(Icons.delete, color: Colors.white),
                        ),
                      ),
                      child: GestureDetector(
                        onTap: () {
                          setState(() {
                            displayImageUrl = notification.imageUrl;
                          });
                        },
                        child: Container(
                          padding: const EdgeInsets.all(10),
                          margin: const EdgeInsets.symmetric(vertical: 5),
                          decoration: BoxDecoration(
                            color: lightYellow,
                            borderRadius: BorderRadius.circular(10),
                            boxShadow: [
                              BoxShadow(
                                color: Colors.grey.withOpacity(0.5),
                                spreadRadius: 1,
                                blurRadius: 3,
                                offset: const Offset(0, 2),
                              ),
                            ],
                          ),
                          child: Row(
                            mainAxisAlignment: MainAxisAlignment.spaceEvenly,
                            children: [
                              Expanded(child: Text(notification.category)),
                              Expanded(child: Text(notification.content)),
                              Expanded(child: Text(formattedTime)),
                            ],
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
    );
  }

  String convertToIso8601(String timeString) {
    // '2024-04-01-10:31:31' 혹은 '2024-04-01T10:31:31' 형식의 입력을 처리
    String iso8601String;
    if (timeString.contains('T')) {
      // 이미 ISO 8601 형식이면 그대로 반환
      iso8601String = timeString;
    } else {
      // '-'를 사용하여 날짜와 시간이 구분된 경우
      var parts = timeString.split('-');
      if (parts.length != 6) {
        throw FormatException(
            "Invalid time format, expected 6 parts but got ${parts.length}");
      }
      // 날짜 부분(년, 월, 일)과 시간 부분(시, 분, 초)을 'T'로 연결
      iso8601String =
          '${parts[0]}-${parts[1]}-${parts[2]}T${parts[3]}:${parts[4]}:${parts[5]}';
    }
    return iso8601String;
  }
}
