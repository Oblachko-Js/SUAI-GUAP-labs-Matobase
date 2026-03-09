package com.example.lab5.controllers;

import com.example.lab5.domain.Purchase;
import com.example.lab5.services.CarsService;
import com.example.lab5.services.CustomersService;
import com.example.lab5.services.PurchasesService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.validation.BindingResult;
import org.springframework.web.bind.annotation.*;

import javax.validation.Valid;
import java.util.List;

@Controller
@RequestMapping("/purchases")
public class PurchasesController {
    private final PurchasesService purchasesService;
    private final CarsService carsService;
    private final CustomersService customersService;

    @Autowired
    public PurchasesController(PurchasesService purchasesService,
                               CarsService carsService,
                               CustomersService customersService) {
        this.purchasesService = purchasesService;
        this.carsService = carsService;
        this.customersService = customersService;
    }

    @GetMapping
    public String list(Model model) {
        model.addAttribute("purchases", purchasesService.getAll());
        return "purchases/list";
    }

    @GetMapping("{id}")
    public String show(@PathVariable Long id, Model model) {
        model.addAttribute("purchases", List.of(purchasesService.get(id)));
        return "purchases/list";
    }

    @GetMapping("/new")
    public String createForm(@ModelAttribute("purchase") Purchase purchase, Model model) {
        model.addAttribute("cars", carsService.getAll());
        model.addAttribute("customers", customersService.getAll());
        return "purchases/new";
    }

    @PostMapping("/new")
    public String create(@Valid @ModelAttribute("purchase") Purchase purchase, BindingResult result) {
        if (result.hasErrors()) {
            System.out.println(result.getAllErrors());
            return "purchases/new";
        }
        purchasesService.save(purchase);
        return "redirect:/purchases";
    }

    @GetMapping("/{id}/delete")
    public String delete(@PathVariable Long id) {
        purchasesService.delete(id);
        return "redirect:/purchases";
    }
}
