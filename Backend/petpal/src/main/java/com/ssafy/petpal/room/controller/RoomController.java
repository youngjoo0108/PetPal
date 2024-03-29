package com.ssafy.petpal.room.controller;

import com.ssafy.petpal.room.dto.RoomRegisterDTO;
import com.ssafy.petpal.room.entity.Room;
import com.ssafy.petpal.room.service.RoomService;
import lombok.RequiredArgsConstructor;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

import java.util.List;

@RestController
@RequiredArgsConstructor
@RequestMapping("/api/v1/rooms")
public class RoomController {
    private final RoomService roomService;

    @PostMapping
    public ResponseEntity<Void> postRoom(RoomRegisterDTO roomRegisterDTO){
        try{
            roomService.createRoom(roomRegisterDTO);
            return ResponseEntity.ok(null);
        }catch (Exception e) {
            return ResponseEntity.status(HttpStatus.INTERNAL_SERVER_ERROR).build();
        }
    }

    @GetMapping
    public ResponseEntity<List<Room>> getRooms(Long homeId){
        try{
            List<Room> list = roomService.fetchAllRoomById(homeId);
            return ResponseEntity.ok(list);
        }catch (Exception e){
            return ResponseEntity.status(HttpStatus.INTERNAL_SERVER_ERROR).build();
        }
    }
}
