package com.ssafy.petpal.control.controller;

import com.fasterxml.jackson.core.JsonProcessingException;
import com.ssafy.petpal.control.dto.ControlDto;
import lombok.RequiredArgsConstructor;
import org.springframework.amqp.rabbit.annotation.RabbitListener;
import org.springframework.amqp.rabbit.core.RabbitTemplate;
import org.springframework.messaging.handler.annotation.DestinationVariable;
import org.springframework.messaging.handler.annotation.MessageMapping;
import org.springframework.messaging.handler.annotation.Payload;
import org.springframework.stereotype.Controller;

@Controller
@RequiredArgsConstructor
public class ControlController {
    private final RabbitTemplate rabbitTemplate;

    private static final String CONTROL_QUEUE_NAME = "control.queue";
    private static final String CONTROL_EXCHANGE_NAME = "control.exchange";

    @MessageMapping("control.message.{userId}")
    public void sendMessage(@Payload ControlDto controlDto, @DestinationVariable String userId) throws JsonProcessingException {
        rabbitTemplate.convertAndSend(CONTROL_EXCHANGE_NAME, "user." + userId, controlDto);
    }

    @RabbitListener(queues = CONTROL_QUEUE_NAME)
    public void receive(ControlDto controlDto) {}
}