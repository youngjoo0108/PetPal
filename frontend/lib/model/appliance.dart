class Appliance {
  final String name;
  final String imagePath;
  bool isOn;

  Appliance({
    required this.name,
    required this.imagePath,
    this.isOn = false,
  });

  void togglePower() {
    isOn = !isOn;
  }
}
