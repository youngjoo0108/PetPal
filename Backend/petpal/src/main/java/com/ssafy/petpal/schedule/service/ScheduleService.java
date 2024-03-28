package com.ssafy.petpal.schedule.service;

import com.ssafy.petpal.home.entity.Home;
import com.ssafy.petpal.home.repository.HomeRepository;
import com.ssafy.petpal.schedule.dto.ScheduleDto;
import com.ssafy.petpal.schedule.entity.Schedule;
import com.ssafy.petpal.schedule.repository.ScheduleRepository;
import lombok.RequiredArgsConstructor;
import org.springframework.stereotype.Service;

import java.util.List;

@Service
@RequiredArgsConstructor
public class ScheduleService {
    private final ScheduleRepository scheduleRepository;
    private final HomeRepository homeRepository;
    public void createSchedule(ScheduleDto scheduleDto){
        Home home = homeRepository.findById(scheduleDto.getHomeId())
                .orElseThrow(IllegalArgumentException::new);
        Schedule schedule = Schedule.builder()
                .home(home)
                .scheduleDay(scheduleDto.getDay())
                .scheduleTime(scheduleDto.getTime())
                .scheduleRepeat(scheduleDto.isRepeat())
                .taskType(scheduleDto.getTaskType())
                .isActive(scheduleDto.isActive())
                .build();
        scheduleRepository.save(schedule);
    }

    public List<Schedule> fetchAllSchedules(Long homeId) {
        return scheduleRepository.findAllByHomeId(homeId);
    }
}
