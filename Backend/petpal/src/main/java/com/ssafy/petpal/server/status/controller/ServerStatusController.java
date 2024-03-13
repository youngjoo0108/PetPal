package com.ssafy.petpal.server.status.controller;

import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RestController;

@RestController
public class ServerStatusController {
    @GetMapping("/api/v1/test")
    public String testAPI() {
        return "Service is up and running!";
    }
}
