package com.ssafy.petpal.room.dto;


import com.ssafy.petpal.room.entity.Room;
import lombok.AllArgsConstructor;
import lombok.Builder;
import lombok.Data;
import lombok.Getter;

//@Builder
@AllArgsConstructor
//@Getter
@Data
public class RoomResponseDTO {

    private Long roomId;

    private String roomName;

//    public RoomResponseDTO of(Room room){
//        return RoomResponseDTO.builder()
//                .id(room.getId())
//                .roomName(room.getRoomName())
//                .build();
//    }
}
