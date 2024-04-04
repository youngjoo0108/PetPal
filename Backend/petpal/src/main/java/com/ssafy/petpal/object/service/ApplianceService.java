package com.ssafy.petpal.object.service;

import com.ssafy.petpal.home.entity.Home;
import com.ssafy.petpal.home.repository.HomeRepository;
import com.ssafy.petpal.object.dto.ApplianceRegisterDTO;
import com.ssafy.petpal.object.dto.ApplianceResponseDto;
import com.ssafy.petpal.object.entity.Appliance;
import com.ssafy.petpal.object.repository.ApplianceRepository;
import com.ssafy.petpal.room.entity.Room;
import com.ssafy.petpal.room.repository.RoomRepository;
import lombok.RequiredArgsConstructor;
import lombok.extern.slf4j.Slf4j;
import org.locationtech.jts.geom.Point;
import org.springframework.data.redis.core.RedisTemplate;
import org.springframework.data.redis.core.StringRedisTemplate;
import org.springframework.stereotype.Service;

import java.util.List;
import java.util.Map;
import java.util.Objects;

import static com.ssafy.petpal.object.dto.TargetRegisterDto.locationToPoint;

@Service
@Slf4j
@RequiredArgsConstructor
public class ApplianceService {

    private final ApplianceRepository applianceRepository;
    private final HomeRepository homeRepository;
    private final RoomRepository roomRepository;
    private final StringRedisTemplate redisTemplate;
    public void createAppliance(ApplianceRegisterDTO applianceRegisterDTO){
        Home home = homeRepository.findById(applianceRegisterDTO.getHomeId())
                .orElseThrow(IllegalArgumentException::new);
        Room room = roomRepository.findById(applianceRegisterDTO.getRoomId())
                .orElseThrow(IllegalArgumentException::new);

//         ROS2로 메세지 발행
//        http로 ROs야 맵데이터 다오
//              response = request(ros주소);
//         ROS2가 준 메세지 받기
//
        // mapRepository.save(map)
        Point point = locationToPoint(applianceRegisterDTO.getCoordinate());
        Appliance appliance = Appliance.builder()
                .applianceUUID(applianceRegisterDTO.getApplianceUUID())
                .applianceType(applianceRegisterDTO.getApplianceType())
                .coordinate(point)
                .home(home)
                .room(room)
                .build();
        Appliance appliance1  =applianceRepository.save(appliance);
        redisTemplate.opsForValue().set("home:" + applianceRegisterDTO.getHomeId() + ":appliance:" + appliance1.getApplianceUUID(), "OFF");
    }

    public ApplianceResponseDto fetchApplianceByUUID(String uuid){
        ApplianceResponseDto appliance = applianceRepository.findByApplianceUUID(uuid);
        String applianceStatus = getApplianceStatus(appliance.getHomeId(), appliance.getApplianceUUID());

        if(applianceStatus==null){
            redisTemplate.opsForValue().set("home:"+appliance.getHomeId()+":appliance:"+appliance.getApplianceUUID(),"OFF");
            applianceStatus="OFF";
        }
        appliance.setApplianceStatus(
            applianceStatus
        );
        return appliance;
    }

    public List<ApplianceResponseDto> fetchAllApplianceByRoomId(Long roomId){
        List<ApplianceResponseDto> list = applianceRepository.findAllByRoomId(roomId);
        list.forEach(appliance -> {
            String applianceStatus = getApplianceStatus(appliance.getHomeId(), appliance.getApplianceUUID());
            if(applianceStatus==null){
                redisTemplate.opsForValue().set("home:"+appliance.getHomeId()+":appliance:"+appliance.getApplianceUUID(),"OFF");
                applianceStatus="OFF";
            }

            appliance.setApplianceStatus(
                applianceStatus
            );
        });
        return list;

    }

    public List<ApplianceResponseDto> fetchAllApplianceByHomeId(Long homeId){
        List<ApplianceResponseDto> list = applianceRepository.findAllByHomeId(homeId);
        list.forEach(appliance -> {
            String applianceStatus = getApplianceStatus(appliance.getHomeId(), appliance.getApplianceUUID());
            if(applianceStatus==null){
                redisTemplate.opsForValue().set("home:"+appliance.getHomeId()+":appliance:"+appliance.getApplianceUUID(),"OFF");
                applianceStatus="OFF";
            }
            appliance.setApplianceStatus(
                    applianceStatus
            );
        });
        return list;
    }

    public void updateApplianceStatus(Long homeId, String applianceUUID, String status) {

        redisTemplate.opsForValue().set("home:" + homeId + ":appliance:" + applianceUUID, status);

    }

    public String getApplianceStatus(Long homeId, String applianceUUID) {
        String key = "home:" + homeId + ":appliance:" + applianceUUID;

        return redisTemplate.opsForValue().get(key);
    }

    public void deleteAppliance(Long applianceId) {
        Appliance appliance = applianceRepository.findById(applianceId)
                .orElseThrow(IllegalArgumentException::new);
        applianceRepository.delete(appliance);
    }

}
