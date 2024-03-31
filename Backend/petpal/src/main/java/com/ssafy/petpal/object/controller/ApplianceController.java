package com.ssafy.petpal.object.controller;

import com.ssafy.petpal.object.dto.ApplianceRegisterDTO;
import com.ssafy.petpal.object.dto.ApplianceResponseDto;
import com.ssafy.petpal.object.entity.Appliance;
import com.ssafy.petpal.object.service.ApplianceService;
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
    public ResponseEntity<Void> postAppliance(ApplianceRegisterDTO applianceRegisterDTO){
        try{
            applianceService.createAppliance(applianceRegisterDTO);
            return ResponseEntity.ok(null);
        }catch (Exception e) {
            return ResponseEntity.status(HttpStatus.INTERNAL_SERVER_ERROR).build();
        }
    }

    // ROS에서 사용
    @GetMapping("/{appliacneId}")
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
