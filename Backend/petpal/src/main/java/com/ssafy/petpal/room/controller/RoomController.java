package com.ssafy.petpal.room.controller;

import com.ssafy.petpal.room.dto.RoomRegisterDTO;
import com.ssafy.petpal.room.dto.RoomResponseDTO;
import com.ssafy.petpal.room.entity.Room;
import com.ssafy.petpal.room.service.RoomService;
import lombok.RequiredArgsConstructor;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

import java.util.ArrayList;
import java.util.List;
import java.util.Map;

@RestController
@RequiredArgsConstructor
@RequestMapping("/api/v1/rooms")
public class RoomController {
    static String[] STR_ARR = {"거실","주방","침실1","침실2","침실3","화장실"};
    private final RoomService roomService;

    @PostMapping
    public ResponseEntity<Void> postRoom(@RequestBody RoomRegisterDTO roomRegisterDTO){
        try{
            roomService.createRoom(roomRegisterDTO);
            return ResponseEntity.ok(null);
        }catch (Exception e) {
            return ResponseEntity.status(HttpStatus.INTERNAL_SERVER_ERROR).build();
        }
    }

    @GetMapping("/default")
    public ResponseEntity<String[]> getDefaultRooms(){
        return ResponseEntity.ok(STR_ARR);
    }

    @GetMapping("/{homeId}")
    public ResponseEntity<List<RoomResponseDTO>> getRooms(@PathVariable Long homeId){
        try{
            List<RoomResponseDTO> list = roomService.fetchAllRoomById(homeId);
            return ResponseEntity.ok(list);
        }catch (Exception e){
            return ResponseEntity.status(HttpStatus.INTERNAL_SERVER_ERROR).build();
        }
    }
}
