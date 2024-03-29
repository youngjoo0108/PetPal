package com.ssafy.petpal.object.controller;

import com.ssafy.petpal.object.dto.ApplianceRegisterDTO;
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

    static String[] STR_ARR = {"TV","Air Conditioner","Light","Curtain","Air Purifier"};
    @PostMapping
    public ResponseEntity<Void> postAppliance(ApplianceRegisterDTO applianceRegisterDTO){
        try{
            applianceService.createAppliance(applianceRegisterDTO);
            return ResponseEntity.ok(null);
        }catch (Exception e) {
            return ResponseEntity.status(HttpStatus.INTERNAL_SERVER_ERROR).build();
        }
    }


    @GetMapping("/{applianceUUID}")
    public ResponseEntity<Appliance> getApplianceByUUID(@PathVariable String applianceUUID){
        try{
            Appliance appliance = applianceService.fetchApplianceByUUID(applianceUUID);
            return ResponseEntity.ok(appliance);
        }catch (Exception e){
            return ResponseEntity.status(HttpStatus.INTERNAL_SERVER_ERROR).build();
        }
    }

    @GetMapping("/{roomId}")
    public ResponseEntity<List<Appliance>> getApplianceListByRoomId(@PathVariable Long roomId){
        try{
            List<Appliance> list =applianceService.fetchAllApplianceByRoomId(roomId);
            return ResponseEntity.ok(list);
        }catch (Exception e) {
            return ResponseEntity.status(HttpStatus.INTERNAL_SERVER_ERROR).build();
        }
    }

    @GetMapping("/default")
    public ResponseEntity<String[]> getDefaultAppliance(){
        return ResponseEntity.ok(STR_ARR);
    }

    @GetMapping("/{homeId}")
    public ResponseEntity<List<Appliance>> getApplianceListByHomeId(@PathVariable Long homeId){
        try{
            List<Appliance> list = applianceService.fetchAllApplianceByHomeId(homeId);
            return ResponseEntity.ok(list);
        }catch (Exception e) {
            return ResponseEntity.status(HttpStatus.INTERNAL_SERVER_ERROR).build();
        }
    }



}
