package ru.qnocks.trsis.lab2.rest;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;
import ru.qnocks.trsis.lab2.dao.CustomersDao;
import ru.qnocks.trsis.lab2.dao.PurchasesDao;
import ru.qnocks.trsis.lab2.domain.Customer;

import javax.validation.Valid;
import java.util.List;

@RestController
@RequestMapping("/customers")
public class CustomerController {
    private final CustomersDao customersDao;
    private final PurchasesDao purchasesDao;

    @Autowired
    public CustomerController(CustomersDao customersDao, PurchasesDao purchasesDao) {
        this.customersDao = customersDao;
        this.purchasesDao = purchasesDao;
    }

    @GetMapping
    public ResponseEntity<List<Customer>> list() {
        return new ResponseEntity<>(customersDao.findALl(), HttpStatus.OK);
    }

    @GetMapping("{id}")
    public ResponseEntity<Customer> show(@PathVariable("id") Long id) {
        Customer customer = customersDao.findById(id);
        if (customer == null) {
            throw new IllegalArgumentException("Cannot find customer with id " + id);
        }
        return new ResponseEntity<>(customer, HttpStatus.OK);
    }

    @PostMapping
    public ResponseEntity<Customer> save(@Valid @RequestBody Customer customer) {
        return new ResponseEntity<>(customersDao.save(customer), HttpStatus.CREATED);
    }

    @DeleteMapping("{id}")
    private ResponseEntity<Void> delete(@PathVariable("id") Long id) {
        customersDao.delete(id);
        purchasesDao.deleteByCustomerId(id);
        return new ResponseEntity<>(HttpStatus.NO_CONTENT);
    }
}
