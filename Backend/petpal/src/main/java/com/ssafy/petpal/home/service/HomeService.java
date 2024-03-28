package com.ssafy.petpal.home.service;

import com.ssafy.petpal.home.repository.HomeRepository;
import lombok.RequiredArgsConstructor;
import org.springframework.stereotype.Service;

@Service
@RequiredArgsConstructor
public class HomeService {

    private final HomeRepository homeRepository;


    public void createHome() {

    }
}
