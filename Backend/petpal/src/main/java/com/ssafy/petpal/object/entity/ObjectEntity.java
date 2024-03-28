package com.ssafy.petpal.object.entity;

import jakarta.persistence.*;
import lombok.*;
import org.locationtech.jts.geom.Point;
import org.springframework.data.jpa.domain.support.AuditingEntityListener;

@Entity
@Getter
@NoArgsConstructor
@EntityListeners({AuditingEntityListener.class})
@Table(name="Objects")
public class ObjectEntity {


    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    @Column(name = "object_id")
    Long id;

    @Column(name = "image_id")
    Long imageId;

//    @Column(name = "object_type")
//    int objectType;

    @Column(name = "cordinate")
    Point cordinate;
//    Point



    @Builder
    public ObjectEntity(Long imageId, /*int objectType,*/ Point cordinate) {
        this.imageId = imageId;
//        this.objectType = objectType;
        this.cordinate = cordinate;
    }

}
