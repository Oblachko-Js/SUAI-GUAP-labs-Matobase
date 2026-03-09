package ru.example.lab1.dao;

import ru.example.lab1.domain.Electricity;

import java.util.HashMap;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;

public class ElectricitysDao {
    private static ElectricitysDao instance;

    private long id = 0L;
    private final Map<Long, Electricity> electricitys = new HashMap<>();

    public static ElectricitysDao getInstance() {
        if (instance == null) {
            instance = new ElectricitysDao();
        }
        return instance;
    }

    public Electricity save(Electricity entity) {
        entity.setId(id++);
        electricitys.put(entity.getId(), entity);
        return entity;
    }

    public void delete(Long id) {
        electricitys.remove(id);
    }

    public Electricity findById(Long id) {
        return electricitys.get(id);
    }

    public List<Electricity> findALl() {
        return new LinkedList<>(electricitys.values());
    }
}
