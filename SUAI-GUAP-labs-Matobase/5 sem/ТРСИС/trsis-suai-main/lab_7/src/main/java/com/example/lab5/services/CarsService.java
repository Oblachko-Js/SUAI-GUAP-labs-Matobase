package com.example.lab5.services;

import com.example.lab5.domain.Car;
import com.example.lab5.repositories.CarsRepository;
import lombok.SneakyThrows;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.List;

@Service
public class CarsService {

    private final CarsRepository carsRepository;

    private final KafkaProducerService kafkaProducerService;

    @Autowired
    public CarsService(CarsRepository carsRepository, KafkaProducerService kafkaProducerService) {
        this.carsRepository = carsRepository;
        this.kafkaProducerService = kafkaProducerService;
    }

    public List<Car> getAll() {
        return (List<Car>) carsRepository.findAll();
    }

    public Car get(Long id) {
        return carsRepository.findById(id)
                .orElseThrow(() -> new IllegalArgumentException("Cannot find Car id: " + id));
    }

    public void save(Car car) {
        kafkaProducerService.sendMessage(car);
    }

    @SneakyThrows
    public Car update(Long id, Car car) {
        throw new NoSuchMethodException();
    }

    public void delete(Long id) {
        carsRepository.deleteById(id);
    }
}
