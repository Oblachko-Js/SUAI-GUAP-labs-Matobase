package ru.example.lab1.dao;

import ru.example.lab1.domain.Paymant;

import java.util.*;

public class PaymantsDao {
    private static PaymantsDao instance;

    private long id = 0L;
    private final Map<Long, Paymant> paymants = new HashMap<>();

    public static PaymantsDao getInstance() {
        if (instance == null) {
            instance = new PaymantsDao();
        }
        return instance;
    }

    public Paymant save(Paymant entity) {
        entity.setId(id++);
        paymants.put(entity.getId(), entity);
        return entity;
    }

    public void delete(Long id) {
        paymants.remove(id);
    }

    public void deleteByElectricityId(Long id) {
        paymants.entrySet().removeIf(p -> p.getValue().getElectricityId().equals(id));
    }

    public void deleteByWaterId(Long id) {
        paymants.entrySet().removeIf(p -> p.getValue().getWaterId().equals(id));
    }

    public Paymant findById(Long id) {
        return paymants.get(id);
    }

    public List<Paymant> findALl() {
        return new LinkedList<>(paymants.values());
    }
}
