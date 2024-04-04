package com.ssafy.petpal.map.dto;

import com.ssafy.petpal.object.dto.Location;
import lombok.AllArgsConstructor;
import lombok.Getter;
import lombok.Setter;
import org.locationtech.jts.geom.Coordinate;
import org.locationtech.jts.geom.GeometryFactory;
import org.locationtech.jts.geom.Point;

@Getter
@Setter
@AllArgsConstructor
public class MapDto {
    private Long homeId;
    private String data;
    private Location startGrid;

    public static Point locationToPoint(Location startGrid){
        return new GeometryFactory().createPoint(new Coordinate(startGrid.getX(), startGrid.getY()));
    }
}
