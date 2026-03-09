package com.example.lab5.repositories;

import com.example.lab5.domain.Purchase;
import org.springframework.data.repository.CrudRepository;
import org.springframework.stereotype.Repository;

@Repository
public interface PurchasesRepository extends CrudRepository<Purchase, Long> {
}
