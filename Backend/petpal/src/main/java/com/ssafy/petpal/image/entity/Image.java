package com.ssafy.petpal.image.entity;

import com.ssafy.petpal.common.BaseEntity;
import jakarta.persistence.*;
import jakarta.validation.constraints.NotNull;
import lombok.Builder;
import lombok.Getter;
import lombok.NoArgsConstructor;

@Entity
@NoArgsConstructor
@Getter
@Table(name = "Images")
public class Image extends BaseEntity {

    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    @Column(name = "image_id")
    private Long id;

    @Column(name = "filename")
    @NotNull
    private String filename;

    @Builder
    public Image(String filename){
        this.filename= filename;
    }
}
