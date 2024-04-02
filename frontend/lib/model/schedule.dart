import 'package:flutter/material.dart';

class Schedule {
  final int scheduleId;
  final int applianceId;
  final String applianceType;
  final String roomName;
  final DateTime day;
  final TimeOfDay time;
  final String taskType;
  bool isActive;

  Schedule({
    required this.scheduleId,
    required this.applianceId,
    required this.applianceType,
    required this.roomName,
    required this.day,
    required this.time,
    required this.taskType,
    required this.isActive,
  });

  factory Schedule.fromJson(Map<String, dynamic> json) {
    final day = DateTime.parse(json['day']);
    final timeParts = (json['time'] as String).split(':');
    final time = TimeOfDay(
        hour: int.parse(timeParts[0]), minute: int.parse(timeParts[1]));

    return Schedule(
      scheduleId: json['scheduleId'],
      applianceId: json['applianceId'],
      applianceType: json['applianceType'],
      roomName: json['roomName'],
      day: day,
      time: time,
      taskType: json['taskType'],
      isActive: json['active'],
    );
  }
}
