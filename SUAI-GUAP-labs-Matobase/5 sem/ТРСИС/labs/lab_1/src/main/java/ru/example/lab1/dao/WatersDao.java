package ru.example.lab1.dao;

import ru.example.lab1.domain.Water;

import java.util.HashMap;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;

public class WatersDao {
    private static WatersDao instance;

    private long id = 0L;
    private final Map<Long, Water> waters = new HashMap<>();

    public static WatersDao getInstance() {
        if (instance == null) {
            instance = new WatersDao();
        }
        return instance;
    }

    public Water save(Water entity) {
        entity.setId(id++);
        waters.put(entity.getId(), entity);
        return entity;
    }

    public void delete(Long id) {
        waters.remove(id);
    }

    public Water findById(Long id) {
        return waters.get(id);
    }

    public List<Water> findALl() {
        return new LinkedList<>(waters.values());
    }
}
