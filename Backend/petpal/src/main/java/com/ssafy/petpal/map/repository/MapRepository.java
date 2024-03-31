package com.ssafy.petpal.map.repository;

import com.ssafy.petpal.map.entity.Map;
import org.springframework.data.jpa.repository.JpaRepository;
import java.util.Optional;

public interface MapRepository extends JpaRepository<Map, Long> {
    Optional<Map> findByHomeId(Long homeId);
}
