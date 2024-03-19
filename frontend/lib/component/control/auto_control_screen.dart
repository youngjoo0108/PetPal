import 'package:flutter/material.dart';
import 'package:frontend/const/colors.dart';
import 'package:frontend/model/appliance.dart';
import 'package:frontend/model/room.dart';

class AutoControlScreen extends StatefulWidget {
  const AutoControlScreen({super.key});

  @override
  State<AutoControlScreen> createState() => _AutoControlScreenState();
}

class _AutoControlScreenState extends State<AutoControlScreen> {
  int _selectedRoomIndex = 0;

  final rooms = [
    Room(
      name: '거실',
      appliances: [
        Appliance(name: '전등', imagePath: 'asset/img/light.png'),
        Appliance(name: '커튼', imagePath: 'asset/img/curtains.png'),
        Appliance(name: 'TV', imagePath: 'asset/img/tv.png'),
        Appliance(name: '에어컨', imagePath: 'asset/img/airConditioner.png'),
        Appliance(name: '공기청정기', imagePath: 'asset/img/purifier.png'),
      ],
    ),
    Room(
      name: '주방',
      appliances: [
        Appliance(name: '전등', imagePath: 'asset/img/light.png'),
        Appliance(name: '커튼', imagePath: 'asset/img/curtains.png'),
        Appliance(name: '세탁기', imagePath: 'asset/img/washingMachine.png'),
      ],
    ),
    Room(
      name: '침실',
      appliances: [
        Appliance(name: '전등', imagePath: 'asset/img/light.png'),
        Appliance(name: '커튼', imagePath: 'asset/img/curtains.png'),
        Appliance(name: 'TV', imagePath: 'asset/img/tv.png'),
        Appliance(name: '에어컨', imagePath: 'asset/img/airConditioner.png'),
        Appliance(name: '공기청정기', imagePath: 'asset/img/purifier.png'),
      ],
    ),
  ];

  List<List<Appliance>> _getPaginatedAppliances(
      List<Appliance> appliances, int itemsPerPage) {
    var pages = <List<Appliance>>[];
    for (int i = 0; i < appliances.length; i += itemsPerPage) {
      pages.add(appliances.sublist(
          i,
          i + itemsPerPage > appliances.length
              ? appliances.length
              : i + itemsPerPage));
    }
    return pages;
  }

  @override
  Widget build(BuildContext context) {
    var paginatedAppliances =
        _getPaginatedAppliances(rooms[_selectedRoomIndex].appliances, 4);

    return Column(
      crossAxisAlignment: CrossAxisAlignment.start,
      children: [
        Container(
          margin: const EdgeInsets.only(left: 30),
          width: 60,
          child: DropdownButton<int>(
            isExpanded: true,
            value: _selectedRoomIndex,
            items: List.generate(
              rooms.length,
              (index) => DropdownMenuItem<int>(
                value: index,
                child: Text(rooms[index].name),
              ),
            ),
            onChanged: (index) {
              setState(() {
                _selectedRoomIndex = index!;
              });
            },
          ),
        ),
        Expanded(
          child: PageView.builder(
            itemCount: paginatedAppliances.length,
            itemBuilder: (context, pageIndex) {
              return GridView.builder(
                gridDelegate: const SliverGridDelegateWithFixedCrossAxisCount(
                  crossAxisCount: 2, // 한 줄에 2개씩
                ),
                itemCount: paginatedAppliances[pageIndex].length,
                itemBuilder: (context, itemIndex) {
                  final appliance = paginatedAppliances[pageIndex][itemIndex];
                  return Padding(
                    padding: const EdgeInsets.all(8.0),
                    child: Card(
                      color: appliance.isOn ? lightYellow : Colors.grey[100],
                      child: Stack(
                        children: [
                          Center(
                            child: FractionallySizedBox(
                              widthFactor: 3 / 7, // 카드 너비의 2/3만큼 차지
                              heightFactor: 3 / 7, // 카드 높이의 2/3만큼 차지
                              child: Image.asset(appliance.imagePath,
                                  fit: BoxFit.contain),
                            ),
                          ),
                          Positioned(
                            bottom: 10,
                            left: 0,
                            right: 0,
                            child: Text(
                              appliance.name,
                              textAlign: TextAlign.center,
                              style: const TextStyle(
                                fontSize: 17,
                                fontWeight: FontWeight.w600,
                              ),
                            ),
                          ),
                          Positioned(
                            top: 10,
                            right: 10,
                            child: Switch(
                              value: appliance.isOn,
                              onChanged: (bool value) {
                                setState(() {
                                  appliance.isOn = value;
                                });
                              },
                            ),
                          ),
                        ],
                      ),
                    ),
                  );
                },
              );
            },
          ),
        ),
      ],
    );
  }
}
