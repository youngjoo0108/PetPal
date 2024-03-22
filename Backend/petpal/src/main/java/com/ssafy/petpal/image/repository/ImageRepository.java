package com.ssafy.petpal.image.repository;

import com.ssafy.petpal.image.entity.Image;
import org.springframework.data.jpa.repository.JpaRepository;

public interface ImageRepository extends JpaRepository<Image, Long> {
}
