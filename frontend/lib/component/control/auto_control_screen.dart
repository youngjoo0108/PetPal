import 'package:flutter/material.dart';

class AutoControlScreen extends StatefulWidget {
  const AutoControlScreen({super.key});

  @override
  State<AutoControlScreen> createState() => _AutoControlScreenState();
}

class _AutoControlScreenState extends State<AutoControlScreen> {
  int _selectedRoomIndex = 0;

  final List<Map<String, dynamic>> rooms = [
    {
      'name': '거실',
      'appliances': ['TV', '에어컨', '청소기', '공기청정기', '세탁기', '냉장고'],
    },
    {
      'name': '주방',
      'appliances': ['냉장고', '전자레인지', '커피머신'],
    },
    {
      'name': '침실',
      'appliances': ['스탠드', '가습기', '알람시계'],
    },
  ];

  List<List<String>> _getPaginatedAppliances(
      List<String> appliances, int itemsPerPage) {
    var pages = <List<String>>[];
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
        _getPaginatedAppliances(rooms[_selectedRoomIndex]['appliances'], 4);

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
                child: Text(rooms[index]['name']),
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
                  return Padding(
                    padding: const EdgeInsets.all(8.0),
                    child: Card(
                      child: ListTile(
                        title: Text(paginatedAppliances[pageIndex][itemIndex]),
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
