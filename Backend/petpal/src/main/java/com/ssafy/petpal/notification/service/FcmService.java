package com.ssafy.petpal.notification.service;

import com.ssafy.petpal.notification.dto.NotificationRequestDto;
import org.springframework.stereotype.Service;

import java.io.IOException;

@Service
public interface FcmService {
    int sendMessageTo(NotificationRequestDto notificationRequestDto) throws IOException;
}
