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
                .id(userDto.getId())
                .email(userDto.getEmail())
                .platform(userDto.getPlatform())
                .refreshToken(userDto.getRefreshToken())
                .build();
        userRepository.save(user);
    }

    public Optional<UserDto> findById(Long userId){
        // 엔티티를 DTO로 변환하여 반환
        return userRepository.findById(userId)
                .map(user -> new UserDto(user.getId(), user.getEmail(), user.getPlatform(), user.getRefreshToken()));
    }

    public UserDto findByRefreshToken(String refreshToken){
        // 엔티티를 DTO로 변환하여 반환
        User user = userRepository.findByRefreshToken(refreshToken);
        return new UserDto(user.getId(), user.getEmail(), user.getPlatform(), user.getRefreshToken());
    }

    public void update(UserDto userDto){
        User user = userRepository.findById(userDto.getId())
                .orElseThrow(() -> new RuntimeException("User not found"));
        user.setEmail(userDto.getEmail());
        user.setPlatform(userDto.getPlatform());
        user.setRefreshToken(userDto.getRefreshToken());
        userRepository.save(user);
    }

    public void updateRefreshToken(UserDto userDto){
        User user = userRepository.findById(userDto.getId())
                .orElseThrow(() -> new RuntimeException("User not found"));
        user.setRefreshToken(userDto.getRefreshToken());
        userRepository.save(user);
    }
}
