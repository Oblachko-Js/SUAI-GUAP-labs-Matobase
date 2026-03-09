package com.example.lab5.services;

import com.example.lab5.domain.Car;
import com.example.lab5.domain.Customer;
import com.example.lab5.domain.Purchase;
import com.example.lab5.repositories.PurchasesRepository;
import lombok.SneakyThrows;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.List;

@Service
public class PurchasesService {
    private final PurchasesRepository purchasesRepository;
    private final CarsService carsService;
    private final CustomersService customersService;

    @Autowired
    public PurchasesService(PurchasesRepository purchasesRepository,
                            CarsService carsService,
                            CustomersService customersService) {
        this.purchasesRepository = purchasesRepository;
        this.carsService = carsService;
        this.customersService = customersService;
    }

    public List<Purchase> getAll() {
        return (List<Purchase>) purchasesRepository.findAll();
    }

    public Purchase get(Long id) {
        return purchasesRepository.findById(id)
                .orElseThrow(() -> new IllegalArgumentException("Cannot find Purchase id: " + id));
    }

    public Purchase save(Purchase purchase) {
        Long carId = purchase.getCar().getId();
        Car car = carsService.getAll().stream()
                .filter(d -> d.getId().equals(carId))
                .findFirst()
                .orElseThrow(() -> new IllegalArgumentException("Cannot find Car with id " + carId));

        Long customerId = purchase.getCustomer().getId();
        Customer customer = customersService.getAll().stream()
                .filter(p -> p.getId().equals(customerId))
                .findFirst()
                .orElseThrow(() -> new IllegalArgumentException("Cannot find Customer with id " + customerId));

        purchase.setCar(car);
        purchase.setCustomer(customer);

        return purchasesRepository.save(purchase);
    }

    @SneakyThrows
    public Purchase update(String id, Purchase purchase) {
        throw new NoSuchMethodException();
    }

    public void delete(Long id) {
        purchasesRepository.deleteById(id);
    }

    public void deleteByCarId(Long id) {
        Purchase purchase = getAll().stream()
                .filter(a -> a.getCar().getId().equals(id))
                .findFirst()
                .orElse(null);

        if (purchase == null) return;
        purchasesRepository.delete(purchase);
    }

    public void deleteByCustomerId(Long id) {
        Purchase purchase = getAll().stream()
                .filter(a -> a.getCustomer().getId().equals(id))
                .findFirst()
                .orElse(null);

        if (purchase == null) return;
        purchasesRepository.delete(purchase);
    }
}
