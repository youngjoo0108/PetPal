package com.ssafy.petpal.object.dto;

import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.Getter;

@Data
@Getter
public class ApplianceResponseDto {

    // roomName(roomId), applianceType(applianceId), applianceStatus
    private Long applianceId;

    private String applianceUUID;

    private String applianceType;

    private String applianceStatus;

    private Long homeId;

    private Long roomId;

    private String roomName;

    public void setApplianceStatus(String status){
        this.applianceStatus = status;
    }

    public ApplianceResponseDto(Long applianceId, String applianceUUID, String applianceType, Long homeId, Long roomId, String roomName) {
        this.applianceId = applianceId;
        this.applianceUUID = applianceUUID;
        this.applianceType = applianceType;
        this.applianceStatus = null;
        this.homeId = homeId;
        this.roomId = roomId;
        this.roomName = roomName;
    }
}
