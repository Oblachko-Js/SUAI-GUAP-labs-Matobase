package com.example.lab_3.dao;

import com.example.lab_3.domain.Customer;
import org.springframework.stereotype.Component;

import java.util.HashMap;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;

@Component
public class CustomersDao {
    private long id = 0L;
    private final Map<Long, Customer> customers = new HashMap<>();

    public Customer save(Customer entity) {
        entity.setId(id++);
        customers.put(entity.getId(), entity);
        return entity;
    }

    public void delete(Long id) {
        customers.remove(id);
    }

    public Customer findById(Long id) {
        return customers.get(id);
    }

    public List<Customer> findALl() {
        return new LinkedList<>(customers.values());
    }
}
