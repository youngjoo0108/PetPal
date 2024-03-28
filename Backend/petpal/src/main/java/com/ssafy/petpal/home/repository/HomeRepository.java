package com.ssafy.petpal.home.repository;

import com.ssafy.petpal.home.entity.Home;
import org.springframework.data.jpa.repository.JpaRepository;

public interface HomeRepository extends JpaRepository<Home,Long> {
}
