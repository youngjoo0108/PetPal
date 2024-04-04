package com.ssafy.petpal.config;

import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;
import org.springframework.web.socket.server.standard.ServletServerContainerFactoryBean;

@Configuration
public class WebSocketContainerConfig {
    @Bean
    public ServletServerContainerFactoryBean createWebSocketContainer(){
        ServletServerContainerFactoryBean container = new ServletServerContainerFactoryBean();
        container.setMaxTextMessageBufferSize(1048576 * 50);
        container.setMaxBinaryMessageBufferSize(1048576 * 50);
        container.setMaxSessionIdleTimeout(300000L);
        return container;
    }
}
