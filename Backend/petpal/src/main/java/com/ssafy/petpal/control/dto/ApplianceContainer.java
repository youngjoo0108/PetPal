package com.ssafy.petpal.control.dto;

import lombok.Getter;
import lombok.Setter;

@Getter
public class ApplianceContainer {
    private Complete complete;
    private Toggle toggle;
    @Getter
    @Setter
    public static class Complete{

        private Long applianceId;
        private String applianceName;
        private Boolean isSuccess;
        private String controlType;
        private String currentStatus;
    }

    @Getter
    @Setter
    public static class Toggle{

    }

}
