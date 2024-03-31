package com.ssafy.petpal.schedule.controller;
import com.amazonaws.Response;
import com.ssafy.petpal.schedule.dto.ScheduleDto;
import com.ssafy.petpal.schedule.dto.ScheduleResponseDto;
import com.ssafy.petpal.schedule.entity.Schedule;
import com.ssafy.petpal.schedule.service.ScheduleService;
import lombok.RequiredArgsConstructor;
import lombok.extern.slf4j.Slf4j;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;
import org.springframework.web.multipart.MultipartFile;

import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

@RestController
@RequiredArgsConstructor
@Slf4j
@RequestMapping("api/v1/schedules")

public class ScheduleController {

    private final ScheduleService scheduleService;



    @PostMapping
    public ResponseEntity<Void> postSchedule(@RequestBody ScheduleDto scheduleDto){
        try{
            log.info(scheduleDto.toString());
            scheduleService.createSchedule(scheduleDto);
            return ResponseEntity.ok(null);
        }catch (Exception e){
            return ResponseEntity.status(HttpStatus.INTERNAL_SERVER_ERROR).build();
        }
    }

    @GetMapping("/{homeId}")
    public ResponseEntity<List<ScheduleResponseDto>> getSchedules(@PathVariable Long homeId){
        try{
            List<ScheduleResponseDto> list = scheduleService.fetchAllSchedules(homeId);
            return ResponseEntity.ok(list);
        }catch (Exception e){
            return ResponseEntity.status(HttpStatus.INTERNAL_SERVER_ERROR).build();
        }
    }

}
