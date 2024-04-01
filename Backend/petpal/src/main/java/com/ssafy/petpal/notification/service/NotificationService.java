package com.ssafy.petpal.notification.service;

import com.ssafy.petpal.notification.dto.NotificationRequestDto;
import com.ssafy.petpal.notification.entity.Notification;
import com.ssafy.petpal.notification.repository.NotificationRepository;
import lombok.RequiredArgsConstructor;
import org.springframework.stereotype.Service;

import java.util.List;

@Service
@RequiredArgsConstructor
public class NotificationService {
    private final NotificationRepository notificationRepository;

    public List<Notification> findAllNotificationsByUserId(Long userId) {
        return notificationRepository.findByTargetUserId(userId);
    }

    public Notification saveNotification(NotificationRequestDto notificationDto) {
        Notification notification = new Notification(
                notificationDto.getTargetUserId(),
                notificationDto.getCategory(),
                notificationDto.getContent(),
                notificationDto.getTime(),
                notificationDto.getImage()
        );
        return notificationRepository.save(notification);
    }

    public void deleteNotification(Long notificationId) {
        notificationRepository.deleteById(notificationId);
    }
}
