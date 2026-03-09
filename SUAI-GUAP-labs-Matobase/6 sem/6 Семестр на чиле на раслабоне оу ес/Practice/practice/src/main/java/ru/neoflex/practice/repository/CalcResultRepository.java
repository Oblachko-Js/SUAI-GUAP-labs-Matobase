package ru.neoflex.practice.repository;

import org.springframework.data.jpa.repository.JpaRepository;
import ru.neoflex.practice.model.CalcResult;

public interface CalcResultRepository extends JpaRepository<CalcResult, Long> {
}