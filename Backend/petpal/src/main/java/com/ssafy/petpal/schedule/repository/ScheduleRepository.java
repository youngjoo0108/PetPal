package com.ssafy.petpal.schedule.repository;

import com.ssafy.petpal.schedule.entity.Schedule;
import org.springframework.data.jpa.repository.JpaRepository;

import java.util.List;

public interface ScheduleRepository extends JpaRepository<Schedule,Long> {
    List<Schedule> findAllByHomeId(Long homeId);
}
