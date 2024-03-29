package com.ssafy.petpal.control.controller;

import com.fasterxml.jackson.core.JsonProcessingException;
import com.fasterxml.jackson.databind.ObjectMapper;
import com.ssafy.petpal.control.dto.ControlDto;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.amqp.rabbit.annotation.RabbitListener;
import org.springframework.amqp.rabbit.core.RabbitTemplate;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.messaging.handler.annotation.DestinationVariable;
import org.springframework.messaging.handler.annotation.MessageMapping;
import org.springframework.messaging.handler.annotation.Payload;
import org.springframework.stereotype.Controller;

@Controller
public class ControlController {
    private final RabbitTemplate rabbitTemplate;
    private final ObjectMapper objectMapper;

    private static final Logger logger = LoggerFactory.getLogger(ControlController.class);
    private static final String CONTROL_QUEUE_NAME = "control.queue";
    private static final String CONTROL_EXCHANGE_NAME = "control.exchange";

    @Autowired
    public ControlController(RabbitTemplate rabbitTemplate, ObjectMapper objectMapper) {
        this.rabbitTemplate = rabbitTemplate;
        this.objectMapper = objectMapper;
    }

    @MessageMapping("control.message.{userId}")
    public void sendMessage(@Payload String rawMessage, @DestinationVariable String userId) throws JsonProcessingException {
//        logger.info("Received message: {}", rawMessage);
        ControlDto controlDto = objectMapper.readValue(rawMessage, ControlDto.class);
        rabbitTemplate.convertAndSend(CONTROL_EXCHANGE_NAME, "user." + userId, controlDto);
    }

    @MessageMapping("scan.map.{userId}.{homeId}")
    public void sendMessage(@Payload String rawMessage, @DestinationVariable String userId, @DestinationVariable String homeId) throws JsonProcessingException {
        ControlDto controlDto = objectMapper.readValue(rawMessage, ControlDto.class);
        String type = controlDto.getType();
        switch (type){
            case "SCAN":
                rabbitTemplate.convertAndSend(CONTROL_EXCHANGE_NAME, "user." + userId, controlDto);
                break;
            case "COMPLETE":
                break;
        }
    }



    @RabbitListener(queues = CONTROL_QUEUE_NAME)
    public void receive(ControlDto controlDto) {
//        logger.info(" log : " + controlDto);
    }
}
