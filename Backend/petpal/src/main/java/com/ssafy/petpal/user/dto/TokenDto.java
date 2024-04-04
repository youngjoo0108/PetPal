package com.ssafy.petpal.user.dto;

public class TokenDto {
    private String token;

    // 기본 생성자
    public TokenDto() {}

    // getter와 setter
    public String getToken() {
        return token;
    }

    public void setToken(String token) {
        this.token = token;
    }
}
