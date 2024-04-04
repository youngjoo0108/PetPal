package com.ssafy.petpal.map.repository;

import com.ssafy.petpal.map.entity.OriginMap;
import org.springframework.data.jpa.repository.JpaRepository;

import java.util.Optional;

public interface OriginMapRepository extends JpaRepository<OriginMap, Long> {
    Optional<OriginMap> findByHomeId(Long homeId);
}
