import 'dart:async';
import 'dart:convert';
import 'dart:collection';
import 'dart:typed_data';
import 'package:flutter/material.dart';
import 'package:flutter_secure_storage/flutter_secure_storage.dart';
import 'package:frontend/socket/socket.dart';
import 'package:get/get.dart';
import 'package:logger/logger.dart';
import 'package:stomp_dart_client/stomp_frame.dart';

class CameraScreen extends StatefulWidget {
  const CameraScreen({super.key});

  @override
  CameraScreenState createState() => CameraScreenState();
}

class CameraScreenState extends State<CameraScreen> {
  final Logger logger = Logger();
  final Queue<Uint8List> _imageQueue = Queue<Uint8List>();
  final int _frameDelay = 30; // Delay in milliseconds for 15fps
  late Timer _renderTimer;
  Uint8List? _currentImage;
  Uint8List? _prevImage;
  final SocketController socketController = Get.find<SocketController>();
  final FlutterSecureStorage secureStorage = const FlutterSecureStorage();

  @override
  void initState() {
    super.initState();
    initWebSocket();
    _startRendering();
  }

  void initWebSocket() async {
    final String? homeId = await secureStorage.read(key: "homeId");
    socketController.initializeWebSocketConnection(
      destination: '/exchange/control.exchange/home.$homeId.images',
      onMessageReceived: _onMessageReceived,
    );
  }

  void _onMessageReceived(StompFrame frame) {
    if (frame.body != null) {
      final data = json.decode(frame.body!);
      if (data['type'] == "video_streaming") {
        final String? imageBase64 = data['message'];
        if (imageBase64 != null) {
          _imageQueue.add(base64Decode(imageBase64));
        }
      }
    }
  }

  void _startRendering() {
    _renderTimer = Timer.periodic(Duration(milliseconds: _frameDelay), (_) {
      if (_imageQueue.isNotEmpty) {
        setState(() {
          _updateImages();
        });
      }
    });
  }

  void _updateImages() {
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
            if (_prevImage == null && _currentImage == null)
              const Positioned.fill(
                child: Text("Data Loading . . ."),
              ),
          ],
        ),
      ),
    );
  }

  @override
  void dispose() {
    _renderTimer.cancel();
    super.dispose();
  }
}
