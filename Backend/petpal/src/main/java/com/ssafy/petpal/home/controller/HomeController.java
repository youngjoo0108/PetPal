package com.ssafy.petpal.home.controller;

import com.ssafy.petpal.home.dto.HomeRequestDTO;
import com.ssafy.petpal.home.entity.Home;
import com.ssafy.petpal.home.service.HomeService;
import com.ssafy.petpal.object.dto.Location;
import lombok.RequiredArgsConstructor;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

import java.util.List;

@RestController
@RequestMapping("/api/v1/homes")
@RequiredArgsConstructor
public class HomeController {

    private final HomeService homeService;

    @PostMapping// test용
    public ResponseEntity<String> postHome(HomeRequestDTO homeRequestDTO ){
        try{
            homeService.createHome(homeRequestDTO);
            return ResponseEntity.ok(null);
        }catch (IllegalArgumentException e){
            return ResponseEntity.ok(e.getMessage());
        }
        catch (Exception e){
            System.out.println(e.getMessage());
            return ResponseEntity.status(HttpStatus.INTERNAL_SERVER_ERROR).build();
        }
    }

    @GetMapping
    public  ResponseEntity<List<Home>> getHomes(Long userId){
        try {
            List<Home> list = homeService.fetchAllByUserId(userId);
            return ResponseEntity.ok(list);
        }catch (Exception e){
            return ResponseEntity.status(HttpStatus.INTERNAL_SERVER_ERROR).build();
        }
    }

    @GetMapping("/pet/{homeId}")
    public ResponseEntity<Location> getPetCoordinate(@PathVariable Long homeId){
        try{
            return ResponseEntity.ok(homeService.fetchPetCoordinate(homeId,0));
        }catch (Exception e){
            return ResponseEntity.status(HttpStatus.INTERNAL_SERVER_ERROR).build();
        }
    }

    @PutMapping("/pet/{homeId}")
    public ResponseEntity<Void> putPetCoordinate(@PathVariable Long homeId, @RequestBody Location coordinate){
        System.out.println("Adsd");
        System.out.println(coordinate.toString());
        try{
            homeService.updatePetCoordinate(homeId,coordinate);
            return ResponseEntity.ok(null);
        }catch (Exception e){
            return ResponseEntity.status(HttpStatus.INTERNAL_SERVER_ERROR).build();
        }
    }

    @GetMapping("/turtle/{homeId}")
    public ResponseEntity<Location> getTurtleCoordinate(@PathVariable Long homeId){
        try{
            return ResponseEntity.ok(homeService.fetchTurtleCoordinate(homeId,0));
        }catch (Exception e){
            return ResponseEntity.status(HttpStatus.INTERNAL_SERVER_ERROR).build();
        }
    }

    @PutMapping("/turtle/{homeId}")
    public ResponseEntity<Void> putTurtleCoordinate(@PathVariable Long homeId,@RequestBody Location coordinate){
        try{
            homeService.updateTurtleCoordinate(homeId,coordinate);
            return ResponseEntity.ok(null);
        }catch (Exception e){
            return ResponseEntity.status(HttpStatus.INTERNAL_SERVER_ERROR).build();
        }
    }
}
