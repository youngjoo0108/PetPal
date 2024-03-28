package com.ssafy.petpal.notification.dto;

import lombok.Builder;
import lombok.Getter;
import lombok.NoArgsConstructor;

@Getter
@NoArgsConstructor
public class NotificationRequestDto {
    private Long targetUserId;
    private String category;
    private String content;
    private String time;
    private String image;

    @Builder
    public NotificationRequestDto(Long targetUserId, String category, String content, String time, String image){
        this.targetUserId = targetUserId;
        this.category = category;
        this.content = content;
        this.time = time;
        this.image = image;
    }
}
