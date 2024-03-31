package com.ssafy.petpal.schedule.repository;

import com.ssafy.petpal.schedule.dto.ScheduleResponseDto;
import com.ssafy.petpal.schedule.entity.Schedule;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.jpa.repository.Query;
import org.springframework.data.repository.query.Param;

import java.util.List;

public interface ScheduleRepository extends JpaRepository<Schedule,Long> {

    @Query("select new com.ssafy.petpal.schedule.dto.ScheduleResponseDto(" +
            "s.appliance.id, s.scheduleDay, s.scheduleTime," +
            " s.taskType, s.scheduleRepeat, s.isActive) " +
            "from Schedules as s " +
            "where s.home.id = :homeId")
    List<ScheduleResponseDto> findAllByHomeId(@Param("homeId") Long homeId);
}
