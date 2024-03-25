package com.ssafy.petpal.user.repository;

import com.ssafy.petpal.user.entity.User;
import org.springframework.data.jpa.repository.JpaRepository;

import java.util.Optional;

public interface UserRepository extends JpaRepository<User, Long> {
    User findByRefreshToken(String refreshToken);

    Optional<User> findByUserId(Long userId);

    // JPA에서는 save 메소드를 통해 엔티티를 저장하거나 업데이트합니다.
    // 별도의 update 메소드를 정의할 필요가 없습니다.
}
