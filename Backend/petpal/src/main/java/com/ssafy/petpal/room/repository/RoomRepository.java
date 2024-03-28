package com.ssafy.petpal.room.repository;

import com.ssafy.petpal.room.entity.Room;
import org.springframework.data.jpa.repository.JpaRepository;

import java.util.List;

public interface RoomRepository extends JpaRepository<Room,Long> {
    List<Room> findAllByHomeId(Long homeId);
}
