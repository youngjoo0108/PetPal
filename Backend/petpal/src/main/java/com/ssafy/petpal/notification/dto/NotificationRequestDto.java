package com.ssafy.petpal.notification.dto;

import lombok.Builder;
import lombok.Getter;
import lombok.NoArgsConstructor;

@Getter
@NoArgsConstructor
public class NotificationRequestDto {
    private Long targetUserId;
    private String category; //ㅇㅇㅇ... 분류 : 위험 요소 처리, 가전제어
    private String content; // 콘텐츠는 동작에 대한 설명
    private String time; // 로컬 타임
    private String image; // S3 다운로드 Url

    @Builder
    public NotificationRequestDto(Long targetUserId, String category, String content, String time, String image){
        this.targetUserId = targetUserId;
        this.category = category;
        this.content = content;
        this.time = time;
        this.image = image;
    }
}
