class Room {
  final int roomId;
  final String roomName;

  Room({required this.roomName, required this.roomId});

  // JSON 데이터로부터 Room 객체를 생성하는 팩토리 생성자
  factory Room.fromJson(Map<String, dynamic> json) {
    return Room(
      roomName: json['roomName'],
      roomId: json['roomId'],
    );
  }

  // Room 객체를 JSON 데이터로 변환하는 메서드
  Map<String, dynamic> toJson() {
    return {
      'roomName': roomName,
      'roomId': roomId,
    };
  }
}
