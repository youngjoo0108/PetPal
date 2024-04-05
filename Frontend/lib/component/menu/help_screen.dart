import 'package:flutter/material.dart';
import 'package:frontend/const/colors.dart';

class HelpScreen extends StatelessWidget {
  const HelpScreen({super.key});

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: const Text("도움말"),
        backgroundColor: lightYellow,
      ),
      body: Container(
        color: white, // 전체 배경색 설정
        child: Padding(
          padding: const EdgeInsets.all(20.0),
          child: ListView(
            children: const [
              Text(
                "소개",
                style: TextStyle(fontSize: 22, fontWeight: FontWeight.bold),
              ),
              SizedBox(height: 10),
              Text(
                "PETPAL은 우리 집 반려동물의 친구라는 컨셉의 서비스 어플리케이션입니다. PETPAL의 터틀봇은 반려동물을 트래킹하며 주변에 위험할 수 있는 물체를 자동으로 인식하여 처리하며, 위험할 수 있는 상황에 대해 사용자에게 알림을 보내 안전 사고를 예방합니다. PETPAL을 통해 반려 동물에게 좀더 안전하고 편안한 실내 환경을 만들어 주세요!",
                style: TextStyle(fontSize: 18),
              ),
              SizedBox(height: 20),
              Text(
                "사용법",
                style: TextStyle(fontSize: 22, fontWeight: FontWeight.bold),
              ),
              SizedBox(height: 15),
              Text(
                "🐢 기기 등록: 로그인 후 가장 먼저 해야할 일은 [기기 등록]입니다. 기기의 ID를 직접 입력하거나 기기의 QR코드를 활용하여 기기를 등록해주세요.",
                style: TextStyle(fontSize: 18),
              ),
              SizedBox(height: 15),
              Text(
                "🏡 홈 스캔: [기기 등록]이 끝났다면, [홈 스캔]을 수행해야합니다. 집 안에 터틀봇을 위치시키고 [앱-메뉴-홈 스캔] 버튼을 누르면 [홈 스캔]이 자동으로 시작됩니다. [홈 스캔]이 끝나면 알림이 제공됩니다.",
                style: TextStyle(fontSize: 18),
              ),
              SizedBox(height: 15),
              Text(
                "🚪 방 관리: [앱-메뉴-방 관리] 버튼을 눌러 [방 관리 페이지]로 이동할 수 있습니다. 해당 페이지에서는 집 안에 있는 방을 사용자가 직접 등록합니다.",
                style: TextStyle(fontSize: 18),
              ),
              SizedBox(height: 15),
              Text(
                "📺 가전 관리: [앱-메뉴-가전 관리] 버튼을 눌러 [가전 관리 페이지]로 이동할 수 있습니다. 터틀봇을 가전 주위에 위치시키고, [+ 아이콘]을 눌러 IOT 기기를 등록합니다. 기기가 등록된 후에는 사용자가 직접 어떤 방의 어떤 기기인지 등록합니다.",
                style: TextStyle(fontSize: 18),
              ),
              SizedBox(height: 15),
              Text(
                "🚀 가전 제어: 등록된 가전을 앱을 통해 제어할 수 있습니다. [제어 페이지]에서 방과 가전을 선택하여 사용자가 직접 ON/OFF 동작을 명령합니다.",
                style: TextStyle(fontSize: 18),
              ),
              SizedBox(height: 15),
              Text(
                "📆 예약: 터틀봇에 가전 제어 기능을 예약할 수 있습니다. [예약-예약 생성 페이지]에서 사용자가 직접 방과 가전, 동작, 그리고 날짜와 시간을 선택하여 예약합니다.",
                style: TextStyle(fontSize: 18),
              ),
              SizedBox(height: 15),
              Text(
                "🔔 알림: 터틀봇이 수행한 각종 동작에 대한 알림이 실시간으로 앱에 전송됩니다. [알림 페이지]에서 확인할 수 있습니다.",
                style: TextStyle(fontSize: 18),
              ),
            ],
          ),
        ),
      ),
    );
  }
}
