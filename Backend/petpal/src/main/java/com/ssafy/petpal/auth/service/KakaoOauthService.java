package com.ssafy.petpal.auth.service;

import com.ssafy.petpal.auth.dto.KakaoInfoDto;
import com.ssafy.petpal.auth.filter.JwtFilter;
import com.ssafy.petpal.user.dto.UserDto;
import com.ssafy.petpal.user.service.UserService;
import lombok.extern.slf4j.Slf4j;
import org.springframework.core.ParameterizedTypeReference;
import org.springframework.stereotype.Service;
import org.springframework.web.reactive.function.client.WebClient;

import java.util.Map;
@Service
@Slf4j
public class KakaoOauthService {
    private final UserService userService;
    public KakaoOauthService(UserService userService) {
        this.userService = userService;
    }

    // 카카오Api 호출해서 AccessToken으로 유저정보 가져오기
    public Map<String, Object> getUserAttributesByToken(String accessToken){
        return WebClient.create()
                .get()
                .uri("https://kapi.kakao.com/v2/user/me")
                .headers(httpHeaders -> httpHeaders.setBearerAuth(accessToken.substring(7)))
                .retrieve()
                .bodyToMono(new ParameterizedTypeReference<Map<String, Object>>() {})
                .block();
    }

    // 카카오API에서 가져온 유저정보를 DB에 저장
    public UserDto getUserProfileByToken(String accessToken){
        Map<String, Object> userAttributesByToken = getUserAttributesByToken(accessToken);
        KakaoInfoDto kakaoInfoDto = new KakaoInfoDto(userAttributesByToken);
        UserDto userDto = UserDto.builder()
                .id(kakaoInfoDto.getId())
                .nickname(kakaoInfoDto.getNickname())
                .platform("kakao")
                .build();
        if(userService.findById(userDto.getId()).isPresent()) {
            userService.update(userDto);
        } else {
            userService.save(userDto);
        }
        return userDto;
    }

}
