package com.ssafy.petpal.user.controller;

import com.ssafy.petpal.auth.utils.SecurityUtil;
import com.ssafy.petpal.exception.CustomException;
import com.ssafy.petpal.exception.ErrorCode;
import com.ssafy.petpal.user.dto.UserDto;
import com.ssafy.petpal.user.service.UserService;
import lombok.RequiredArgsConstructor;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

@RestController
@RequiredArgsConstructor
@RequestMapping("/api/v1/user")
public class UserController {
    private final UserService userService;

    // 유저정보 조회 API
    @GetMapping("/info")
    public UserDto info() {
        final long userId = SecurityUtil.getCurrentUserId();
        UserDto userDto = userService.findById(userId)
                .orElseThrow(() -> new CustomException(ErrorCode.NOT_EXIST_USER));

        if(userDto == null) {
            throw new CustomException(ErrorCode.NOT_EXIST_USER);
        }
        return userDto;
    }
}
