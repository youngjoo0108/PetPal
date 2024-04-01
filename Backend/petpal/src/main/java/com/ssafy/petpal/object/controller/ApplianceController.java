package com.ssafy.petpal.object.controller;

import com.ssafy.petpal.object.dto.ApplianceRegisterDTO;
import com.ssafy.petpal.object.dto.ApplianceResponseDto;
import com.ssafy.petpal.object.entity.Appliance;
import com.ssafy.petpal.object.service.ApplianceService;
import com.ssafy.petpal.room.dto.RoomResponseDTO;
import lombok.RequiredArgsConstructor;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

import java.util.List;

@RestController
@RequiredArgsConstructor
@RequestMapping("/api/v1/appliances")
public class ApplianceController {
    private final ApplianceService applianceService;

    static String[] STR_ARR = {"TV","에어컨","전등","커튼","공기청정기"};
    @PostMapping
    public ResponseEntity<Void> postAppliance(@RequestBody ApplianceRegisterDTO applianceRegisterDTO){
        try{
            String newApplianceName = applianceRegisterDTO.getApplianceType();
            List<ApplianceResponseDto> list = applianceService.fetchAllApplianceByHomeId(applianceRegisterDTO.getHomeId());
            boolean isDuplicate = false;
            for(ApplianceResponseDto dto : list){
                if(dto.getApplianceType().equals(newApplianceName)){
                    isDuplicate = true;
                    break;
                }
            }
            if(isDuplicate){
                // 중복이 발생했을 경우의 로직
                throw new IllegalArgumentException("중복된 가전 이름입니다.");
            } else {
                // 중복이 없을 경우의 로직, 예를 들어 새로운 방을 추가하는 로직 등
                applianceService.createAppliance(applianceRegisterDTO);
                return ResponseEntity.ok(null);
            }


        }catch (IllegalArgumentException e){
            return ResponseEntity.status(HttpStatus.CONFLICT).build();
        }catch (Exception e) {
            System.out.println(e.getMessage());
            return ResponseEntity.status(HttpStatus.INTERNAL_SERVER_ERROR).build();
        }
    }

    // ROS에서 사용
    @GetMapping("/{appliacneUUID}")
    public ResponseEntity<ApplianceResponseDto> getApplianceByUUID(@PathVariable String applianceUUID){
        try{
            ApplianceResponseDto appliance = applianceService.fetchApplianceByUUID(applianceUUID);
            return ResponseEntity.ok(appliance);
        }catch (Exception e){
            return ResponseEntity.status(HttpStatus.INTERNAL_SERVER_ERROR).build();
        }
    }

    @GetMapping("/room/{roomId}")
    public ResponseEntity<List<ApplianceResponseDto>> getApplianceListByRoomId(@PathVariable Long roomId){
        try{
            List<ApplianceResponseDto> list =applianceService.fetchAllApplianceByRoomId(roomId);
            return ResponseEntity.ok(list);
        }catch (Exception e) {
            return ResponseEntity.status(HttpStatus.INTERNAL_SERVER_ERROR).build();
        }
    }

    @GetMapping("/default")
    public ResponseEntity<String[]> getDefaultAppliance(){
        return ResponseEntity.ok(STR_ARR);
    }

    @GetMapping("/home/{homeId}")
    public ResponseEntity<List<ApplianceResponseDto>> getApplianceListByHomeId(@PathVariable Long homeId){
        try{
            List<ApplianceResponseDto> list = applianceService.fetchAllApplianceByHomeId(homeId);
            return ResponseEntity.ok(list);
        }catch (Exception e) {
            return ResponseEntity.status(HttpStatus.INTERNAL_SERVER_ERROR).build();
        }
    }

    // 테스트용
//    @GetMapping("/status/{applianceId}")
//    public ResponseEntity<String> putApplianceStatus(Long homeId, @PathVariable Long applianceId,String status){
//        try{
//            applianceService.updateApplianceStatus(homeId, applianceId, status);
//            return ResponseEntity.ok(applianceService.getApplianceStatus(homeId,applianceId));
//        }catch (Exception e){
//            System.out.println(e.getMessage());
//            return ResponseEntity.status(HttpStatus.INTERNAL_SERVER_ERROR).build();
//        }
//    }


}
