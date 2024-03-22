package com.ssafy.petpal.image.entity;

import jakarta.persistence.*;
import lombok.Builder;
import lombok.Getter;
import lombok.NoArgsConstructor;

@Entity
@NoArgsConstructor
@Getter
@Table(name = "Images")
public class Image {
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    @Column(name = "image_id")
    private Long id;

    @Column(name = "image_path")
    private String imagePath;

    @Column(name = "image_original_name")
    private String imageOriginalName;

    @Column(name = "image_changed_name")
    private String imageChangedName;

    @Builder
    public Image(String imagePath, String imageOriginalName, String imageChangedName){
        this.imagePath = imagePath;
        this.imageOriginalName = imageOriginalName;
        this.imageChangedName = imageChangedName;
    }
}
