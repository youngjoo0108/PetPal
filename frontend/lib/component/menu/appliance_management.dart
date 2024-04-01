import 'package:flutter/material.dart';
import 'package:frontend/component/menu/register_appliance.dart';
import 'package:frontend/model/appliance.dart';
import 'package:frontend/service/appliance_service.dart';

class ApplianceManagement extends StatefulWidget {
  const ApplianceManagement({super.key});

  @override
  ApplianceManagementState createState() => ApplianceManagementState();
}

class ApplianceManagementState extends State<ApplianceManagement> {
  final ApplianceService _applianceService = ApplianceService();
  List<Appliance> appliances = [];
  bool isLoading = true;

  @override
  void initState() {
    super.initState();
    _fetchAppliances();
  }

  _fetchAppliances() async {
    try {
      List<Appliance> loadedAppliances =
          await _applianceService.fetchAppliances();
      setState(() {
        appliances = loadedAppliances;
        isLoading = false;
      });
    } catch (e) {
      setState(() {
        isLoading = false;
      });
      // 에러 처리: 예를 들어, 사용자에게 에러 메시지를 표시
    }
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: const Text('Appliance Management'),
      ),
      body: isLoading
          ? const Center(child: CircularProgressIndicator())
          : ListView.builder(
              itemCount: appliances.length,
              itemBuilder: (context, index) {
                Appliance appliance = appliances[index];
                return ListTile(
                  title: Text(appliance.roomName),
                  subtitle: Text('Type: ${appliance.applianceType}'),
                  // 여기서 추가적인 액션(예: 수정, 삭제)에 대한 아이콘 버튼을 추가할 수 있습니다.
                  onTap: () {
                    // 아이템 탭 시 실행할 액션: 예를 들어, 가전 상세 페이지로 이동
                  },
                );
              },
            ),
      // 가전 등록 페이지로 이동할 수 있는 FAB 추가
      floatingActionButton: FloatingActionButton(
        onPressed: () {
          Navigator.push(
            context,
            MaterialPageRoute(builder: (context) => const RegisterAppliance()),
          ).then((_) {
            // 사용자가 돌아왔을 때 가전 목록을 새로고침
            _fetchAppliances();
          });
        },
        tooltip: 'Register Appliance',
        child: const Icon(Icons.add),
      ),
    );
  }
}
