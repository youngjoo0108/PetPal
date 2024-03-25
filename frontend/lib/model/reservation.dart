import 'package:flutter/material.dart';
import 'package:frontend/model/appliance.dart';
import 'package:frontend/model/room.dart';

class Reservation {
  final Room room; // 방
  final Appliance appliance; // 가전
  final DateTime date; // 날짜
  final TimeOfDay time; // 시간
  final String action; // 'on' || 'off'
  bool isActive; // 인스턴스 활성화 여부

  Reservation({
    required this.room,
    required this.appliance,
    required this.date,
    required this.time,
    required this.action,
    this.isActive = true,
  });
}
