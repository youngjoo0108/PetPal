package com.ssafy.petpal.home.service;

import com.ssafy.petpal.home.dto.HomeRequestDTO;
import com.ssafy.petpal.home.entity.Home;
import com.ssafy.petpal.home.repository.HomeRepository;
import com.ssafy.petpal.object.dto.Location;
import com.ssafy.petpal.user.entity.User;
import com.ssafy.petpal.user.repository.UserRepository;
import lombok.RequiredArgsConstructor;
import lombok.extern.slf4j.Slf4j;
import org.springframework.data.redis.core.RedisTemplate;
import org.springframework.data.redis.core.StringRedisTemplate;
import org.springframework.stereotype.Service;

import java.util.LinkedHashMap;
import java.util.List;

@Service
@RequiredArgsConstructor
@Slf4j
public class HomeService {

    private final HomeRepository homeRepository;
    private final UserRepository userRepository;

    private final RedisTemplate<String,Object> redisTemplate;
    public long createHome(HomeRequestDTO homeRequestDTO) {
        Home home = Home.builder()
//                .homeNickname(homeRequestDTO.getHomeNickname())
                .kakaoId(homeRequestDTO.getUserId())
                .build();
        Home returnHome = homeRepository.save(home);
        return returnHome.getId();
    }

    public List<Home> fetchAllByUserId(Long userId) {
        return homeRepository.findByKakaoId(userId);
    }

    public Location fetchPetCoordinate(Long homeId, int depth){
        if(depth==2){
            return new Location(0.1,0.2);
        }
        String key = "home:" + homeId+":pet";
        try{
            Location value = (Location) redisTemplate.opsForValue().get(key);
            if(value!=null){
                return value;
            } else {
                log.info("No status found for pet. " + "Retry..."+depth);
                return fetchPetCoordinate(homeId,depth+1);
            }
        }catch (Exception e){
            log.error(e.getMessage());
            return null;
        }

    }

    public void updatePetCoordinate(Long homeId, Location coordinate){
        String key = "home:"+homeId+":pet";
        redisTemplate.opsForValue().set(key, coordinate);
    }

    public Location fetchTurtleCoordinate(Long homeId, int depth) {
        if(depth==2){
            return null;
        }
        String key = "home:" + homeId+":turtle";
        try{
            Location value = (Location) redisTemplate.opsForValue().get(key);
            if(value!=null){
                return value;
            }else {
                log.info("No status found for turtle. " + "Retry..."+depth);
                return fetchTurtleCoordinate(homeId,depth+1);
            }
        }catch (Exception e){
            log.error(e.getMessage());
            return null;
        }

    }

    public void updateTurtleCoordinate(Long homeId, Location coordinate) {
        redisTemplate.opsForValue().set("home:" + homeId+":turtle", coordinate);
    }

    public Long findKakaoIdByHomeId(Long homeId) {
        return homeRepository.findById(homeId)
                .map(Home::getKakaoId) // Home 엔티티에서 kakaoId 추출
                .orElseThrow(() -> new RuntimeException("Home not found with id: " + homeId));
    }
}
