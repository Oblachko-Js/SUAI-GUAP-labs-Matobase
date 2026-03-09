package ru.example.lab1.dao;

import ru.example.lab1.domain.Purchase;

import java.util.*;

public class PurchasesDao {
    private static PurchasesDao instance;

    private long id = 0L;
    private final Map<Long, Purchase> purchases = new HashMap<>();

    public static PurchasesDao getInstance() {
        if (instance == null) {
            instance = new PurchasesDao();
        }
        return instance;
    }

    public Purchase save(Purchase entity) {
        entity.setId(id++);
        purchases.put(entity.getId(), entity);
        return entity;
    }

    public void delete(Long id) {
        purchases.remove(id);
    }

    public void deleteByCarId(Long id) {
        purchases.entrySet().removeIf(p -> p.getValue().getCarId().equals(id));
    }

    public void deleteByCustomerId(Long id) {
        purchases.entrySet().removeIf(p -> p.getValue().getCustomerId().equals(id));
    }

    public Purchase findById(Long id) {
        return purchases.get(id);
    }

    public List<Purchase> findALl() {
        return new LinkedList<>(purchases.values());
    }
}
