package com.ssafy.petpal.image.dto;

import lombok.AllArgsConstructor;
import lombok.Getter;
import lombok.RequiredArgsConstructor;

@Getter
@AllArgsConstructor
public class ImageResponseDTO {

    private Long imageId;
    private String presignedURL;

}
