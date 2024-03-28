package com.ssafy.petpal.object.entity;

import ch.qos.logback.classic.spi.LoggingEventVO;
import jakarta.persistence.*;
import lombok.Builder;
import lombok.Getter;
import lombok.NoArgsConstructor;

@Entity
@Getter
@NoArgsConstructor
@Table(name = "Targets")
public class Target {


    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    @Column(name = "target_id")
    private Long id;

    @Column(name = "home_id")
    private Long homeId;

    @Column(name = "object_id")
    private Long objectId;

    @Builder
    public Target(Long homeId, Long objectId){
        this.homeId = homeId;
        this.objectId = objectId;
    }


}
