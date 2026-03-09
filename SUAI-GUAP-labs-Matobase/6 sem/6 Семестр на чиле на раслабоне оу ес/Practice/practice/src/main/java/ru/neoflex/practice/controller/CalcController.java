package ru.neoflex.practice.controller;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;
import ru.neoflex.practice.model.CalcResult;
import ru.neoflex.practice.repository.CalcResultRepository;

import java.util.List;

@RestController
public class CalcController {

    @Autowired
    private CalcResultRepository repository;

    @GetMapping("/plus/{a}/{b}")
    public Integer plus(@PathVariable("a") Integer a, @PathVariable("b") Integer b) {
        int res = a + b;
        repository.save(new CalcResult(null, a, b, "plus", res));
        return res;
    }

    @GetMapping("/minus/{a}/{b}")
    public Integer minus(@PathVariable("a") Integer a, @PathVariable("b") Integer b) {
        int res = a - b;
        repository.save(new CalcResult(null, a, b, "minus", res));
        return res;
    }

    // API для получения всех сохранённых результатов калькулятора
    @GetMapping("/results")
    public List<CalcResult> getAllResults() {
        return repository.findAll();
    }
}