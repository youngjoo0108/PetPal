package com.ssafy.petpal.image.controller;

import com.ssafy.petpal.image.service.ImageService;
import lombok.RequiredArgsConstructor;
import lombok.extern.slf4j.Slf4j;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;
import org.springframework.web.multipart.MultipartFile;

import java.io.IOException;

@RestController
@Slf4j
@RequiredArgsConstructor
@RequestMapping("/api/image")
public class ImageController {


    /* 터틀봇에서 카메라로 오브젝트 사진 생성 요청을 먼저 한다.
    *  반환 값으로 Object 생성 api 요청
    * */
    private final ImageService imageService;
    @PostMapping
    public ResponseEntity<Long> postImage(@RequestParam("file") MultipartFile file, String homeID ) {


        log.info("Starting upload..");
        try {
            // s3 업로드
            String s3URL = imageService.uploadFile(file);
            // db 저장
            Long imageId = imageService.createImage(s3URL,file);
            return ResponseEntity.ok(imageId);
        } catch ( IOException e) {
            e.printStackTrace();
            return ResponseEntity.status(HttpStatus.INTERNAL_SERVER_ERROR).build();
        }
    }
}
