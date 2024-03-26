package com.ssafy.petpal.auth.controller;

import com.ssafy.petpal.auth.dto.OauthRequestDto;
import com.ssafy.petpal.auth.dto.OauthResponseDto;
import com.ssafy.petpal.auth.dto.RefreshTokenResponseDto;
import com.ssafy.petpal.auth.service.OauthService;
import com.ssafy.petpal.exception.CustomException;
import com.ssafy.petpal.exception.ErrorCode;
import jakarta.servlet.http.Cookie;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;
import lombok.RequiredArgsConstructor;
import lombok.extern.slf4j.Slf4j;
import org.springframework.web.bind.annotation.*;

import java.util.*;

@Slf4j
@RestController
@RequiredArgsConstructor
@RequestMapping("/api/v1")
public class OauthController {

    private final OauthService oauthService;

    @PostMapping("/login/oauth/{provider}")
    public OauthResponseDto login(@PathVariable String provider, @RequestBody OauthRequestDto oauthRequestDto,
                                  HttpServletResponse response) {
        log.error("[ExceptionHandlerFilter] errMsg : " + oauthRequestDto.getAccessToken());
        OauthResponseDto oauthResponseDto = new OauthResponseDto();
        switch (provider) {
            case "kakao":
                String[] arr = oauthService.loginWithKakao(oauthRequestDto.getAccessToken());
                oauthResponseDto.setAccessToken(arr[0]);
                oauthResponseDto.setRefreshToken(arr[1]);
        }
        return oauthResponseDto;
    }

    // refresh Token -> access Token 재발급
    @PostMapping("/token/refresh")
    public RefreshTokenResponseDto tokenRefresh(HttpServletRequest request) {
        RefreshTokenResponseDto refreshTokenResponseDto = new RefreshTokenResponseDto();
        Cookie[] list = request.getCookies();
        if(list == null) {
            throw new CustomException(ErrorCode.INVALID_REFRESH_TOKEN);
        }

        Cookie refreshTokenCookie = Arrays.stream(list).filter(cookie -> cookie.getName().equals("refresh_token")).toList().get(0);

        if(refreshTokenCookie == null) {
            throw new CustomException(ErrorCode.INVALID_REFRESH_TOKEN);
        }
        String accessToken = oauthService.refreshAccessToken(refreshTokenCookie.getValue());
        refreshTokenResponseDto.setAccessToken(accessToken);
        return refreshTokenResponseDto;
    }
}
