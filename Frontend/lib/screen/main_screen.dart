import 'package:flutter/material.dart';
import 'package:flutter_secure_storage/flutter_secure_storage.dart';
import 'package:frontend/screen/control_screen.dart';
import 'package:frontend/screen/home_screen.dart';
import 'package:frontend/const/tabs.dart';
import 'package:frontend/const/colors.dart';
import 'package:frontend/screen/menu_screen.dart';
// import 'package:frontend/screen/mode_screen.dart';
import 'package:frontend/screen/noti_screen.dart';
import 'package:frontend/screen/schedule_screen.dart';

class MainScreen extends StatefulWidget {
  const MainScreen({super.key});

  @override
  State<MainScreen> createState() => _MainScreenState();
}

class _MainScreenState extends State<MainScreen> with TickerProviderStateMixin {
  late final TabController controller;
  FlutterSecureStorage secureStorage = const FlutterSecureStorage();

  @override
  void initState() {
    super.initState();

    controller = TabController(
      length: tabs.length,
      vsync: this,
    );

    controller.addListener(() {
      setState(() {});
    });
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      backgroundColor: white,
      appBar: AppBar(
        // elevation: 0.5,
        backgroundColor: lightYellow,
        title: Padding(
          padding: const EdgeInsets.symmetric(vertical: 0),
          child: Row(
            mainAxisAlignment: MainAxisAlignment.spaceBetween,
            // crossAxisAlignment: CrossAxisAlignment.stretch,
            children: [
              Column(
                children: [
                  SizedBox(
                    height: 45,
                    child: Image.asset('asset/img/logo.png'),
                  )
                ],
              ),
              FutureBuilder<List<String?>>(
                future: Future.wait([
                  secureStorage.read(key: 'nickname'), // 닉네임 불러오기
                  secureStorage.read(key: 'profileUrl'), // 프로필 이미지 URL 불러오기
                ]),
                builder: (BuildContext context,
                    AsyncSnapshot<List<String?>> snapshot) {
                  if (snapshot.connectionState == ConnectionState.done &&
                      snapshot.hasData) {
                    // 데이터 로드 완료
                    String? nickname = snapshot.data![0];
                    String? profileUrl = snapshot.data![1];

                    return Row(
                      children: [
                        if (profileUrl != null)
                          CircleAvatar(
                            backgroundImage: NetworkImage(profileUrl),
                            radius: 20.0, // 원하는 크기로 조절
                          ),
                        const SizedBox(width: 10), // 이미지와 텍스트 사이 간격
                        Text(
                          '${nickname ?? ""} 님의 집',
                          style: const TextStyle(
                            fontWeight: FontWeight.w800,
                            fontSize: 20,
                            color: black,
                          ),
                        ),
                      ],
                    );
                  } else if (snapshot.connectionState ==
                      ConnectionState.waiting) {
                    // 데이터 로딩 중
                    return const CircularProgressIndicator(); // 로딩 인디케이터 표시, 원하는 다른 위젯으로 대체 가능
                  } else {
                    // 데이터 로드 실패 또는 nickname, profileUrl 둘 다 없는 경우
                    return const Text(
                      '님의 집',
                      style: TextStyle(
                        fontWeight: FontWeight.w800,
                        fontSize: 20,
                        color: black,
                      ),
                    );
                  }
                },
              ),
            ],
          ),
        ),
      ),
      body: TabBarView(
        physics: const NeverScrollableScrollPhysics(),
        controller: controller,
        children: const [
          HomeScreen(),
          ControlScreen(),
          ScheduleScreen(),
          NotiScreen(),
          MenuScreen(),
        ],
      ),
      bottomNavigationBar: BottomNavigationBar(
        backgroundColor: white,
        selectedItemColor: blue,
        unselectedItemColor: black,
        showSelectedLabels: true,
        showUnselectedLabels: true,
        currentIndex: controller.index,
        type: BottomNavigationBarType.fixed,
        onTap: (index) {
          controller.animateTo(index);
        },
        items: tabs
            .map(
              (e) =>
                  BottomNavigationBarItem(icon: Icon(e.icon), label: e.label),
            )
            .toList(),
      ),
    );
  }
}
