package com.ssafy.petpal.home.service;

import com.ssafy.petpal.home.dto.HomeRequestDTO;
import com.ssafy.petpal.home.entity.Home;
import com.ssafy.petpal.home.repository.HomeRepository;
import com.ssafy.petpal.user.entity.User;
import com.ssafy.petpal.user.repository.UserRepository;
import lombok.RequiredArgsConstructor;
import org.springframework.stereotype.Service;

import java.util.List;

@Service
@RequiredArgsConstructor
public class HomeService {

    private final HomeRepository homeRepository;
    private final UserRepository userRepository;

    public void createHome(HomeRequestDTO homeRequestDTO) {
        User user = userRepository.findByUserId(homeRequestDTO.getUserId())
                .orElseThrow(IllegalArgumentException::new);
        Home home = Home.builder()
                .homeNickname(homeRequestDTO.getHomeNickname())
                .user(user)
                .build();
        homeRepository.save(home);
    }

    public List<Home> fetchAllByUserId(Long userId) {
        return homeRepository.findByUserId(userId);
    }
}
