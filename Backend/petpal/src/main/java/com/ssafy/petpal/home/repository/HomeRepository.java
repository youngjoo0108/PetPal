package com.ssafy.petpal.home.repository;

import com.ssafy.petpal.home.entity.Home;
import org.springframework.data.jpa.repository.JpaRepository;

import java.util.List;
import java.util.Optional;

public interface HomeRepository extends JpaRepository<Home,Long> {
    List<Home> findByKakaoId(Long userId);
    Optional<Home> findById(Long homeId);
}
