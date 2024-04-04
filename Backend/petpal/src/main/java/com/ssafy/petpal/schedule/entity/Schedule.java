package com.ssafy.petpal.schedule.entity;

import com.ssafy.petpal.common.BaseEntity;
import com.ssafy.petpal.home.entity.Home;
import com.ssafy.petpal.object.entity.Appliance;
import jakarta.persistence.*;
import lombok.*;

import java.time.LocalDate;
import java.time.LocalDateTime;
import java.time.LocalTime;

@Entity(name = "Schedules")
@Getter
@Setter
@ToString
@NoArgsConstructor
public class Schedule extends BaseEntity {

    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    @Column(name = "schedule_id")
    private Long id;

    @ManyToOne
    @JoinColumn(name = "home_id")
    private Home home;

    @ManyToOne
    @JoinColumn(name = "appliance_id")
    private Appliance appliance;
//    @Column(name = "schedule_tsid")
//    private String tsid;

    @Column(name = "task_type")
    private String taskType;

    @Column(name = "schedule_day")
    private LocalDate scheduleDay;

    @Column(name = "schedule_start_time")
    private LocalTime scheduleTime;


    @Column(name = "schedule_toggle")
    private boolean isActive;

    @Builder
    public Schedule(Home home, Appliance appliance,/*String tsid,*/String taskType, LocalTime scheduleTime, LocalDate scheduleDay, boolean isActive){
        this.home = home;
        this.appliance = appliance;
//        this.tsid = tsid;
        this.taskType = taskType;
        this.scheduleTime = scheduleTime;
        this.scheduleDay = scheduleDay;
        this.isActive = isActive;

    }

    public void update(boolean isActive) {
//        this.home = home;
//        this.appliance = appliance;
//        this.scheduleDay = day;
//        this.scheduleTime = time;
//        this.taskType = taskType;
        this.isActive = isActive;
    }

}
