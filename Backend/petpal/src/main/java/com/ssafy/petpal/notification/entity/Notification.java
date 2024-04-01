package com.ssafy.petpal.notification.entity;

import jakarta.persistence.*;
import lombok.Getter;
import lombok.NoArgsConstructor;
import lombok.Setter;

@Entity
@Table(name = "Notifications")
@Getter
@Setter
@NoArgsConstructor // Lombok을 사용하여 기본 생성자를 생성
public class Notification {
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Long id;

    private Long targetUserId;
    private String category;
    private String content;
    private String time;
    private String image;

    // 모든 필드를 초기화하는 생성자 직접 정의
    public Notification(Long targetUserId, String category, String content, String time, String image) {
        this.targetUserId = targetUserId;
        this.category = category;
        this.content = content;
        this.time = time;
        this.image = image;
    }
}
