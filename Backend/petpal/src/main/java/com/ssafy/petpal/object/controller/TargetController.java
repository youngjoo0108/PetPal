package com.ssafy.petpal.object.controller;

import com.ssafy.petpal.object.dto.TargetRegisterDto;
import com.ssafy.petpal.object.service.TargetService;
import lombok.RequiredArgsConstructor;
import lombok.extern.slf4j.Slf4j;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

@RestController
@Slf4j
@RequiredArgsConstructor
@RequestMapping("/api/v1/targets")
public class TargetController {
    private final TargetService objectService;
    @PostMapping
    public ResponseEntity<Void> postObject(@RequestBody TargetRegisterDto targetRegisterDto){
        log.info("Successfully parse Coordinate value if this is not null: "+targetRegisterDto.getCoordinate().getX());
        objectService.createTarget(targetRegisterDto);

        return ResponseEntity.ok(null);
    }
}
