package com.example.lab_3.dao;

import com.example.lab_3.domain.Car;
import org.springframework.stereotype.Component;

import java.util.HashMap;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;

@Component
public class CarsDao {
    private long id = 0L;
    private final Map<Long, Car> cars = new HashMap<>();

    public Car save(Car entity) {
        entity.setId(id++);
        cars.put(entity.getId(), entity);
        return entity;
    }

    public void delete(Long id) {
        cars.remove(id);
    }

    public Car findById(Long id) {
        return cars.get(id);
    }

    public List<Car> findALl() {
        return new LinkedList<>(cars.values());
    }
}
