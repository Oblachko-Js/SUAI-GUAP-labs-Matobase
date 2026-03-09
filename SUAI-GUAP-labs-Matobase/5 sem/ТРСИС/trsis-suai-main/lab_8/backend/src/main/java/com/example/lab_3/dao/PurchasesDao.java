package com.example.lab_3.dao;

import com.example.lab_3.domain.Car;
import com.example.lab_3.domain.Customer;
import com.example.lab_3.domain.Purchase;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Component;

import java.util.HashMap;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;

@Component
public class PurchasesDao {
    private final CarsDao carsDao;
    private final CustomersDao customersDao;

    private long id = 0L;
    private final Map<Long, Purchase> purchases = new HashMap<>();

    @Autowired
    public PurchasesDao(CarsDao carsDao, CustomersDao customersDao) {
        this.carsDao = carsDao;
        this.customersDao = customersDao;
    }

    public Purchase save(Purchase entity) {
        Car car = carsDao.findById(entity.getCarId());
        Customer customer = customersDao.findById(entity.getCustomerId());
        if (car == null || customer == null) {
            throw new IllegalArgumentException
                    ("Cannot find Car [" + entity.getCarId() + "] or Customer [" + entity.getCustomerId() + "]");
        }
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
