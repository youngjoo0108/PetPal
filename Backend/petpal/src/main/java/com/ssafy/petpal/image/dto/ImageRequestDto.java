package com.ssafy.petpal.image.dto;

import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.Getter;

@Data
@Getter
@AllArgsConstructor
public class ImageRequestDto {

    Long homeId;
    String extension;

}
