package com.ssafy.petpal.room.service;

import com.ssafy.petpal.home.entity.Home;
import com.ssafy.petpal.home.repository.HomeRepository;
import com.ssafy.petpal.room.dto.RoomRegisterDTO;
import com.ssafy.petpal.room.dto.RoomResponseDTO;
import com.ssafy.petpal.room.entity.Room;
import com.ssafy.petpal.room.repository.RoomRepository;
import lombok.RequiredArgsConstructor;
import lombok.extern.slf4j.Slf4j;
import org.springframework.stereotype.Service;

import java.util.List;

@Service
@Slf4j
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

    public List<RoomResponseDTO> fetchAllRoomById(Long homeId) {
        log.info("33");
        List<RoomResponseDTO> allByHomeId = roomRepository.findAllByHomeId(homeId);
        log.info("35");
        return allByHomeId;
    }
}
