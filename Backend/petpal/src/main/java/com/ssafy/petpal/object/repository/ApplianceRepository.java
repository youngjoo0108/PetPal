package com.ssafy.petpal.object.repository;

import com.ssafy.petpal.object.entity.Appliance;
import org.springframework.data.jpa.repository.JpaRepository;

public interface ApplianceRepository extends JpaRepository<Appliance,Long> {
}
