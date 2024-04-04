package com.ssafy.petpal.map.entity;

import com.ssafy.petpal.common.BaseEntity;
import jakarta.persistence.*;
import lombok.Getter;
import lombok.NoArgsConstructor;
import lombok.Setter;
import org.locationtech.jts.geom.Point;

@Entity
@Table(name ="Maps")
@NoArgsConstructor
@Getter
@Setter
public class Map extends BaseEntity {
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Long id;

    @Column(name = "home_id")
    private Long homeId;

    @Column(name = "map_data",columnDefinition = "MEDIUMTEXT")
    private String data;

    @Column(name = "start_grid")
    private Point point;
}
