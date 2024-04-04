package com.ssafy.petpal.image.service;

import com.amazonaws.HttpMethod;
import com.amazonaws.services.s3.AmazonS3Client;
import com.amazonaws.services.s3.model.MultipartUpload;
import com.amazonaws.services.s3.model.ObjectMetadata;
import com.ssafy.petpal.image.entity.Image;
import com.ssafy.petpal.image.repository.ImageRepository;
import lombok.RequiredArgsConstructor;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.stereotype.Service;
import org.springframework.web.multipart.MultipartFile;

import java.io.IOException;
import java.net.URL;
import java.util.Calendar;
import java.util.Date;
import java.util.UUID;

@Service
@RequiredArgsConstructor
public class ImageService {
    private final AmazonS3Client amazonS3Client;
    private final ImageRepository imageRepository;
    @Value("${cloud.aws.s3.bucket}")
    private String bucket;
/* MultiPartFile 받아서 올릴 때.. 현재 사용 안 함 */
//    public String uploadFile(MultipartFile file) throws IOException {
//
//        String fileName= "image/" + UUID.randomUUID() +  file.getOriginalFilename();
//        String fileUrl= "https://" + bucket + "/test" +fileName;
//        ObjectMetadata metaData= new ObjectMetadata();
//        metaData.setContentType(file.getContentType());
//        metaData.setContentLength(file.getSize());
//        amazonS3Client.putObject(bucket,fileName,file.getInputStream(),metaData);
//        return fileUrl;
//    }
    /*
       ImageController에서 s3에 올렸을 때,
       Exception 나지 않으면 DB에도 추가하는 로직
       DB에 Image 추가하고 image id뱉기
    */


    public Long createImage(String filename) {
//        TODO: Image 레포 생성 Done
        Image image = Image.builder()
                .filename(filename)
                .build();
        Image retrievedImage = imageRepository.save(image);
        return retrievedImage.getId();
    }

    public String generateURL(String filename, HttpMethod method) {
        Calendar cal = new Calendar.Builder().build();
        cal.setTime(new Date());
        cal.add(Calendar.MINUTE,180);
        URL url = amazonS3Client.generatePresignedUrl(bucket,filename,cal.getTime(),method);
        return url.toString();
    }


    /* 알림기능에서 이미지 url 가져올 때 사용할 메서드
    *   notification 쪽에서 하는게 맞음
    * */
//    public String getDownloadURL(String filename){
//        return generateURL(filename, HttpMethod.GET);
//    }
}
