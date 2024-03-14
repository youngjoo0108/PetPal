package com.ssafy.rabbit.security.config;

import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;
import org.springframework.security.config.annotation.web.builders.HttpSecurity;
import org.springframework.security.config.annotation.web.configuration.EnableWebSecurity;
import org.springframework.security.web.SecurityFilterChain;

import static org.springframework.security.config.Customizer.withDefaults;

@Configuration
@EnableWebSecurity
public class TmpSecurityConfig {

    @Bean
    public SecurityFilterChain securityFilterChain(HttpSecurity http) throws Exception {
        http
                .authorizeHttpRequests((authorize) -> authorize
                        .requestMatchers("/api/v1/rabbitTest").permitAll()  // /api/v1/rabbitTest에 대한 접근을 모두에게 허용
                        .anyRequest().authenticated()  // 나머지 요청에 대해서는 인증을 요구
                )
                .httpBasic(withDefaults())  // HTTP Basic 인증 활성화
                .formLogin(withDefaults());  // 폼 로그인 활성화
        return http.build();
    }
}
