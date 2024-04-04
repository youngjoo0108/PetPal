package com.ssafy.petpal.object.dto;

import lombok.*;
import org.locationtech.jts.geom.Point;

@Data
@Getter
@Setter
@ToString
@AllArgsConstructor
@NoArgsConstructor
public class Location {
    private Double x;
    private Double y;

    public static Location pointToLocation(Point point) {
        double x = point.getX();
        double y = point.getY();
        return new Location(x, y);
    }
}
