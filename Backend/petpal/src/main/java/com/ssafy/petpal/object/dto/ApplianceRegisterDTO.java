package com.ssafy.petpal.object.dto;

import lombok.Data;
import lombok.Getter;
import org.locationtech.jts.geom.Coordinate;
import org.locationtech.jts.geom.GeometryFactory;
import org.locationtech.jts.geom.Point;

@Data
@Getter
public class ApplianceRegisterDTO {


    private String applianceType;

    private String applianceUUID;

    private Location coordinate;

    private Long homeId;

    private Long roomId;

    public static Point locationToPoint(Location coordinate){
        return new GeometryFactory().createPoint(new Coordinate(coordinate.getX(), coordinate.getY()));
    }
}
