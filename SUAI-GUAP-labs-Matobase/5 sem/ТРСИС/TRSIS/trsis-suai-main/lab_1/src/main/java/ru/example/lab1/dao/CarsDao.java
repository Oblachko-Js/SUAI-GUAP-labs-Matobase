package ru.example.lab1.dao;

import ru.example.lab1.domain.Car;

import java.util.HashMap;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;

public class CarsDao {
    private static CarsDao instance;

    private long id = 0L;
    private final Map<Long, Car> cars = new HashMap<>();

    public static CarsDao getInstance() {
        if (instance == null) {
            instance = new CarsDao();
        }
        return instance;
    }

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
