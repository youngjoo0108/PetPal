import 'package:flutter/material.dart';
import 'package:frontend/model/appliance.dart';

class Schedule {
  final int scheduleId;
  final Appliance appliance; // 가전
  final DateTime date; // 날짜
  final TimeOfDay time; // 시간
  final String action; // 'on' || 'off'
  bool isActive; // 인스턴스 활성화 여부

  Schedule({
    required this.scheduleId,
    required this.appliance,
    required this.date,
    required this.time,
    required this.action,
    this.isActive = true,
  });

  factory Schedule.fromJson(Map<String, dynamic> json) {
    return Schedule(
      scheduleId: json['scheduleId'] as int,
      appliance:
          Appliance.fromJson(json['appliance']), // Appliance의 fromJson 메서드가 필요
      date: DateTime.parse(json['date']),
      time: TimeOfDay(
        hour: int.parse(json['time'].split(":")[0]),
        minute: int.parse(json['time'].split(":")[1]),
      ),
      action: json['action'] as String,
      isActive: json['isActive'] as bool,
    );
  }

  Map<String, dynamic> toJson() {
    return {
      'scheduleId': scheduleId,
      'appliance': appliance.toJson(), // Appliance의 toJson 메서드가 필요
      'date': date.toIso8601String(),
      'time': '${time.hour}:${time.minute}',
      'action': action,
      'isActive': isActive,
    };
  }
}
