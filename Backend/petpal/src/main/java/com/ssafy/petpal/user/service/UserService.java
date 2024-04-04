package com.ssafy.petpal.user.service;

import com.ssafy.petpal.user.dto.UserDto;
import com.ssafy.petpal.user.entity.User;
import com.ssafy.petpal.user.repository.UserRepository;
import lombok.RequiredArgsConstructor;
import org.springframework.stereotype.Service;

import java.util.Optional;

@RequiredArgsConstructor
@Service
public class UserService {
    private final UserRepository userRepository;

    public void save(UserDto userDto){
        User user = User.builder()
                .userId(userDto.getId())
                .nickname(userDto.getNickname())
                .platform(userDto.getPlatform())
                .refreshToken(userDto.getRefreshToken())
                .fcmToken(userDto.getFcmToken())
                .build();
        userRepository.save(user);
    }

    public Optional<UserDto> findById(Long userId){
        // 엔티티를 DTO로 변환하여 반환
        return userRepository.findByUserId(userId)
                .map(user -> new UserDto(user.getUserId(), user.getNickname(), user.getPlatform(), user.getRefreshToken(), user.getFcmToken()));
    }

    public UserDto findByRefreshToken(String refreshToken){
        // 엔티티를 DTO로 변환하여 반환
        User user = userRepository.findByRefreshToken(refreshToken);
        return new UserDto(user.getUserId(), user.getNickname(), user.getPlatform(), user.getRefreshToken(), user.getFcmToken());
    }

    public void update(UserDto userDto){
        User user = userRepository.findByUserId(userDto.getId())
                .orElseThrow(() -> new RuntimeException("User not found"));
        user.setNickname(userDto.getNickname());
        user.setPlatform(userDto.getPlatform());
        user.setRefreshToken(userDto.getRefreshToken());
        user.setFcmToken(userDto.getFcmToken());
        userRepository.save(user);
    }

    public void updateRefreshToken(UserDto userDto){
        User user = userRepository.findByUserId(userDto.getId())
                .orElseThrow(() -> new RuntimeException("User not found"));
        user.setRefreshToken(userDto.getRefreshToken());
        userRepository.save(user);
    }

    public void updateFCMToken(Long userId, String fcmToken){
        User user = userRepository.findByUserId(userId)
                .orElseThrow(() -> new RuntimeException("User not found"));
        user.setFcmToken(fcmToken);
        userRepository.save(user);
    }
}
