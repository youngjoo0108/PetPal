import 'package:flutter/material.dart';
import 'package:frontend/screen/control_screen.dart';
import 'package:frontend/screen/home_screen.dart';
import 'package:frontend/const/tabs.dart';
import 'package:frontend/const/colors.dart';
import 'package:frontend/screen/menu_screen.dart';
// import 'package:frontend/screen/mode_screen.dart';
import 'package:frontend/screen/noti_screen.dart';

class MainScreen extends StatefulWidget {
  const MainScreen({super.key});

  @override
  State<MainScreen> createState() => _MainScreenState();
}

class _MainScreenState extends State<MainScreen> with TickerProviderStateMixin {
  late final TabController controller;

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
        elevation: 0.5,
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
              const Column(
                children: [
                  Text(
                    'O O O 님의 집',
                    style: TextStyle(
                      fontWeight: FontWeight.w800,
                      fontSize: 20,
                      color: black,
                    ),
                  )
                ],
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
          HomeScreen(),
          ControlScreen(),
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
