package com.ssafy.petpal.map.controller;

import com.ssafy.petpal.map.dto.MapDto;
import com.ssafy.petpal.map.entity.Map;
import com.ssafy.petpal.map.repository.MapRepository;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

@RestController
@RequestMapping("/api/v1/maps")
public class MapController {
    private final MapRepository mapRepository;

    public MapController(MapRepository mapRepository) {
        this.mapRepository = mapRepository;
    }

    @GetMapping("/{homeId}")
    public ResponseEntity<MapDto> getMapData(@PathVariable Long homeId) {
        return mapRepository.findByHomeId(homeId)
                .map(map -> ResponseEntity.ok(new MapDto(map.getHomeId(), map.getData())))
                .orElseGet(() -> ResponseEntity.notFound().build()); // homeId에 해당하는 Map이 없는 경우 404 Not Found 반환
    }
}
