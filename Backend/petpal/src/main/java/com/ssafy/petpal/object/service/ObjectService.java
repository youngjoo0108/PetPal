package com.ssafy.petpal.object.service;

import com.ssafy.petpal.object.dto.ObjectRegisterDto;
import com.ssafy.petpal.object.entity.Appliance;
import com.ssafy.petpal.object.entity.ObjectEntity;
import com.ssafy.petpal.object.entity.Target;
import com.ssafy.petpal.object.repository.ApplianceRepository;
import com.ssafy.petpal.object.repository.ObjectRepository;
import com.ssafy.petpal.object.repository.TargetRepository;
import lombok.RequiredArgsConstructor;
import org.springframework.stereotype.Service;

@Service
@RequiredArgsConstructor
public class ObjectService {
    private final ObjectRepository objectRepository;
    private final TargetRepository targetRepository;
    private final ApplianceRepository applianceRepository;
    public void createObject(ObjectRegisterDto objectRegisterDto) {
        // 요청한 기기의 고유값. 토큰이 나을 거 같지만 일단 임시
        Long homeId = objectRegisterDto.getHomeId();

        ObjectEntity object = ObjectEntity.builder()
                .imageId(objectRegisterDto.getImageId())
                .objectType(objectRegisterDto.getObjectType())
                .cordinate(ObjectRegisterDto.locationToPoint(objectRegisterDto.getCoordinate()))
                .build();

        ObjectEntity objectEntity = objectRepository.save(object);
        // 오브젝트의 타입 ex( 0: 처리대상, 1: 가전, etc...)
        int type =objectEntity.getObjectType();

        if(type==0){ // 0이 타겟이라고 가정
            Target target = Target.builder()
                    .homeId(homeId)
                    .objectId(objectEntity.getId())
                    .build();
            //TODO: Target용 Repository 생성해놓고 save()
            targetRepository.save(target);
        }else if (type==1){ // 1이 가전이라고 가정
            Appliance appliance = Appliance.builder()
                    .homeId(homeId)
                    .objectId(objectEntity.getId())
                    .build();
            //TODO: Appliance용 Repository 생성해놓고 save()
            applianceRepository.save(appliance);
        }
    }

}
