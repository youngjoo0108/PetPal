package com.ssafy.petpal.object.repository;

import com.ssafy.petpal.object.dto.ApplianceResponseDto;
import com.ssafy.petpal.object.entity.Appliance;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.jpa.repository.Query;
import org.springframework.data.repository.query.Param;

import java.util.List;

public interface ApplianceRepository extends JpaRepository<Appliance,Long> {


    @Query("select new com.ssafy.petpal.object.dto." +
            "ApplianceResponseDto(a.id, a.applianceType,a.home.id, a.room.id, a.room.roomName)" +
            "from Appliance a " +
            "where a.room.id = :roomId "+
            "order by a.room.roomName"
    )
    List<ApplianceResponseDto> findAllByRoomId(@Param("roomId") Long roomId);


    @Query("select new com.ssafy.petpal.object.dto." +
            "ApplianceResponseDto(a.id, a.applianceType, a.home.id, a.room.id, a.room.roomName) " +
            "from Appliance a " +
            "where a.home.id = :homeId " +
            "order by a.room.roomName")
    List<ApplianceResponseDto> findAllByHomeId(@Param("homeId") Long homeId);


    @Query("select new com.ssafy.petpal.object.dto." +
            "ApplianceResponseDto(a.id, a.applianceType, a.home.id, a.room.id, a.room.roomName) " +
            "from Appliance a " +
            "where a.applianceUUID = :uuid")
    ApplianceResponseDto findByApplianceUUID(String uuid);
}
