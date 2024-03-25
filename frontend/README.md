# frontend

PETPAL frontend

## Structure

│  main.dart
│
├─component   // screen보다 작은 단위로, screen에서 렌더링되는 세분화된 UI입니다.
│  ├─control  
│  │      auto_control_screen.dart
│  │      manual_screen.dart
│  │
│  ├─reserve
│  │      create_reserve_screen.dart
│  │
│  ├─stream
│  │      camera_screen.dart
│  │      map_screen.dart
│  │      map_view_screen.dart
│  │
│  └─weather
│          indoor_screen.dart
│          outdoor_screen.dart
│          weather_screen.dart
│          weather_text.dart
│
├─const   // APK 전역에서 쓰이는 변수 및 메서드들이 정의되어 있습니다.
│      colors.dart
│      global_alert_dialog.dart
│      map_painter.dart
│      secure_storage.dart
│      tabs.dart
│      time_creator.dart
│
├─model   // API 연동 및 어플 자체에서 사용되는 객체들이 정의되어 있습니다.
│      appliance.dart
│      notification.dart
│      reservation.dart
│      room.dart
│
├─screen  // APK의 메인 화면과 각 기능에 맞는 화면들이 정의되어 있습니다.
│      control_screen.dart
│      home_screen.dart
│      login_screen.dart
│      main_screen.dart
│      menu_screen.dart
│      mode_screen.dart
│      noti_screen.dart
│      reserve_screen.dart
│
├─service // 서버 및 외부 API 연동에 필요한 함수들이 정의되어 있습니다.
│      control_service.dart
│      fetch_weather.dart
│      noti_service.dart
│      reserve_service.dart
│      user_service.dart
│
└─socket  // WebSocket과 관련된 함수들이 정의되어 있습니다.
        socket.dart