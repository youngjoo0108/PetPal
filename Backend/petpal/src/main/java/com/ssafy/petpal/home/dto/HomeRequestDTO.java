package com.ssafy.petpal.home.dto;

import lombok.Data;
import lombok.Getter;

@Data
@Getter
public class HomeRequestDTO {

    private Long userId;

    private String homeNickname;

}
