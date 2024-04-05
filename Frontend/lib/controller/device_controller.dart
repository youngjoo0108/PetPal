import 'package:get/get.dart';

class DeviceController extends GetxController {
  var isOn = false.obs;
  var isPatrollingMode = true.obs;

  void toggleDevice() {
    isOn.value = !isOn.value;
  }

  void toggleMode() {
    isPatrollingMode.value = !isPatrollingMode.value;
  }
}
