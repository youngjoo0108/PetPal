package com.ssafy.petpal.route.repository;

import com.ssafy.petpal.route.entity.Route;
import org.springframework.data.jpa.repository.JpaRepository;

public interface RouteRepository extends JpaRepository<Route, Long> {
}
