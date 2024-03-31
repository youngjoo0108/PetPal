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
////         ROS2가 준 메세지 받기
///
        // mapRepository.save(map)
        Point point = locationToPoint(applianceRegisterDTO.getCoordinate());
        Appliance appliance = Appliance.builder()
                .applianceUUID(applianceRegisterDTO.getApplianceUUID())
                .applianceType(applianceRegisterDTO.getApplianceType())
                .coordinate(point)
                .home(home)
                .room(room)
                .build();
        applianceRepository.save(appliance);
    }

    public Appliance fetchApplianceByUUID(String uuid){
        return applianceRepository.findByApplianceUUID(uuid);
    }

    public List<ApplianceResponseDto> fetchAllApplianceByRoomId(Long roomId){
        List<ApplianceResponseDto> allByRoomId = applianceRepository.findAllByRoomId(roomId);
        allByRoomId.forEach(appliance -> {
            String key = "home:" + appliance.getHomeId() + ":appliance:" + appliance.getApplianceId();
            String value = redisTemplate.opsForValue().get(key);
            if (value != null) {
                try {
                    int applianceStatus = Integer.parseInt(value);
                    appliance.setApplianceStatus(applianceStatus);
                } catch (NumberFormatException e) {
                    // 정수로 변환할 수 없는 값이 조회된 경우의 처리, 예: 로깅
                    log.error("Invalid appliance status format for appliance " + appliance.getApplianceId(), e);
                }
            } else {
                // Redis에서 조회된 값이 null인 경우의 처리, 예: 기본값 설정 또는 로깅
                appliance.setApplianceStatus(-1); // 가정: 상태를 알 수 없음을 -1로 표현
                log.info("No status found for appliance " + appliance.getApplianceId() + ", defaulting to -1");
            }
        });
        return allByRoomId;

    }

    public List<Appliance> fetchAllApplianceByHomeId(Long homeId){
        return applianceRepository.findAllByHomeId(homeId);
    }

    public void updateApplianceStatus(Long homeId, Long applianceId, String status) {
        redisTemplate.opsForValue().set("home:" + homeId + ":appliance:" + applianceId, status);
    }
}
