package com.example.lab5.services;

import com.example.lab5.domain.Car;
import lombok.extern.slf4j.Slf4j;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.kafka.core.KafkaTemplate;
import org.springframework.stereotype.Service;

@Slf4j
@Service
public class KafkaProducerService {

    @Value("${app.kafka.topic}")
    private String TOPIC;

    private final KafkaTemplate<String, Car> kafkaTemplate;

    @Autowired
    public KafkaProducerService(KafkaTemplate<String, Car> kafkaTemplate) {
        this.kafkaTemplate = kafkaTemplate;
    }

    public void sendMessage(Car car) {
        log.info("--- KAFKA --- Sending some doctor: " + car);
        kafkaTemplate.send(TOPIC, car);
    }
}