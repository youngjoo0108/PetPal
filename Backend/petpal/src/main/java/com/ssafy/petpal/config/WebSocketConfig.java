package com.ssafy.petpal.config;

import lombok.RequiredArgsConstructor;
import lombok.extern.slf4j.Slf4j;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.context.annotation.Configuration;
import org.springframework.messaging.simp.config.MessageBrokerRegistry;
import org.springframework.util.AntPathMatcher;
import org.springframework.web.socket.config.annotation.EnableWebSocketMessageBroker;
import org.springframework.web.socket.config.annotation.StompEndpointRegistry;
import org.springframework.web.socket.config.annotation.WebSocketMessageBrokerConfigurer;

@Slf4j
@Configuration
@EnableWebSocketMessageBroker
@RequiredArgsConstructor

public class WebSocketConfig implements WebSocketMessageBrokerConfigurer {
    @Value("${spring.rabbitmq.host}")
    private String host;

    @Value("${spring.rabbitmq.username}")
    private String username;

    @Value("${spring.rabbitmq.password}")
    private String password;

    @Value("${rabbitmq.client.id}")
    private String clientId;

    @Value("{rabbitmq.client.pw}")
    private String clientPw;

    @Override
    public void configureMessageBroker(MessageBrokerRegistry config) {
        //메시지 구독 url
        config.enableStompBrokerRelay("/exchange")
                .setClientLogin(clientId)
                .setClientPasscode(clientPw)
                .setSystemLogin(username)
                .setSystemPasscode(password)
                .setRelayHost(host)
                .setRelayPort(8083)
                .setVirtualHost("/");
        //메시지 발행 url
        config.setPathMatcher(new AntPathMatcher("."));
        config.setApplicationDestinationPrefixes("/pub");
    }

    @Override
    public void registerStompEndpoints(StompEndpointRegistry registry) {
        registry.addEndpoint("/api/ws")
                .setAllowedOriginPatterns("*");
        //.withSockJS();
    }
}
