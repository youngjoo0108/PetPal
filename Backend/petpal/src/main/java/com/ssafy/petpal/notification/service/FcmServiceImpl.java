package com.ssafy.petpal.notification.service;

import com.fasterxml.jackson.core.JsonProcessingException;
import com.fasterxml.jackson.databind.ObjectMapper;
import com.google.auth.oauth2.GoogleCredentials;
import com.google.firebase.FirebaseApp;
import com.google.firebase.FirebaseOptions;
import com.google.firebase.messaging.FirebaseMessaging;
import com.ssafy.petpal.image.service.ImageService;
import com.ssafy.petpal.notification.dto.FcmMessageDto;
import com.ssafy.petpal.notification.dto.NotificationRequestDto;
import com.ssafy.petpal.notification.service.FcmService;
import com.ssafy.petpal.user.dto.UserDto;
import com.ssafy.petpal.user.service.UserService;
import lombok.extern.slf4j.Slf4j;
import org.apache.commons.lang3.StringEscapeUtils;
import org.checkerframework.checker.units.qual.A;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.*;
import org.springframework.stereotype.Service;
import org.springframework.web.client.RestTemplate;

import java.io.IOException;
import java.util.Map;
import java.util.Optional;

@Slf4j
@Service
public class FcmServiceImpl implements FcmService {
    @Autowired
    private GoogleCredentials googleCredentials;

    @Autowired
    private UserService userService;


    @Override
    public int sendMessageTo(NotificationRequestDto notificationRequestDto) throws IOException {
        String message = makeMessage(notificationRequestDto);
        RestTemplate restTemplate = new RestTemplate();

        HttpHeaders headers = new HttpHeaders();
        headers.setContentType(MediaType.APPLICATION_JSON);

        headers.set("Authorization", "Bearer " + getAccessToken());
        log.info(headers.get("Authorization").toString() + " ");

        HttpEntity entity = new HttpEntity<>(message, headers);

        String API_URL = "https://fcm.googleapis.com/v1/projects/petpal-d6248/messages:send";
        ResponseEntity response = restTemplate.exchange(API_URL, HttpMethod.POST, entity, String.class);

        System.out.println(response.getStatusCode());

        return response.getStatusCode() == HttpStatus.OK ? 1 : 0;
    }

    private String getAccessToken() throws IOException {
        googleCredentials.refreshIfExpired();
        return googleCredentials.getAccessToken().getTokenValue();
    }
    private String makeMessage(NotificationRequestDto notificationRequestDto) throws JsonProcessingException {
        Optional<UserDto> userDtoOptional = userService.findById(notificationRequestDto.getTargetUserId());
        String token = userDtoOptional.map(UserDto::getFcmToken).orElse("");

        ObjectMapper om = new ObjectMapper();
        FcmMessageDto fcmMessageDto = FcmMessageDto.builder()
                .validateOnly(false)
                .message(FcmMessageDto.Message.builder()
                        .token(token)
                        .notification(FcmMessageDto.Notification.builder()
                                .title("PetPal 알림 도착")
                                .body(notificationRequestDto.getContent())
                                .build())
                        .data(Map.of( // 사용자 정의 데이터
                                "category", notificationRequestDto.getCategory(), // 어떤 동작을 했냐
                                "content", notificationRequestDto.getContent(), // 동작에 대한 설명
                                "time", notificationRequestDto.getTime(), // 로컬 타임
                                "image", notificationRequestDto.getImage() // s3 presigned download url
                        ))
                        .build())
                .build();

        return om.writeValueAsString(fcmMessageDto);
    }
}
