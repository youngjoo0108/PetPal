import 'package:flutter/material.dart';

class TabInfo {
  final IconData icon;
  final String label;
  final String location;

  const TabInfo({
    required this.icon,
    required this.label,
    required this.location,
  });
}

const tabs = [
  TabInfo(
    icon: Icons.home,
    label: '홈',
    location: 'HomeScreen',
  ),
  TabInfo(
    icon: Icons.android,
    label: '모드',
    location: 'ModeScreen',
  ),
  TabInfo(
    icon: Icons.control_camera_rounded,
    label: '제어',
    location: 'ControlScreen',
  ),
  TabInfo(
    icon: Icons.notifications,
    label: '알림',
    location: 'NotiScreen',
  ),
  TabInfo(
    icon: Icons.menu,
    label: '메뉴',
    location: 'MenuScreen',
  ),
];
