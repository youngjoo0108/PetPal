class Appliance {
  final int roomId;
  final String roomName;
  final int applianceId;
  final String applianceUUID;
  final String applianceType;
  String imagePath = "";
  String applianceStatus; // 상태를 String으로 변경

  Appliance({
    required this.roomId,
    required this.roomName,
    required this.applianceId,
    required this.applianceUUID,
    required this.applianceType,
    required this.applianceStatus, // 타입 변경
  }) {
    imagePath = getImagePath(applianceType);
  }

  factory Appliance.fromJson(Map<String, dynamic> json) {
    return Appliance(
      roomId: json['roomId'],
      roomName: json['roomName'],
      applianceId: json['applianceId'],
      applianceUUID: json['applianceUUID'],
      applianceType: json['applianceType'],
      applianceStatus: json['applianceStatus'] == "NULL"
          ? "OFF"
          : json['applianceStatus'], // "ON" 또는 "OFF"
    );
  }

  Map<String, dynamic> toJson() {
    return {
      'roomId': roomId,
      'roomName': roomName,
      'applianceId': applianceId,
      'applianceUUID': applianceUUID,
      'applianceType': applianceType,
      'applianceStatus': applianceStatus, // String 타입 그대로 반환
    };
  }

  void togglePower() {
    applianceStatus = applianceStatus == "ON" ? "OFF" : "ON";
  }

  static String getImagePath(String applianceType) {
    switch (applianceType) {
      case "에어컨":
        return "asset/img/airConditioner.png";
      case "커튼":
        return "asset/img/curtains.png";
      case "전등":
        return "asset/img/light.png";
      case "공기청정기":
        return "asset/img/purifier.png";
      case "TV":
        return "asset/img/tv.png";
      default:
        return "asset/img/washingMachine.png";
    }
  }
}
