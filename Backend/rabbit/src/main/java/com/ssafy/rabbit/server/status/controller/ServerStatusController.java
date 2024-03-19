package com.ssafy.rabbit.server.status.controller;

import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RestController;

@RestController
public class ServerStatusController {
    @GetMapping("/rabbitTest") //test
    public String testAPI() {
        return "✅ RabbitMQ Service is up and running!";
    }
}
