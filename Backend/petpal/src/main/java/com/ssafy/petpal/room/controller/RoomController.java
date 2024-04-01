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
    static String[] STR_ARR = {"거실","주방","침실","화장실"};
    private final RoomService roomService;

    @PostMapping
    public ResponseEntity<Void> postRoom(@RequestBody RoomRegisterDTO roomRegisterDTO){
        try{
            String newRoomName = roomRegisterDTO.getRoomName();
            List<RoomResponseDTO> list = roomService.fetchAllRoomById(roomRegisterDTO.getHomeId());
            boolean isDuplicate = false;
            for(RoomResponseDTO dto : list){
                if(dto.getRoomName().equals(newRoomName)){
                    isDuplicate = true;
                    break;
                }
            }
            if(isDuplicate){
                // 중복이 발생했을 경우의 로직
                throw new IllegalArgumentException("중복된 방 이름입니다.");
            } else {
                // 중복이 없을 경우의 로직, 예를 들어 새로운 방을 추가하는 로직 등
                roomService.createRoom(roomRegisterDTO);
                return ResponseEntity.ok(null);
            }


        }catch (IllegalArgumentException e){
            return ResponseEntity.status(HttpStatus.CONFLICT).build();
        }
        catch (Exception e) {
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
            System.out.println(list.get(0).getRoomName());
            return ResponseEntity.ok(list);
        }catch (Exception e){
            return ResponseEntity.status(HttpStatus.INTERNAL_SERVER_ERROR).build();
        }
    }
}
