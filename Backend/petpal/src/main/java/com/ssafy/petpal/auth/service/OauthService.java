package com.ssafy.petpal.auth.service;

import com.ssafy.petpal.exception.CustomException;
import com.ssafy.petpal.exception.ErrorCode;
import com.ssafy.petpal.user.dto.UserDto;
import com.ssafy.petpal.user.service.UserService;
import jakarta.servlet.http.HttpServletResponse;
import lombok.RequiredArgsConstructor;
import org.springframework.stereotype.Service;

@RequiredArgsConstructor
@Service
public class OauthService {
    private final UserService userService;
    private final JwtTokenService jwtTokenService;
    private final KakaoOauthService kakaoOauthService;

    //카카오 로그인
    public String loginWithKakao(String accessToken, HttpServletResponse response) {
        UserDto userDto = kakaoOauthService.getUserProfileByToken(accessToken);
        return getTokens(userDto.getId(), response);
    }

    //access Token, refresh Token 생성
    public String getTokens(Long id, HttpServletResponse response) {
        final String accessToken = jwtTokenService.createAccessToken(id.toString());
        final String refreshToken = jwtTokenService.createRefreshToken();

        UserDto userDto = userService.findById(id)
                .orElseThrow(() -> new CustomException(ErrorCode.NOT_EXIST_USER));

        userDto.setRefreshToken(refreshToken);
        userService.updateRefreshToken(userDto);

        jwtTokenService.addRefreshTokenToCookie(refreshToken, response);
        return accessToken;
    }

    // refresh Token -> access Token 새로 갱신
    public String refreshAccessToken(String refreshToken) {
        UserDto userDto = userService.findByRefreshToken(refreshToken);
        if(userDto == null) {
            throw new CustomException(ErrorCode.INVALID_REFRESH_TOKEN);
        }

        if(!jwtTokenService.validateToken(refreshToken)) {
            throw new CustomException(ErrorCode.INVALID_REFRESH_TOKEN);
        }

        return jwtTokenService.createAccessToken(userDto.getId().toString());
    }
}
