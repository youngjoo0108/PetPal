package com.ssafy.petpal.control.controller;

import com.fasterxml.jackson.core.JsonProcessingException;
import com.fasterxml.jackson.databind.ObjectMapper;
import com.ssafy.petpal.control.dto.ControlDto;
import com.ssafy.petpal.object.service.ApplianceService;
import lombok.AllArgsConstructor;
import lombok.RequiredArgsConstructor;
import org.checkerframework.checker.units.qual.A;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.amqp.rabbit.annotation.RabbitListener;
import org.springframework.amqp.rabbit.core.RabbitTemplate;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.data.redis.core.StringRedisTemplate;
import org.springframework.messaging.handler.annotation.DestinationVariable;
import org.springframework.messaging.handler.annotation.MessageMapping;
import org.springframework.messaging.handler.annotation.Payload;
import org.springframework.stereotype.Controller;

@Controller
//@RequiredArgsConstructor
@AllArgsConstructor
public class ControlController {
    private final RabbitTemplate rabbitTemplate;
    private final ObjectMapper objectMapper;
    private final StringRedisTemplate redisTemplate;
    private final ApplianceService applianceService;
    private static final Logger logger = LoggerFactory.getLogger(ControlController.class);
    private static final String CONTROL_QUEUE_NAME = "control.queue";
    private static final String CONTROL_EXCHANGE_NAME = "control.exchange";



    @MessageMapping("control.message.{homeId}")
    public void sendMessage(@Payload String rawMessage, @DestinationVariable String homeId) throws JsonProcessingException {
//        logger.info("Received message: {}", rawMessage);
        ControlDto controlDto = objectMapper.readValue(rawMessage, ControlDto.class);
        String type = controlDto.getType();
        switch (type){
            case "COMPLETE":
                // ROS에서 입증한 실제 가전상태 데이터를 redis에 올린다.
//                controlDto.getMessage() //parsing
//                applianceService.updateApplianceStatus(homeId,applianceId,status);
//
//              fcm 호출.
                break;
            case "ON":
                break;
            case "OFF":
                break;
        }
        rabbitTemplate.convertAndSend(CONTROL_EXCHANGE_NAME, "home." + homeId, controlDto);
    }

    @MessageMapping("scan.map.{homeId}")
    public void sendMapData(@Payload String rawMessage, @DestinationVariable String homeId) throws JsonProcessingException {
        ControlDto controlDto = objectMapper.readValue(rawMessage, ControlDto.class);
        String type = controlDto.getType();
        switch (type){
            case "SCAN":
                rabbitTemplate.convertAndSend(CONTROL_EXCHANGE_NAME, "home." + homeId, controlDto);
                break;
            case "COMPLETE":
                // 날것의 맵
                // dtoMapper로 만들ㅇ서ㅓ
                // mapService.createMap(dto)
                // scan.map.{homeID} 메세지 발행(깎은 맵이 들어가있다)

                break;
            case "ROUTE":
                // 경로 저장 repository

        }
    }



    @RabbitListener(queues = CONTROL_QUEUE_NAME)
    public void receive(ControlDto controlDto) {
//        logger.info(" log : " + controlDto);
    }
}
