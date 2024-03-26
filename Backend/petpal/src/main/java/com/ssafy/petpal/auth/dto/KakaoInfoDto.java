package com.ssafy.petpal.auth.dto;

import lombok.AllArgsConstructor;
import lombok.Getter;

import java.util.Map;

@Getter
@AllArgsConstructor
public class KakaoInfoDto {
    private Long id;
    private String nickname;

    public KakaoInfoDto(Map<String, Object> attributes) {
        this.id = Long.valueOf(attributes.get("id").toString());
        Map<String, Object> properties = (Map<String, Object>) attributes.get("properties");
        this.nickname = properties != null ? properties.get("nickname").toString() : "";
    }
}
