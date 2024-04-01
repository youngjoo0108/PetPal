class Appliance {
  final int roomId;
  final String roomName;
  final int applianceId;
  final String applianceType;
  String imagePath = "";
  int applianceStatus;

  Appliance({
    required this.roomId,
    required this.roomName,
    required this.applianceId,
    required this.applianceType,
    required this.applianceStatus,
  }) {
    imagePath = getImagePath(applianceType);
  }

  // JSON 데이터로부터 Appliance 객체를 생성하는 팩토리 생성자
  factory Appliance.fromJson(Map<String, dynamic> json) {
    return Appliance(
      roomId: json['roomId'] as int,
      roomName: json['roomName'] as String,
      applianceId: json['applianceId'] as int,
      applianceType: json['applianceType'] as String,
      applianceStatus: json['applianceStatus'] as int,
    );
  }

  // Appliance 객체를 JSON 데이터로 변환하는 메서드
  Map<String, dynamic> toJson() {
    return {
      'roomId': roomId,
      'roomName': roomName,
      'applianceId': applianceId,
      'applianceType': applianceType,
      'applianceStatus': applianceStatus,
    };
  }

  void togglePower() {
    applianceStatus = applianceStatus == 1 ? 0 : 1;
  }

  static String getImagePath(String applianceType) {
    return applianceType == "에어컨"
        ? "asset/img/airConditioner.png"
        : applianceType == "에어컨"
            ? "asset/img/curtains.png"
            : applianceType == "전구"
                ? "asset/img/light.png"
                : applianceType == "공기청정기"
                    ? "asset/img/purifier.png"
                    : applianceType == "TV"
                        ? "asset/img/tv.png"
                        : "asset/img/washingMachine.png";
  }
}
