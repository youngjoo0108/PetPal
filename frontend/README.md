# About

Frontend source of project PETPAL

## Structure
```
frontend
├── main.dart
│
├── component // Smaller units than screens, rendering detailed UIs within screens.
│ ├── control
│ │ ├── auto_control_screen.dart
│ │ └── manual_screen.dart
│ │
│ ├── reserve
│ │ └── create_reserve_screen.dart
│ │
│ ├── stream
│ │ ├── camera_screen.dart
│ │ ├── map_screen.dart
│ │ └── map_view_screen.dart
│ │
│ └── weather
│ ├── indoor_screen.dart
│ ├── outdoor_screen.dart
│ ├── weather_screen.dart
│ └── weather_text.dart
│
├── const // Defines global variables and methods used across the APK.
│ ├── colors.dart
│ ├── global_alert_dialog.dart
│ ├── map_painter.dart
│ ├── secure_storage.dart
│ ├── tabs.dart
│ └── time_creator.dart
│
├── model // Defines objects used for API integration and within the app itself.
│ ├── appliance.dart
│ ├── notification.dart
│ ├── reservation.dart
│ └── room.dart
│
├── screen // Defines the main screens of the APK and screens for each feature.
│ ├── control_screen.dart
│ ├── home_screen.dart
│ ├── login_screen.dart
│ ├── main_screen.dart
│ ├── menu_screen.dart
│ ├── mode_screen.dart
│ ├── noti_screen.dart
│ └── reserve_screen.dart
│
├── service // Functions needed for server and external API integration.
│ ├── control_service.dart
│ ├── fetch_weather.dart
│ ├── noti_service.dart
│ ├── reserve_service.dart
│ └── user_service.dart
│
└── socket // Defines functions related to WebSocket.
└── socket.dart
```