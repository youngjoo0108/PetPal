package com.ssafy.petpal.object.dto;

import lombok.Data;
import org.locationtech.jts.geom.Point;
@Data
public class ObjectRegisterDto {
    /* 오브젝트타입, 좌표, 이미지ID */
    private Long homeId; // token 정보로 homeId를 찾게 하는게 나으려나
    private Long imageId;
    private int objectType;
    private Point coordinate;
}
