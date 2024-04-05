package com.ssafy.petpal.object.dto;

import lombok.Data;
import lombok.Getter;
import org.locationtech.jts.geom.Coordinate;
import org.locationtech.jts.geom.GeometryFactory;
import org.locationtech.jts.geom.Point;

@Data
@Getter
public class TargetRegisterDto {
    /* 오브젝트타입, 좌표, 이미지ID */
    private Long homeId; // token 정보로 homeId를 찾게 하는게 나으려나
    private Long imageId;
    private String objectType; // BookPile, Mug, PenHolder, Stapler
    private Location coordinate;

    public static Point locationToPoint(Location coordinate){
        return new GeometryFactory().createPoint(new Coordinate(coordinate.getX(), coordinate.getY()));
    }
}
