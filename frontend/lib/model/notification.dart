class Noti {
  final String category;
  final String content;
  final DateTime timestamp;
  final String imageUrl;

  Noti({
    required this.category,
    required this.content,
    required this.timestamp,
    required this.imageUrl,
  });

  @override
  String toString() {
    return 'Category: $category, Content: $content, Timestamp: $timestamp, Image URL: $imageUrl';
  }
}
