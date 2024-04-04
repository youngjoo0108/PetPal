package com.ssafy.petpal.room.dto;

import lombok.Data;
import lombok.Getter;

@Data
@Getter
public class RoomRegisterDTO {

    String roomName;
    Long homeId;
}
