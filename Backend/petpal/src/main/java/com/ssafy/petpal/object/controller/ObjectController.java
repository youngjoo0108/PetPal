package com.ssafy.petpal.object.controller;

import com.ssafy.petpal.object.dto.ObjectRegisterDto;
import com.ssafy.petpal.object.service.ObjectService;
import lombok.RequiredArgsConstructor;
import org.springframework.http.ResponseEntity;
import org.springframework.messaging.handler.annotation.Payload;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

@RestController
@RequiredArgsConstructor
@RequestMapping("/api/v1/object")
public class ObjectController {
    private final ObjectService objectService;
    @PostMapping
    public ResponseEntity<Void> postObject(@Payload ObjectRegisterDto objectRegisterDto){
        objectService.createObject(objectRegisterDto);
        return ResponseEntity.ok(null);
    }
}
