package com.ssafy.petpal.notification.controller;

import com.ssafy.petpal.notification.dto.NotificationRequestDto;
import com.ssafy.petpal.notification.service.FcmService;
import com.ssafy.petpal.notification.service.NotificationService;
import lombok.extern.slf4j.Slf4j;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.validation.annotation.Validated;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

import java.io.IOException;

@Slf4j
@RestController
@RequestMapping("/api/v1/fcm")
public class FcmController {
    private final FcmService fcmService;
    private final NotificationService notificationService;
    public FcmController(FcmService fcmService, NotificationService notificationService){
        this.fcmService = fcmService;
        this.notificationService = notificationService;
    }

    @PostMapping("/send")
    public ResponseEntity<Integer> pushMessage(@RequestBody @Validated NotificationRequestDto notificationRequestDto) throws IOException {
        log.debug("[+] 푸시 메시지를 전송합니다. ");
        int result = fcmService.sendMessageTo(notificationRequestDto);
        notificationService.saveNotification(notificationRequestDto);
        return new ResponseEntity<>(result, HttpStatus.OK);
    }
}
