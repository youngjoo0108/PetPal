package com.ssafy.petpal.notification.repository;

import com.ssafy.petpal.notification.entity.Notification;
import org.springframework.data.jpa.repository.JpaRepository;

import java.util.List;

public interface NotificationRepository extends JpaRepository<Notification, Long> {
    List<Notification> findByTargetUserId(Long targetUserId);
}
