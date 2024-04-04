import 'package:get/get.dart';
import 'dart:convert';
import 'package:flutter_dotenv/flutter_dotenv.dart';
import 'package:flutter_secure_storage/flutter_secure_storage.dart';
import 'package:frontend/const/time_creator.dart';
import 'package:logger/logger.dart';
import 'package:stomp_dart_client/stomp.dart';
import 'package:stomp_dart_client/stomp_config.dart';
import 'package:stomp_dart_client/stomp_frame.dart';

class SocketController extends GetxController {
  late StompClient stompClient;
  final Logger logger = Logger();
  final String? wsUrl = dotenv.env['WS_URL'];
  final FlutterSecureStorage secureStorage = const FlutterSecureStorage();
  dynamic unsubscribeFn;
  final isInitialized = false.obs; // StompClient 초기화 상태 추적

  @override
  void onInit() {
    super.onInit();
    isInitialized.value = false;
    initializeWebSocketConnection();
  }

  // 연결 초기화 및 선택적으로 구독 시작
  void initializeWebSocketConnection(
      {String? destination, Function(StompFrame)? onMessageReceived}) {
    stompClient = StompClient(
      config: StompConfig(
        url: wsUrl!,
        onConnect: (StompFrame frame) {
          isInitialized.value = true;

          logger.d('Connected to WebSocket');
          if (destination != null && onMessageReceived != null) {
            subscribeToDestination(destination, onMessageReceived);
          }
        },
        beforeConnect: () async {
          logger.d('Waiting to connect...');
        },
        onWebSocketError: _defaultWebSocketError,
      ),
    );
    stompClient.activate();
  }

  void subscribeToDestination(
      String destination, Function(StompFrame) onMessageReceived) {
    unsubscribeFn = stompClient.subscribe(
      destination: destination,
      callback: onMessageReceived,
    );
    logger.d('Subscribed to $destination');
  }

  void sendMessage({
    required String destination,
    required String type,
    required String messageContent,
  }) async {
    logger.d('stompClient Connection: ${stompClient.connected}');
    final String? userId = await secureStorage.read(key: "userId");
    var message = jsonEncode({
      'type': type,
      'sender': '$userId',
      'time': TimeCreator.nowInKorea().toIso8601String(),
      'message': messageContent,
    });

    send(destination, message);
  }

  void send(String destination, String message,
      {Map<String, String>? headers}) {
    final Map<String, String> defaultHeaders = {
      'Content-Type': 'application/json',
    };

    final Map<String, String> resolvedHeaders = {}
      ..addAll(defaultHeaders)
      ..addAll(headers ?? {});

    stompClient.send(
      destination: destination,
      body: message,
      headers: resolvedHeaders,
    );
    logger.d('Message sent to $destination: $message');
  }

  void _defaultWebSocketError(dynamic error) {
    logger.e('WebSocket Error: $error');
  }

  @override
  void onClose() {
    super.onClose();
    deactivate();
  }

  void deactivate() {
    if (stompClient.connected) {
      stompClient.deactivate();
    }
  }
}
