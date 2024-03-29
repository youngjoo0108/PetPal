package com.ssafy.petpal.object.service;

import com.ssafy.petpal.home.entity.Home;
import com.ssafy.petpal.home.repository.HomeRepository;
import com.ssafy.petpal.object.dto.ApplianceRegisterDTO;
import com.ssafy.petpal.object.entity.Appliance;
import com.ssafy.petpal.object.repository.ApplianceRepository;
import com.ssafy.petpal.room.entity.Room;
import com.ssafy.petpal.room.repository.RoomRepository;
import lombok.RequiredArgsConstructor;
import org.locationtech.jts.geom.Point;
import org.springframework.stereotype.Service;

import java.util.List;

import static com.ssafy.petpal.object.dto.TargetRegisterDto.locationToPoint;

@Service
@RequiredArgsConstructor
public class ApplianceService {

    private final ApplianceRepository applianceRepository;
    private final HomeRepository homeRepository;
    private final RoomRepository roomRepository;
    public void createAppliance(ApplianceRegisterDTO applianceRegisterDTO){
        Home home = homeRepository.findById(applianceRegisterDTO.getHomeId())
                .orElseThrow(IllegalArgumentException::new);
        Room room = roomRepository.findById(applianceRegisterDTO.getRoomId())
                .orElseThrow(IllegalArgumentException::new);
        Point point = locationToPoint(applianceRegisterDTO.getCoordinate());
        Appliance appliance = Appliance.builder()
                .applianceUUID(applianceRegisterDTO.getApplianceUUID())
                .applianceName(applianceRegisterDTO.getApplianceName())
                .coordinate(point)
                .home(home)
                .room(room)
                .build();
        applianceRepository.save(appliance);
    }

    public Appliance fetchApplianceByUUID(String uuid){
        return applianceRepository.findByApplianceUUID(uuid);
    }

    public List<Appliance> fetchAllApplianceByRoomId(Long roomId){
        return applianceRepository.findAllByRoomId(roomId);
    }

    public List<Appliance> fetchAllApplianceByHomeId(Long homeId){
        return applianceRepository.findAllByHomeId(homeId);
    }
}
