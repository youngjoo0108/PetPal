import 'package:flutter/material.dart';
import 'package:flutter_secure_storage/flutter_secure_storage.dart';
// import 'package:frontend/screen/login_screen.dart';
import 'package:frontend/screen/main_screen.dart';

void main() {
  runApp(
    MaterialApp(
        // theme: ThemeData(fontFamily: 'Samsung'),
        // debugShowCheckedModeBanner: false,
        initialRoute: '/',
        routes: {
          '/': (context) => const MainScreen(),
          // '/home': (context) => MainScreen(),
          // '/intro':(context) => IntroScreen(),
          // '/calendar': (context) => CalendarScreen(),
          // '/log':(context)=>LogScreen(),
        }),
  );
}

class MyApp extends StatelessWidget {
  // flutter_secure_storage 인스턴스 생성
  final storage = const FlutterSecureStorage();

  const MyApp({super.key});

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      title: 'PETPAL',
      home: FutureBuilder(
        future: storage.read(key: "isLoggedIn"),
        builder: (context, snapshot) {
          // 로그인 상태 확인 로직
          if (snapshot.data != null && snapshot.data == "true") {
            // 로그인 상태이면 메인 화면으로
            return const MainScreen();
          } else {
            // 로그인 상태가 아니면 로그인 화면으로
            return const MainScreen();
          }
        },
      ),
    );
  }
}

// -------------------- Sample Code ------------------------
// class MyApp extends StatelessWidget {
//   const MyApp({super.key});

//   // This widget is the root of your application.
//   @override
//   Widget build(BuildContext context) {
//     return MaterialApp(
//       title: 'Flutter Demo',
//       theme: ThemeData(
//         colorScheme: ColorScheme.fromSeed(seedColor: Colors.deepPurple),
//         useMaterial3: true,
        
//       ),
//       // home: const MyHomePage(title: 'Flutter Demo Home Page'),
//     );
//   }
// }

// class MyHomePage extends StatefulWidget {
//   const MyHomePage({super.key, required this.title});
//   final String title;

//   @override
//   State<MyHomePage> createState() => _MyHomePageState();
// }

// class _MyHomePageState extends State<MyHomePage> {
//   int _counter = 0;

//   void _incrementCounter() {
//     setState(() {
//       _counter++;
//     });
//   }

//   @override
//   Widget build(BuildContext context) {
//     return Scaffold(
//       appBar: AppBar(
//         backgroundColor: Theme.of(context).colorScheme.inversePrimary,
//         title: Text(widget.title),
//       ),
//       body: Center(
//         child: Column(
//           mainAxisAlignment: MainAxisAlignment.center,
//           children: <Widget>[
//             const Text(
//               'You have pushed the button this many times:',
//             ),
//             Text(
//               '$_counter',
//               style: Theme.of(context).textTheme.headlineMedium,
//             ),
//           ],
//         ),
//       ),
//       floatingActionButton: FloatingActionButton(
//         onPressed: _incrementCounter,
//         tooltip: 'Increment',
//         child: const Icon(Icons.add),
//       ), // This trailing comma makes auto-formatting nicer for build methods.
//     );
//   }
// }