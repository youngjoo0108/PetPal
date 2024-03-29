package com.ssafy.petpal.user.entity;

import com.ssafy.petpal.common.BaseEntity;
import jakarta.persistence.*;
import lombok.*;

@Entity
@Table(name = "Users")
@Getter
@Setter
@NoArgsConstructor
@AllArgsConstructor
@Builder
public class User extends BaseEntity {

    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Long id;

    private Long userId;
    private String nickname;
    private String platform;
    private String refreshToken;

    private String fcmToken;
}
