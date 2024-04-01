package com.ssafy.petpal.control.dto;

import lombok.Getter;
import lombok.Setter;

@Getter
public class MessageContainer {
    private A_Complete aComplete;
    private O_Complete oComplete;
    @Getter
    @Setter
    public static class A_Complete{

        private Long applianceId;
        private String applianceName;
        private Boolean isSuccess;
        private String controlType;
        private String currentStatus;
    }

    @Getter
    @Setter
    public static class O_Complete{
        private Long objectId;
        private String objectType;
        private Boolean isSuccess;
        private String controlType;
        private String currentStatus;

    }

}
