package com.ssafy.petpal.control.dto;

import lombok.Getter;
import lombok.Setter;

@Getter
@Setter
public class ControlDto {
    private String type;
    private String sender;
    private String time;
    private Object message;
}
