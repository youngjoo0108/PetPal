package com.ssafy.petpal.notification.service;

import com.fasterxml.jackson.core.JsonProcessingException;
import com.fasterxml.jackson.databind.ObjectMapper;
import com.google.auth.oauth2.GoogleCredentials;
import com.google.firebase.FirebaseApp;
import com.google.firebase.FirebaseOptions;
import com.google.firebase.messaging.FirebaseMessaging;
import com.ssafy.petpal.notification.dto.FcmMessageDto;
import com.ssafy.petpal.notification.dto.NotificationRequestDto;
import com.ssafy.petpal.notification.service.FcmService;
import com.ssafy.petpal.user.dto.UserDto;
import com.ssafy.petpal.user.service.UserService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.*;
import org.springframework.stereotype.Service;
import org.springframework.web.client.RestTemplate;

import java.io.IOException;
import java.util.Optional;

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

        HttpEntity entity = new HttpEntity<>(message, headers);

        String API_URL = "<https://fcm.googleapis.com/v1/projects/petpal-d6248/messages:send>";
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

        // Optional에서 토큰 추출하기. 값이 없으면 기본값으로 ""(빈 문자열) 사용
        String token = userDtoOptional.map(UserDto::getFcmToken).orElse("");

        ObjectMapper om = new ObjectMapper();
        FcmMessageDto fcmMessageDto = FcmMessageDto.builder()
                .message(FcmMessageDto.Message.builder()
                        .token(token)
                        .notification(FcmMessageDto.Notification.builder()
                                .title("띵동")
                                .body("ROS에서 보낸 메시지가 있습니다.")
                                .category(notificationRequestDto.getCategory())
                                .content(notificationRequestDto.getContent())
                                .time(notificationRequestDto.getTime())
                                .image(notificationRequestDto.getImage())
                                .build()
                        ).build()).validateOnly(false).build();

        return om.writeValueAsString(fcmMessageDto);
    }
}
