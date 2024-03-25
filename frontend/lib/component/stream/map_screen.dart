import 'package:flutter/material.dart';
import 'package:frontend/component/stream/map_view_screen.dart';

class MapScreen extends StatelessWidget {
  const MapScreen({super.key});

  @override
  Widget build(BuildContext context) {
    return Padding(
      padding: const EdgeInsets.all(20.0),
      child: ClipRRect(
        borderRadius: BorderRadius.circular(10.0),
        child: const MapView(),
      ),
    );
  }
}
