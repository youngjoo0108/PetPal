package com.ssafy.petpal.route.controller;

import com.ssafy.petpal.route.dto.RouteDto;
import com.ssafy.petpal.route.service.RouteService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

@RestController
@RequestMapping("/api/v1/routes")
public class RouteController {

    private final RouteService routeService;

    @Autowired
    public RouteController(RouteService routeService) {
        this.routeService = routeService;
    }

    @GetMapping("/{homeId}")
    public ResponseEntity<RouteDto> getRouteByHomeId(@PathVariable String homeId) {
        try {
            RouteDto routeDto = routeService.getRoute(homeId);
            return ResponseEntity.ok(routeDto);
        } catch (RuntimeException ex) {
            // 예외 처리: 해당 homeId로 루트를 찾을 수 없는 경우
            return ResponseEntity.notFound().build();
        }
    }
}
