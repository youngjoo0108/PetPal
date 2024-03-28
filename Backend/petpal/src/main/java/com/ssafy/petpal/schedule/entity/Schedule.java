package com.ssafy.petpal.schedule.entity;

import com.ssafy.petpal.home.entity.Home;
import com.ssafy.petpal.object.entity.Appliance;
import jakarta.persistence.*;
import lombok.Builder;
import lombok.Getter;
import lombok.NoArgsConstructor;

import java.time.LocalTime;

@Entity(name = "Schedules")
@Getter
@NoArgsConstructor
public class Schedule {

    @Id
    @Column(name = "schedule_id")
    private Long id;

    @ManyToOne
    @JoinColumn(name = "home_id")
    private Home home;

    @OneToOne
    @JoinColumn(name = "appliance_id")
    private Appliance appliance;
//    @Column(name = "schedule_tsid")
//    private String tsid;

    @Column(name = "task_type")
    private String taskType;

    @Column(name = "schedule_start_time")
    private LocalTime scheduleTime;

    @Column(name = "schedule_day")
    private String scheduleDay;

    @Column(name = "schedule_repeat")
    private boolean scheduleRepeat;

    @Column(name = "schedule_toggle")
    private boolean isActive;

    @Builder
    public Schedule(Home home, Appliance appliance,/*String tsid,*/String taskType, LocalTime scheduleTime, String scheduleDay, boolean scheduleRepeat, boolean isActive){
        this.home = home;
        this.appliance = appliance;
//        this.tsid = tsid;
        this.taskType = taskType;
        this.scheduleTime = scheduleTime;
        this.scheduleDay = scheduleDay;
        this.scheduleRepeat = scheduleRepeat;
        this.isActive = isActive;

    }
}
