package com.ssafy.petpal.object.dto;

import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.Getter;

@Data
@Getter
public class ApplianceResponseDto {

    // roomName(roomId), applianceType(applianceId), applianceStatus
    private Long applianceId;

    private String applianceType;

    private Integer applianceStatus;

    private Long homeId;

    private Long roomId;

    private String roomName;

    public void setApplianceStatus(int status){
        this.applianceStatus = status;
    }

    public ApplianceResponseDto(Long applianceId, String applianceType, Long homeId, Long roomId, String roomName) {
        this.applianceId = applianceId;
        this.applianceType = applianceType;
        this.applianceStatus = null;
        this.homeId = homeId;
        this.roomId = roomId;
        this.roomName = roomName;
    }
}
