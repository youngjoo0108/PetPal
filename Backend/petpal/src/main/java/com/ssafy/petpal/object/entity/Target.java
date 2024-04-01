package com.ssafy.petpal.object.entity;

import ch.qos.logback.classic.spi.LoggingEventVO;
import com.ssafy.petpal.common.BaseEntity;
import com.ssafy.petpal.home.entity.Home;
import com.ssafy.petpal.image.entity.Image;
import jakarta.persistence.*;
import lombok.Builder;
import lombok.Getter;
import lombok.NoArgsConstructor;
import org.locationtech.jts.geom.Point;
import org.springframework.data.annotation.CreatedDate;

import java.time.LocalDate;

@Entity
@Getter
@NoArgsConstructor
@Table(name = "Targets")
public class Target extends BaseEntity {


    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    @Column(name = "target_id")
    private Long id;

    @ManyToOne
    @JoinColumn(name = "home_id")
    private Home home;

    @Column(name = "object_type")
    private String objectType;

    @OneToOne
    @JoinColumn(name = "image_id")
    private Image image;

    @Column(name = "coordinate")
    private Point coordinate;




    @Builder
    public Target(Home home,String objectType, Image image, Point coordinate){
        this.home = home;
        this.objectType = objectType;
        this.image = image;
        this.coordinate = coordinate;
    }


}
