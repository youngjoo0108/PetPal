package com.ssafy.petpal.room.repository;

import com.ssafy.petpal.room.dto.RoomResponseDTO;
import com.ssafy.petpal.room.entity.Room;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.jpa.repository.Query;
import org.springframework.data.repository.query.Param;

import java.util.List;

public interface RoomRepository extends JpaRepository<Room,Long> {

    @Query("select new com.ssafy.petpal.room.dto.RoomResponseDTO(r.id, r.roomName) " +
            "from Room r " +
            "where r.home.id = :homeId")
    List<RoomResponseDTO> findAllByHomeId(@Param("homeId") Long homeId);
}
