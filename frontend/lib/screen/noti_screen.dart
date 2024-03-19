import 'package:flutter/material.dart';
import 'package:frontend/const/colors.dart';
import 'package:frontend/model/notification.dart';
import 'package:intl/intl.dart'; // intl 패키지 임포트

class NotiScreen extends StatefulWidget {
  const NotiScreen({super.key});

  @override
  NotiScreenState createState() => NotiScreenState();
}

class NotiScreenState extends State<NotiScreen> {
  String? displayImageUrl;

  final List<Noti> notifications = [
    Noti(
      category: 'Category 1',
      content: 'Content 1',
      timestamp: DateTime.now(),
      imageUrl: 'asset/img/windy.png',
    ),
    Noti(
      category: 'Category 2',
      content: 'Content 2',
      timestamp: DateTime.now(),
      imageUrl: 'asset/img/tv.png',
    ),
    // 더 많은 알림 추가 가능...
  ];

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
            borderRadius:
                const BorderRadius.all(Radius.circular(20.0)), // 모서리 둥글게
          ),
          child: Column(
            children: [
              if (displayImageUrl != null)
                Container(
                  height: 240,
                  width: 320,
                  decoration: BoxDecoration(
                    image: DecorationImage(
                      image: AssetImage(displayImageUrl!),
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
                    final formattedDate = DateFormat('MM월 dd일 HH:mm')
                        .format(notification.timestamp); // 날짜 형식 지정
                    return GestureDetector(
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
                            Expanded(child: Text(formattedDate)),
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
    );
  }
}
