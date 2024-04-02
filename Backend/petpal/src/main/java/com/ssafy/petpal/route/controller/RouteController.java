package com.ssafy.petpal.route.controller;

import com.ssafy.petpal.route.dto.RouteDto;
import com.ssafy.petpal.route.service.RouteService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

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

    @PostMapping
    public ResponseEntity<RouteDto> saveRoute(@RequestParam("homeId") String homeId, @RequestBody String data) {
        try {
            RouteDto savedRouteDto = routeService.saveRoute(homeId, data);
            return new ResponseEntity<>(savedRouteDto, HttpStatus.CREATED);
        } catch (Exception e) {
            // 예외 처리 로직 (예: 로깅)
            return ResponseEntity.status(HttpStatus.INTERNAL_SERVER_ERROR).build();
        }
    }
}
