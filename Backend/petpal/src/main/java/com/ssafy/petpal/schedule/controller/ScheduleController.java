package com.ssafy.petpal.schedule.controller;

import com.fasterxml.jackson.core.JsonProcessingException;
import com.ssafy.petpal.schedule.dto.ScheduleDto;
import com.ssafy.petpal.schedule.service.ScheduleService;
import lombok.RequiredArgsConstructor;
import lombok.extern.log4j.Log4j2;
import org.springframework.amqp.rabbit.annotation.RabbitListener;
import org.springframework.amqp.rabbit.core.RabbitTemplate;
import org.springframework.messaging.handler.annotation.DestinationVariable;
import org.springframework.messaging.handler.annotation.MessageMapping;
import org.springframework.messaging.handler.annotation.Payload;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

@RestController
@RequiredArgsConstructor
@RequestMapping("api/v1/schedules")

public class ScheduleController {

    private final ScheduleService scheduleService;

    private final RabbitTemplate rabbitTemplate;

    private static final String CONTROL_QUEUE_NAME = "control.queue";
    private static final String CONTROL_EXCHANGE_NAME = "control.exchange";

    @MessageMapping("control.message.{userId}")
    public void sendMessage(@Payload ScheduleDto scheduleDto, @DestinationVariable String userId) throws JsonProcessingException {
        rabbitTemplate.convertAndSend(CONTROL_EXCHANGE_NAME, "user." + userId, scheduleDto);
    }

    @RabbitListener(queues = CONTROL_QUEUE_NAME)
    public void receive(ScheduleDto scheduleDto) {}
}
