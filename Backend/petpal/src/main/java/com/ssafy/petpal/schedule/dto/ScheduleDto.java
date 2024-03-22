package com.ssafy.petpal.schedule.dto;

import lombok.Getter;
import lombok.Setter;

@Getter
@Setter
public class ScheduleDto {
    private String room;
    private String appliance;
    private String date;
    private String time;
    private String action;
    private boolean isActive;
}