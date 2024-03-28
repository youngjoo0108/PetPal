package com.ssafy.petpal.image.controller;

import com.amazonaws.HttpMethod;
import com.ssafy.petpal.image.dto.ImageResponseDTO;
import com.ssafy.petpal.image.service.ImageService;
import lombok.RequiredArgsConstructor;
import lombok.extern.slf4j.Slf4j;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

import java.util.UUID;

@RestController
@Slf4j
@RequiredArgsConstructor
@RequestMapping("/api/v1/images")
public class ImageController {


    /* 터틀봇에서 카메라로 오브젝트 사진 생성 요청을 먼저 한다.
    *  반환 값으로 Object 생성 api 요청
    * */
    private final ImageService imageService;
//    @PostMapping
//    public ResponseEntity<Long> postImage(@RequestParam("file") MultipartFile file, String homeID ) {
//
//        log.info("Starting upload..");
//        try {
//            // s3 업로드
//            String s3URL = imageService.uploadFile(file);
//            // db 저장
//            Long imageId = imageService.createImage(s3URL,file);
//            return ResponseEntity.ok(imageId);
//        } catch ( IOException e) {
//            e.printStackTrace();
//            return ResponseEntity.status(HttpStatus.INTERNAL_SERVER_ERROR).build();
//        }
//    }

    @PostMapping
    public ResponseEntity<ImageResponseDTO> postImage(@RequestParam String extension){
        // 실제 s3에 저장될 객체의 이름
        String filename = UUID.randomUUID()+"."+extension;
        // 해당 객체에 대한 UPLOAD만을 위한 URL 생성
        String uploadURL = imageService.generateURL(filename,HttpMethod.PUT);

        // 해당 객체이름으로 Image 테이블에 추가
        Long imageId = imageService.createImage(filename);
        // ROS2 파트에서
        // 1. Object 생성 요청 시 사용할 "imageId"와
        // 2. s3업로드에 사용할 "uploadURL" 묶어서 반환
        return ResponseEntity.ok(new ImageResponseDTO(imageId,uploadURL));
    }

    /* 어차피 푸시알림 보내줄 때에 presigned 발급해서 알림에 함께 보내주면 되니까
    *  controller에 구현하는 것보단 "service단에 구현"해서 내부적으로 notification 로직에서 사용하도록 하는 것이 적합
    * */
    @GetMapping
    public ResponseEntity<String> getPreSignedDownloadURL(@RequestParam("filename") String filename){
        String downloadURL = imageService.generateURL(filename, HttpMethod.GET);
        return ResponseEntity.ok(downloadURL);
    }
}
