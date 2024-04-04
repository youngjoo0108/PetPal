package com.ssafy.petpal.schedule.controller;
import com.ssafy.petpal.schedule.dto.ScheduleActualResponseDto;
import com.ssafy.petpal.schedule.dto.ScheduleDto;
import com.ssafy.petpal.schedule.dto.ScheduleTemporalDto;
import com.ssafy.petpal.schedule.dto.ScheduleUpdateDto;
import com.ssafy.petpal.schedule.service.ScheduleService;
import lombok.RequiredArgsConstructor;
import lombok.extern.slf4j.Slf4j;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

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
            scheduleService.createSchedule(scheduleDto);
            return ResponseEntity.ok(null);
        }catch (Exception e){
            return ResponseEntity.status(HttpStatus.INTERNAL_SERVER_ERROR).build();
        }
    }

    @GetMapping("/{homeId}")
    public ResponseEntity<List<ScheduleActualResponseDto>> getSchedules(@PathVariable Long homeId){
        try{
            List<ScheduleActualResponseDto> list = scheduleService.fetchAllSchedules(homeId);
            return ResponseEntity.ok(list);
        }catch (Exception e){
            return ResponseEntity.status(HttpStatus.INTERNAL_SERVER_ERROR).build();
        }
    }

    @DeleteMapping("/{scheduleId}")
    public ResponseEntity<Void> deleteSchedule(@PathVariable Long scheduleId){
        try{
            scheduleService.deleteSchedule(scheduleId);
            return ResponseEntity.ok(null);
        }catch (Exception e){
            return ResponseEntity.status(HttpStatus.INTERNAL_SERVER_ERROR).build();
        }
    }

    @PutMapping
    public ResponseEntity<Void> putSchedule(@RequestBody ScheduleUpdateDto scheduleUpdateDto){
        try{
            scheduleService.updateSchedule(scheduleUpdateDto);
            return ResponseEntity.ok(null);
        }catch (Exception e){
            return ResponseEntity.status(HttpStatus.INTERNAL_SERVER_ERROR).build();
        }
    }
}
