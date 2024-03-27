import 'dart:convert';
import 'package:flutter/material.dart';
import 'package:web_socket_channel/web_socket_channel.dart';
import 'package:logger/logger.dart';
import 'package:flutter_dotenv/flutter_dotenv.dart';

class CameraScreen extends StatefulWidget {
  const CameraScreen({super.key});

  @override
  CameraScreenState createState() => CameraScreenState();
}

class CameraScreenState extends State<CameraScreen> {
  final wsUrl = dotenv.env['WS_URL'];
  final Logger logger = Logger();
  late WebSocketChannel channel;
  String? _imageBase64;

  @override
  void initState() {
    super.initState();
    // WebSocket 서버 URL을 사용하여 채널을 초기화
    channel = WebSocketChannel.connect(Uri.parse('$wsUrl'));

    logger.d('Attempting to connect to WebSocket at $wsUrl');
    // 메시지를 수신 대기
    channel.stream.listen((message) {
      logger.d('Received message: $message');
      setState(() {
        // 메시지 파싱 로직에 따라 _imageBase64를 업데이트
        final decodedMessage = json.decode(message);
        logger.d(message);
        if (decodedMessage['type'] == 'video_streaming') {
          _imageBase64 = decodedMessage['message'];
          logger.d('Updated _imageBase64 with video_streaming data');
        }
      });
    }, onDone: () {
      // WebSocket 연결이 종료되면 실행
      logger.d('WebSocket connection closed');
    }, onError: (error) {
      // 에러 처리
      logger.e(error);
      logger.e('WebSocket error: $error');
    });
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      body: _imageBase64 == null
          ? const Center(child: Text('No data'))
          : Padding(
              padding: const EdgeInsets.only(top: 20, right: 20, left: 20),
              child: Container(
                width: 320, // 이미지의 너비 설정
                height: 240, // 이미지의 높이 설정
                decoration: BoxDecoration(
                  // WebSocket에서 받은 이미지 데이터를 사용
                  image: DecorationImage(
                    image: MemoryImage(base64Decode(_imageBase64!)),
                    fit: BoxFit.cover, // 이미지가 컨테이너 영역을 꽉 채우도록 설정
                  ),
                  boxShadow: [
                    BoxShadow(
                      color: Colors.grey.withOpacity(0.5),
                      spreadRadius: 3,
                      blurRadius: 4,
                      offset: const Offset(0, 3), // 그림자의 위치 조정
                    ),
                  ],
                  borderRadius:
                      const BorderRadius.all(Radius.circular(20)), // 모서리 처리
                ),
              ),
            ),
    );
  }

  @override
  void dispose() {
    channel.sink.close();
    super.dispose();
  }
}
