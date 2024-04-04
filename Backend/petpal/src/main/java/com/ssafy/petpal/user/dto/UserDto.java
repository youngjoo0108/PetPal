package com.ssafy.petpal.user.dto;

import lombok.*;

@Getter
@Setter
@Builder
@ToString
@AllArgsConstructor
public class UserDto {
    private Long id;
    private String nickname;
    private String platform;
    private String refreshToken;

    private String fcmToken;
}
