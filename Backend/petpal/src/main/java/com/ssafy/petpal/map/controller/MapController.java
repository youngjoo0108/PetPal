package com.ssafy.petpal.map.controller;

import com.ssafy.petpal.map.dto.MapDto;
import com.ssafy.petpal.map.dto.OriginMapDto;
import com.ssafy.petpal.map.entity.Map;
import com.ssafy.petpal.map.repository.MapRepository;
import com.ssafy.petpal.map.service.MapService;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

@RestController
@RequestMapping("/api/v1/maps")
public class MapController {
    private final MapService mapService;

    public MapController(MapService mapService) {
        this.mapService = mapService;
    }

    @GetMapping("/{homeId}")
    public ResponseEntity<MapDto> getMapData(@PathVariable Long homeId) {
        try {
            MapDto mapDto = mapService.getMapData(homeId);
            return ResponseEntity.ok(mapDto);
        } catch (RuntimeException ex) {
            return ResponseEntity.notFound().build();
        }
    }

    @PostMapping
    public ResponseEntity<MapDto> saveMapData(@RequestBody MapDto mapDto) {
        try {
            MapDto savedMapDto = mapService.saveMapData(mapDto);
            return ResponseEntity.status(HttpStatus.CREATED).body(savedMapDto);
        } catch (Exception e) {
            return ResponseEntity.status(HttpStatus.INTERNAL_SERVER_ERROR).build();
        }
    }

    @GetMapping("/{homeId}/origin")
    public ResponseEntity<OriginMapDto> getOriginMapData(@PathVariable Long homeId) {
        try {
            OriginMapDto originMapDto = mapService.getOriginMapData(homeId);
            return ResponseEntity.ok(originMapDto);
        } catch (RuntimeException ex) {
            return ResponseEntity.notFound().build();
        }
    }

    @PostMapping("/origin")
    public ResponseEntity<OriginMapDto> saveOriginMapData(@RequestBody OriginMapDto originMapDto) {
        try {
            OriginMapDto savedMapDto = mapService.saveOriginMapData(originMapDto);
            return ResponseEntity.status(HttpStatus.CREATED).body(savedMapDto);
        } catch (Exception e) {
            return ResponseEntity.status(HttpStatus.INTERNAL_SERVER_ERROR).build();
        }
    }
}
