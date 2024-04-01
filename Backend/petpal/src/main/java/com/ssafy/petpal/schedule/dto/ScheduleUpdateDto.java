package com.ssafy.petpal.schedule.dto;

import lombok.*;

import java.time.LocalDate;
import java.time.LocalTime;

@Getter
@Setter
@ToString
@AllArgsConstructor
@Data
public class ScheduleUpdateDto {
    private Long roomId;
    private Long applianceId;

    private LocalDate day;  // YYYY-MM-DD 형식 String
    private LocalTime time; // HH-MM 형식 String
    private String taskType; //  "ON" | "OFF" String

    private boolean isActive;// boolean(일단 무조건 true로 보냄)
}
