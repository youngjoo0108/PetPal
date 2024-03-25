package com.ssafy.petpal.object.controller;

import com.ssafy.petpal.object.dto.ObjectRegisterDto;
import com.ssafy.petpal.object.service.ObjectService;
import lombok.RequiredArgsConstructor;
import lombok.extern.slf4j.Slf4j;
import org.springframework.http.ResponseEntity;
import org.springframework.messaging.handler.annotation.Payload;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

@RestController
@Slf4j
@RequiredArgsConstructor
@RequestMapping("/api/v1/object")
public class ObjectController {
    private final ObjectService objectService;
    @PostMapping
    public ResponseEntity<Void> postObject(@RequestBody ObjectRegisterDto objectRegisterDto){
        log.info("Successfully parse Coordinate value if this is not null: "+objectRegisterDto.getCoordinate().getX());
        objectService.createObject(objectRegisterDto);
        return ResponseEntity.ok(null);
    }
}
