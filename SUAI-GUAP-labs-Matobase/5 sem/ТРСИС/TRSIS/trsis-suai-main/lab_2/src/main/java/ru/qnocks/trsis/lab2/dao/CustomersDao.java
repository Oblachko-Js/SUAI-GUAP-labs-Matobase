package ru.qnocks.trsis.lab2.dao;


import org.springframework.stereotype.Component;
import ru.qnocks.trsis.lab2.domain.Customer;

import java.util.HashMap;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;

@Component
public class CustomersDao {
    private static CustomersDao instance;

    private long id = 0L;
    private final Map<Long, Customer> customers = new HashMap<>();

    public static CustomersDao getInstance() {
        if (instance == null) {
            instance = new CustomersDao();
        }
        return instance;
    }

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
