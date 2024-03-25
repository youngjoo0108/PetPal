import 'package:flutter/material.dart';
import 'package:frontend/const/colors.dart';

class GlobalAlertDialog {
  static Future<void> show(BuildContext context,
      {String? title, required String message}) {
    return showDialog<void>(
      context: context,
      barrierDismissible: false, // 사용자가 다이얼로그 바깥을 탭하면 닫히지 않도록 설정
      builder: (BuildContext context) {
        return AlertDialog(
          title:
              title != null ? Text(title) : null, // title이 null이 아닐 경우에만 제목을 표시
          backgroundColor: lightYellow,
          content: SingleChildScrollView(
            child: ListBody(
              children: <Widget>[
                Text(message),
              ],
            ),
          ),
          actions: <Widget>[
            TextButton(
              child: const Text('확인'),
              onPressed: () {
                Navigator.of(context).pop(); // 다이얼로그 닫기
              },
            ),
          ],
        );
      },
    );
  }
}
