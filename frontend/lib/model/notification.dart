class Noti {
  final int id;
  final int targetUserId;
  final String category;
  final String content;
  final String time; // DateTime 대신 String을 사용
  final String imageUrl;

  Noti({
    required this.id,
    required this.targetUserId,
    required this.category,
    required this.content,
    required this.time,
    required this.imageUrl,
  });

  factory Noti.fromJson(Map<String, dynamic> json) {
    return Noti(
      id: json['id'] as int,
      targetUserId: json['targetUserId'] as int,
      category: json['category'] as String,
      content: json['content'] as String,
      time: json['time'] as String,
      imageUrl: json['image'] as String,
    );
  }

  @override
  String toString() {
    return 'ID: $id, Target User ID: $targetUserId, Category: $category, Content: $content, Time: $time, Image URL: $imageUrl';
  }
}
