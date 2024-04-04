package com.ssafy.petpal.schedule.service;

import com.ssafy.petpal.home.entity.Home;
import com.ssafy.petpal.home.repository.HomeRepository;
import com.ssafy.petpal.object.dto.Location;
import com.ssafy.petpal.object.entity.Appliance;
import com.ssafy.petpal.object.repository.ApplianceRepository;
import com.ssafy.petpal.schedule.dto.ScheduleActualResponseDto;
import com.ssafy.petpal.schedule.dto.ScheduleDto;
import com.ssafy.petpal.schedule.dto.ScheduleTemporalDto;
import com.ssafy.petpal.schedule.dto.ScheduleUpdateDto;
import com.ssafy.petpal.schedule.entity.Schedule;
import com.ssafy.petpal.schedule.repository.ScheduleRepository;
import lombok.RequiredArgsConstructor;
import org.locationtech.jts.geom.Point;
import org.springframework.stereotype.Service;

import java.util.List;
import java.util.stream.Collectors;

@Service
@RequiredArgsConstructor
public class ScheduleService {
    private final ScheduleRepository scheduleRepository;
    private final HomeRepository homeRepository;
    private final ApplianceRepository applianceRepository;
    public void createSchedule(ScheduleDto scheduleDto){
        Home home = homeRepository.findById(scheduleDto.getHomeId())
                .orElseThrow(IllegalArgumentException::new);
        Appliance appliance = applianceRepository.findById(scheduleDto.getApplianceId())
                .orElseThrow(IllegalArgumentException::new);

        Schedule schedule = Schedule.builder()
                .home(home)
                .appliance(appliance)
                .scheduleDay(scheduleDto.getDay())
                .scheduleTime(scheduleDto.getTime())
                .taskType(scheduleDto.getTaskType())
                .isActive(scheduleDto.isActive())
                .build();
        scheduleRepository.save(schedule);
    }

    public List<ScheduleActualResponseDto> fetchAllSchedules(Long homeId) {

        List<Schedule> schedules = scheduleRepository.findAllByHomeId(homeId);
        return schedules.stream().map(this::convertToScheduleActualResponseDto).collect(Collectors.toList());
    }

    private ScheduleActualResponseDto convertToScheduleActualResponseDto(Schedule schedule) {
        // Appliance의 Point 좌표를 Location으로 변환
        Point coordinate = schedule.getAppliance().getCoordinate();
        Location location = new Location(coordinate.getX(), coordinate.getY()); // 이 부분은 Location 생성자나 팩토리 메소드가 적절히 정의되어 있어야 합니다.

        return new ScheduleActualResponseDto(
                schedule.getId(),
                schedule.getAppliance().getId(),
                schedule.getAppliance().getApplianceType(),
                location, // 변환된 Location 객체
                schedule.getAppliance().getApplianceUUID(),
                schedule.getAppliance().getRoom().getRoomName(),
                schedule.getScheduleDay(),
                schedule.getScheduleTime(),
                schedule.getTaskType(),
                schedule.isActive()
        );
    }

    public void deleteSchedule(Long scheduleId) {
        Schedule schedule = scheduleRepository.findById(scheduleId)
                .orElseThrow(IllegalArgumentException::new);
        scheduleRepository.delete(schedule);
    }

    public void deleteAllScheduleByApplianceId(Long applianceId){
        scheduleRepository.deleteAllByApplianceId(applianceId);
    }


    public void updateSchedule(ScheduleUpdateDto scheduleUpdateDto) {
        Schedule schedule = scheduleRepository.findById(scheduleUpdateDto.getScheduleId())
                .orElseThrow(IllegalArgumentException::new);
// Home 엔티티 조회

        // Schedule 엔티티의 속성 갱신
        schedule.update(scheduleUpdateDto.isActive());

    }
}
