package com.ssafy.petpal.config;

import com.google.auth.oauth2.GoogleCredentials;
import com.google.firebase.FirebaseApp;
import com.google.firebase.FirebaseOptions;
import com.google.firebase.messaging.FirebaseMessaging;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;

import java.io.ByteArrayInputStream;
import java.io.IOException;
import java.nio.charset.StandardCharsets;
import java.util.List;

@Configuration
public class FCMConfig {

    @Value("${firebase.project-id}")
    private String projectId;

    @Value("${firebase.private-key}")
    private String privateKey;

    @Value("${firebase.client-email}")
    private String clientEmail;

    @Value("${firebase.private-key-id}")
    private String privateKeyId;

    @Value("${firebase.client-id}")
    private String clientId;

    @Value("${firebase.auth-uri}")
    private String authUri;

    @Value("${firebase.token-uri}")
    private String tokenUri;

    @Value("${firebase.auth-provider-x509-cert-url}")
    private String authProvider;

    @Value("{$firebase.client-x509-cert-url}")
    private String clientX509;

    @Bean
    public FirebaseMessaging firebaseMessaging() throws IOException {

        GoogleCredentials credentials = GoogleCredentials.fromStream(
                new ByteArrayInputStream(
                        String.format(
                                "{\n" +
                                        "  \"type\": \"service_account\",\n" +
                                        "  \"project_id\": \"%s\",\n" +
                                        "  \"private_key_id\": \"%s\",\n" +
                                        "  \"private_key\": \"%s\",\n" +
                                        "  \"client_email\": \"%s\",\n" +
                                        "  \"client_id\": \"%s\",\n" +
                                        "  \"auth_uri\": \"%s\",\n" +
                                        "  \"token_uri\": \"%s\",\n" +
                                        "  \"auth_provider_x509_cert_url\": \"%s\",\n" +
                                        "  \"client_x509_cert_url\": \"%s\"\n" +
                                        "}",
                                projectId,
                                privateKeyId,
                                privateKey,
                                clientEmail,
                                clientId,
                                authUri,
                                tokenUri,
                                authProvider,
                                clientX509
                        ).getBytes(StandardCharsets.UTF_8)
                )
        );

        FirebaseOptions options = FirebaseOptions.builder()
                .setCredentials(credentials)
                .build();

        FirebaseApp firebaseApp = FirebaseApp.initializeApp(options);
        return FirebaseMessaging.getInstance(firebaseApp);
    }

    @Bean
    public GoogleCredentials googleCredentials() throws IOException {
        return GoogleCredentials.fromStream(new ByteArrayInputStream(
                        String.format("{\n" +
                                        "  \"type\": \"service_account\",\n" +
                                        "  \"project_id\": \"%s\",\n" +
                                        "  \"private_key_id\": \"%s\",\n" +
                                        "  \"private_key\": \"%s\",\n" +
                                        "  \"client_email\": \"%s\",\n" +
                                        "  \"client_id\": \"%s\",\n" +
                                        "  \"auth_uri\": \"%s\",\n" +
                                        "  \"token_uri\": \"%s\",\n" +
                                        "  \"auth_provider_x509_cert_url\": \"%s\",\n" +
                                        "  \"client_x509_cert_url\": \"%s\"\n" +
                                        "}", projectId, privateKeyId, privateKey.replace("\\n", "\n"), clientEmail, clientId, authUri, tokenUri, authProvider, clientX509)
                                .getBytes(StandardCharsets.UTF_8)))
                .createScoped(List.of("https://www.googleapis.com/auth/cloud-platform"));
    }
}