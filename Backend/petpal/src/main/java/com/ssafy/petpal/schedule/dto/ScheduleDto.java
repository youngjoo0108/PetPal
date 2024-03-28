package com.ssafy.petpal.schedule.dto;

import lombok.Getter;
import lombok.Setter;

import java.time.LocalTime;

@Getter
@Setter
public class ScheduleDto {
    private Long roomId;
    private Long homeId;

    private Long applianceId;
    private String day;
    private LocalTime time;
    private String taskType;

    private boolean isRepeat;
    private boolean isActive; // 스케줄 자체의 상태
}