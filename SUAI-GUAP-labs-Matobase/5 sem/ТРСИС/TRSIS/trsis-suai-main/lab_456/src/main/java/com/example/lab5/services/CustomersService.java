package com.example.lab5.services;

import com.example.lab5.domain.Customer;
import com.example.lab5.repositories.CustomersRepository;
import lombok.SneakyThrows;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.List;

@Service
public class CustomersService {
    private final CustomersRepository customersRepository;

    @Autowired
    public CustomersService(CustomersRepository customersRepository) {
        this.customersRepository = customersRepository;
    }

    public List<Customer> getAll() {
        return (List<Customer>) customersRepository.findAll();
    }

    public Customer get(Long id) {
        return customersRepository.findById(id)
                .orElseThrow(() -> new IllegalArgumentException("Cannot find Customer id: " + id));
    }

    public Customer save(Customer customer) {
        return customersRepository.save(customer);
    }

    @SneakyThrows
    public Customer update(Long id, Customer customer) {
        throw new NoSuchMethodException();
    }

    public void delete(Long id) {
        customersRepository.deleteById(id);
    }
}
