import 'dart:convert';

import 'package:flutter/material.dart';
import 'package:flutter_secure_storage/flutter_secure_storage.dart';
import 'package:frontend/component/menu/register_appliance.dart';
import 'package:frontend/const/colors.dart';
import 'package:frontend/const/global_alert_dialog.dart';
import 'package:frontend/model/appliance.dart';
import 'package:frontend/service/appliance_service.dart';
import 'package:frontend/socket/socket.dart';
import 'package:get/get.dart';
import 'package:logger/logger.dart';
import 'package:stomp_dart_client/stomp_frame.dart';

final Logger logger = Logger();

class ApplianceManagement extends StatefulWidget {
  const ApplianceManagement({super.key});

  @override
  ApplianceManagementState createState() => ApplianceManagementState();
}

class ApplianceManagementState extends State<ApplianceManagement> {
  final ApplianceService _applianceService = ApplianceService();
  List<Appliance> appliances = [];
  bool isLoading = true;
  final SocketController socketController = Get.find<SocketController>();
  final FlutterSecureStorage secureStorage = const FlutterSecureStorage();
  late String scannedApplianceUUID;
  bool _isRegistering = false;

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
        title: const Text('가전 관리'),
      ),
      body: isLoading
          ? const Center(child: CircularProgressIndicator())
          : _isRegistering
              ? const Center(
                  child: CircularProgressIndicator()) // 등록 중 로딩 인디케이터
              : ListView.builder(
                  itemCount: appliances.length,
                  itemBuilder: (context, index) {
                    Appliance appliance = appliances[index];
                    return Dismissible(
                      key: Key(appliance.hashCode.toString()),
                      onDismissed: (direction) async {
                        final applianceId = appliances[index].applianceId;
                        // 서버에서 스케줄 삭제 시도
                        bool success = await ApplianceService()
                            .deleteAppliance(applianceId);
                        if (!success) {
                          // 삭제 실패 시 GlobalAlertDialog로 실패 알림
                          GlobalAlertDialog.show(
                            context,
                            title: "서버 에러",
                            message: "가전 삭제에 실패했습니다.",
                          );
                          // 실패한 스케줄을 다시 리스트에 추가 (UI 업데이트)
                          setState(() {
                            appliances.insert(index, appliance);
                          });
                        } else {
                          // 삭제 성공 시 스케줄 리스트에서 해당 스케줄 제거
                          setState(() {
                            appliances.removeAt(index);
                          });
                          GlobalAlertDialog.show(
                            context,
                            title: "알림",
                            message: "가전을 삭제했습니다.",
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
                      child: ListTile(
                        title: Text(appliance.roomName),
                        subtitle: Text(appliance.applianceType),
                        // 여기서 추가적인 액션(예: 수정, 삭제)에 대한 아이콘 버튼을 추가할 수 있습니다.
                        onTap: () {
                          // 아이템 탭 시 실행할 액션: 예를 들어, 가전 상세 페이지로 이동
                        },
                      ),
                    );
                  },
                ),
      // 가전 등록 페이지로 이동할 수 있는 FAB 추가
      floatingActionButton: FloatingActionButton(
        onPressed: () async {
          final String? homeId = await secureStorage.read(key: "homeId");
          setState(() {
            _isRegistering = true; // 로딩 시작
          });
          socketController.subscribeToDestination(
            "/exchange/control.exchange/home.$homeId",
            _getApplianceUUID,
          );
          socketController.sendMessage(
            destination: '/pub/control.message.$homeId',
            type: 'REGISTER_REQUEST',
            messageContent: '',
          );
        },
        tooltip: 'Register Appliance',
        child: const Icon(Icons.add),
      ),
    );
  }

  void _getApplianceUUID(StompFrame frame) {
    final data = json.decode(frame.body ?? '{}');
    if (data['type'] == 'REGISTER_RESPONSE') {
      logger.d("Succeed to register IOT");
      setState(() {
        _isRegistering = false; // 로딩 종료
      });
      scannedApplianceUUID = data['message'];
      logger.d("scannedApplianceUUID: $scannedApplianceUUID");
      GlobalAlertDialog.show(
        context,
        title: "알림",
        message: "기기가 등록되었습니다.",
      ).then((_) {
        Navigator.push(
          context,
          MaterialPageRoute(
              builder: (context) => RegisterAppliance(
                    applianceUUID: scannedApplianceUUID,
                  )),
        ).then((value) {
          // RegisterAppliance 페이지에서 true 값을 반환받았을 때만 _fetchAppliances() 호출
          if (value == true) {
            _fetchAppliances();
          }
        });
      });
    }
  }
}
