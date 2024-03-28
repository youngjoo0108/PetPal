package com.ssafy.petpal.room.service;

import com.ssafy.petpal.home.entity.Home;
import com.ssafy.petpal.home.repository.HomeRepository;
import com.ssafy.petpal.room.dto.RoomRegisterDTO;
import com.ssafy.petpal.room.entity.Room;
import com.ssafy.petpal.room.repository.RoomRepository;
import lombok.RequiredArgsConstructor;
import org.springframework.stereotype.Service;

import java.util.List;

@Service
@RequiredArgsConstructor
public class RoomService {

    private final RoomRepository roomRepository;
    private final HomeRepository homeRepository;
    public void createRoom(RoomRegisterDTO roomRegisterDTO) {
        Home home = homeRepository.findById(roomRegisterDTO.getHomeId())
                .orElseThrow(IllegalArgumentException::new);
        Room room  = Room.builder()
                .roomName(roomRegisterDTO.getRoomName())
                .home(home)
                .build();
        roomRepository.save(room);
    }

    public List<Room> fetchAllRoomById(Long homeId) {
        return roomRepository.findAllByHomeId(homeId);
    }
}
