package com.ssafy.petpal.schedule.dto;

import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.Getter;

import java.time.LocalTime;
@Data
@AllArgsConstructor
@Getter
public class ScheduleResponseDto {

    private Long applianceId;

    private String day;
    private LocalTime time;
    private String taskType;

    private boolean isRepeat;
    private boolean isActive; // 스케줄 자체의 상태
}
