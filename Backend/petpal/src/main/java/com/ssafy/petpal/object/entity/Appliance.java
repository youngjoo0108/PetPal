package com.ssafy.petpal.object.entity;

import jakarta.persistence.*;
import lombok.Builder;
import lombok.Getter;
import lombok.NoArgsConstructor;

@Entity
@Getter
@NoArgsConstructor
@Table(name = "appliance_object_home")
public class Appliance {


    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    @Column(name = "appliance_id")
    private Long id;

    @Column(name = "home_id")
    private Long homeId;

    @Column(name = "object_id")
    private Long objectId;

    @Builder
    public Appliance(Long homeId, Long objectId){
        this.homeId = homeId;
        this.objectId = objectId;
    }


}
