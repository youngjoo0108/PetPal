import 'package:flutter_dotenv/flutter_dotenv.dart';
import 'package:logger/logger.dart';
import 'package:stomp_dart_client/stomp.dart';
import 'package:stomp_dart_client/stomp_config.dart';
import 'package:stomp_dart_client/stomp_frame.dart';

class SocketService {
  late StompClient stompClient;
  final Logger logger = Logger();
  final String? wsUrl = dotenv.env['WS_URL']; // WebSocket URL
  Function(StompFrame)? onConnectCallback;
  Function(dynamic)? onWebSocketError;
  String destination;
  Function(StompFrame) onMessageReceived;

  SocketService({
    required this.destination,
    required this.onMessageReceived,
    this.onConnectCallback,
    this.onWebSocketError,
  }) {
    _initializeWebSocketConnection();
  }

  void _initializeWebSocketConnection() {
    stompClient = StompClient(
      config: StompConfig(
        url: wsUrl!,
        onConnect: onConnectCallback ?? _defaultOnConnect,
        beforeConnect: () async {
          logger.d('Waiting to connect...');
          logger.d('Connecting...');
        },
        onWebSocketError: onWebSocketError ?? _defaultWebSocketError,
      ),
    );
    stompClient.activate();
  }

  void _defaultOnConnect(StompFrame frame) {
    subscribeToDestination(destination);
  }

  void subscribeToDestination(String destination) {
    stompClient.subscribe(
      destination: destination,
      callback: onMessageReceived,
    );
  }

  void _defaultWebSocketError(dynamic error) {
    logger.e(error.toString());
  }

  void deactivate() {
    stompClient.deactivate();
  }
}
