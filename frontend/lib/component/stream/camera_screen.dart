import 'dart:async';
import 'dart:convert';
import 'dart:collection';
import 'dart:typed_data';
import 'package:flutter/material.dart';
import 'package:logger/logger.dart';
import 'package:flutter_dotenv/flutter_dotenv.dart';
import 'package:stomp_dart_client/stomp.dart';
import 'package:stomp_dart_client/stomp_config.dart';
import 'package:stomp_dart_client/stomp_frame.dart';

class CameraScreen extends StatefulWidget {
  const CameraScreen({super.key});

  @override
  CameraScreenState createState() => CameraScreenState();
}

class CameraScreenState extends State<CameraScreen> {
  final wsUrl = dotenv.env['WS_URL']; // WebSocket URL
  final Logger logger = Logger();
  late StompClient stompClient;
  final Queue<Uint8List> _imageQueue = Queue<Uint8List>();
  final int _frameDelay = 30; // Delay in milliseconds for 15fps
  late Timer _renderTimer;
  Uint8List? _currentImage;
  Uint8List? _prevImage;

  @override
  void initState() {
    super.initState();
    _initializeWebSocketConnection();
    _startRendering();
  }

  void _initializeWebSocketConnection() {
    stompClient = StompClient(
      config: StompConfig(
        url: wsUrl!,
        onConnect: _onStompConnect,
        beforeConnect: () async {
          logger.d('waiting to connect...');
          logger.d('connecting...');
        },
        onWebSocketError: (dynamic error) => logger.e(error.toString()),
      ),
    );
    stompClient.activate();
  }

  void _onStompConnect(StompFrame frame) {
    stompClient.subscribe(
      destination: '/exchange/control.exchange/user.1',
      callback: (frame) {
        if (frame.body != null) {
          /*
          json.decode(frame.body!)['type'] == "video_streaming"인지 확인하는 로직 추가 
          */
          final String? imageBase64 = json.decode(frame.body!)['message'];
          if (imageBase64 != null) {
            _imageQueue.add(base64Decode(imageBase64));
          }
        }
      },
    );
  }

  void _startRendering() {
    _renderTimer = Timer.periodic(Duration(milliseconds: _frameDelay), (_) {
      if (_imageQueue.isNotEmpty) {
        setState(() {
          updateImages();
        });
      }
    });
  }

  void updateImages() {
    _prevImage = _currentImage;
    _currentImage = _imageQueue.first;
    _imageQueue.removeFirst();
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      body: Center(
        child: Stack(
          children: [
            if (_prevImage != null)
              Positioned.fill(
                child: Image.memory(_prevImage!),
              ),
            if (_currentImage != null)
              Positioned.fill(
                child: Image.memory(_currentImage!),
              ),
          ],
        ),
      ),
    );
  }

  @override
  void dispose() {
    stompClient.deactivate();
    _renderTimer.cancel();
    super.dispose();
  }
}
