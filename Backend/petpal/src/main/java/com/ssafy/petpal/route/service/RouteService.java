package com.ssafy.petpal.route.service;

import com.ssafy.petpal.map.entity.Map;
import com.ssafy.petpal.map.repository.MapRepository;
import com.ssafy.petpal.route.dto.RouteDto;
import com.ssafy.petpal.route.entity.Route;
import com.ssafy.petpal.route.repository.RouteRepository;
import org.springframework.stereotype.Service;

@Service
public class RouteService {
    private final MapRepository mapRepository;
    private final RouteRepository routeRepository;

    public RouteService(MapRepository mapRepository, RouteRepository routeRepository) {
        this.mapRepository = mapRepository;
        this.routeRepository = routeRepository;
    }

    public RouteDto saveRoute(String homeId, String data) {
        Long mapId = findMapIdByHomeId(Long.valueOf(homeId));
        RouteDto routeDto = new RouteDto(mapId, data);
        Route route = new Route();
        route.setMapId(mapId);
        route.setData(data);
        routeRepository.save(route);
        return routeDto;
    }

    public Long findMapIdByHomeId(Long homeId) {
        return mapRepository.findByHomeId(homeId)
                .map(Map::getId)
                .orElseThrow(() -> new RuntimeException("Map not found with homeId: " + homeId));
    }

}
