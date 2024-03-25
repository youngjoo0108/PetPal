import 'package:flutter/material.dart';
import 'package:timezone/data/latest.dart' as tz;
import 'package:timezone/timezone.dart' as tz;

// 한국 시간대 맞는 날짜와 시간 정보를 만들어주는 클래스
class TimeCreator {
  static void initializeTimeZones() {
    if (!tz.timeZoneDatabase.isInitialized) {
      tz.initializeTimeZones();
    }
  }

  static tz.Location korea = tz.getLocation('Asia/Seoul');

  static DateTime nowInKorea() {
    final tz.TZDateTime now = tz.TZDateTime.now(korea);
    return DateTime(
        now.year, now.month, now.day, now.hour, now.minute, now.second);
  }

  static DateTime specificDateInKorea(int year, int month, int day) {
    final tz.TZDateTime specificDate = tz.TZDateTime(korea, year, month, day);
    return DateTime(specificDate.year, specificDate.month, specificDate.day);
  }

  static TimeOfDay timeOfDayInKorea() {
    final tz.TZDateTime now = tz.TZDateTime.now(korea);
    return TimeOfDay(hour: now.hour, minute: now.minute);
  }
}
