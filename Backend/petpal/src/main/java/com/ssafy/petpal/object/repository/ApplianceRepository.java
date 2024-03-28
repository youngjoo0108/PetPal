package com.ssafy.petpal.object.repository;

import com.ssafy.petpal.object.entity.Appliance;
import org.springframework.data.jpa.repository.JpaRepository;

import java.util.List;

public interface ApplianceRepository extends JpaRepository<Appliance,Long> {

    List<Appliance> findAllByRoomId(Long roomId);


    List<Appliance> findAllByHomeId(Long homeId);

    Appliance findByApplianceUUID(String uuid);
}
