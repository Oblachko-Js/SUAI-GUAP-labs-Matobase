package com.example.lab5.controllers;

import com.example.lab5.domain.Car;
import com.example.lab5.services.CarsService;
import com.example.lab5.services.PurchasesService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.validation.BindingResult;
import org.springframework.web.bind.annotation.*;

import javax.validation.Valid;
import java.util.List;

@Controller
@RequestMapping("/cars")
public class CarsController {
    private final CarsService carsService;
    private final PurchasesService purchasesService;

    @Autowired
    public CarsController(CarsService carsService, PurchasesService purchasesService) {
        this.carsService = carsService;
        this.purchasesService = purchasesService;
    }

    @GetMapping
    public String list(Model model) {
        model.addAttribute("cars", carsService.getAll());
        return "cars/list";
    }

    @GetMapping("{id}")
    public String show(@PathVariable Long id, Model model) {
        model.addAttribute("cars", List.of(carsService.get(id)));
        return "cars/list";
    }

    @GetMapping("/new")
    public String createForm(@ModelAttribute("car") Car car) {
        return "cars/new";
    }

    @PostMapping("/new")
    public String create(@Valid @ModelAttribute Car car, BindingResult result) {
        if (result.hasErrors()) {
            System.out.println(result.getAllErrors());
            return "cars/new";
        }
        carsService.save(car);
        return "redirect:/cars";
    }

    @GetMapping("/{id}/delete")
    public String delete(@PathVariable Long id) {
        purchasesService.deleteByCarId(id);
        carsService.delete(id);
        return "redirect:/cars";
    }
}
