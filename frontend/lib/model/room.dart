class Room {
  final String name;

  Room({required this.name});

  // JSON 데이터로부터 Room 객체를 생성하는 팩토리 생성자
  factory Room.fromJson(Map<String, dynamic> json) {
    return Room(
      name: json['name'],
    );
  }

  // Room 객체를 JSON 데이터로 변환하는 메서드
  Map<String, dynamic> toJson() {
    return {
      'name': name,
    };
  }
}
