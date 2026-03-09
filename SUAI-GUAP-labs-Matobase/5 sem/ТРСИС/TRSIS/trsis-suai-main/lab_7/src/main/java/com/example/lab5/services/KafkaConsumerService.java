package com.example.lab5.services;

import com.example.lab5.domain.Car;
import com.example.lab5.repositories.CarsRepository;
import lombok.RequiredArgsConstructor;
import lombok.extern.slf4j.Slf4j;
import org.springframework.kafka.annotation.KafkaListener;
import org.springframework.stereotype.Service;

@Slf4j
@Service
@RequiredArgsConstructor
public class KafkaConsumerService {

    private final CarsRepository carsRepository;

    @KafkaListener(topics = "${app.kafka.topic}", groupId = "${app.kafka.group}")
    public void listen(Car car) {
        System.out.println("Received Doctor information : " + car);
        carsRepository.save(car);
    }
}


