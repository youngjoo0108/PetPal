package com.ssafy.petpal.schedule.controller;

import com.fasterxml.jackson.core.JsonProcessingException;
import com.ssafy.petpal.schedule.dto.ScheduleDto;
import com.ssafy.petpal.schedule.service.ScheduleService;
import lombok.RequiredArgsConstructor;
import org.springframework.amqp.rabbit.annotation.RabbitListener;
import org.springframework.amqp.rabbit.core.RabbitTemplate;
import org.springframework.http.ResponseEntity;
import org.springframework.messaging.handler.annotation.DestinationVariable;
import org.springframework.messaging.handler.annotation.MessageMapping;
import org.springframework.messaging.handler.annotation.Payload;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;

import java.util.ArrayList;
import java.util.List;

@RestController
@RequiredArgsConstructor
@RequestMapping("api/v1/schedules")

public class ScheduleController {

    private final ScheduleService scheduleService;

    private final RabbitTemplate rabbitTemplate;

    private static final String CONTROL_QUEUE_NAME = "control.queue";
    private static final String CONTROL_EXCHANGE_NAME = "control.exchange";

    @GetMapping
    public ResponseEntity<List<ScheduleDto>> getSchedule(@RequestParam(defaultValue = "0") int page, @RequestParam(defaultValue = "10") int size){
        List<ScheduleDto> response = new ArrayList<>();
        ScheduleDto sd = new ScheduleDto();
        sd.setSender("1"); sd.setMessage("Api Test DTO");
        response.add(sd);
        return ResponseEntity.ok(response);
    }

    @MessageMapping("control.message.{userId}")
    public void sendMessage(@Payload ScheduleDto scheduleDto, @DestinationVariable String userId) throws JsonProcessingException {
        rabbitTemplate.convertAndSend(CONTROL_EXCHANGE_NAME, "user." + userId, scheduleDto);
    }

    @RabbitListener(queues = CONTROL_QUEUE_NAME)
    public void receive(ScheduleDto scheduleDto) {}
}
