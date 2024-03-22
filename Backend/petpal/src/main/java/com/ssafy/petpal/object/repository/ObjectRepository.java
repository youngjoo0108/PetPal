package com.ssafy.petpal.object.repository;

import com.ssafy.petpal.object.entity.ObjectEntity;
import org.springframework.data.jpa.repository.JpaRepository;

public interface ObjectRepository extends JpaRepository<ObjectEntity, Long> {
}
