import 'package:flutter/material.dart';
import 'package:frontend/model/appliance.dart';
import 'package:frontend/model/room.dart';

class Reservation {
  final Room room;
  final Appliance appliance;
  final DateTime date;
  final TimeOfDay time;
  bool isActive;

  Reservation({
    required this.room,
    required this.appliance,
    required this.date,
    required this.time,
    this.isActive = true,
  });
}
