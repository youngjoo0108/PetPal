package com.ssafy.petpal.route.repository;

import com.ssafy.petpal.route.entity.Route;
import org.springframework.data.jpa.repository.JpaRepository;
import java.util.Optional;

public interface RouteRepository extends JpaRepository<Route, Long> {
    Optional<Route> findByMapId(Long mapId);
}
