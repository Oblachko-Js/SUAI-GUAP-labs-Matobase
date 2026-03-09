package com.example.lab5.controllers;

import com.example.lab5.domain.Customer;
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
@RequestMapping("/customers")
public class CustomersController {
    private final CustomersService customersService;
    private final PurchasesService purchasesService;

    @Autowired
    public CustomersController(CustomersService customersService, PurchasesService purchasesService) {
        this.customersService = customersService;
        this.purchasesService = purchasesService;
    }

    @GetMapping
    public String list(Model model) {
        model.addAttribute("customers", customersService.getAll());
        return "customers/list";
    }

    @GetMapping("{id}")
    public String show(@PathVariable Long id, Model model) {
        model.addAttribute("customers", List.of(customersService.get(id)));
        return "customers/list";
    }

    @GetMapping("/new")
    public String createForm(@ModelAttribute("customer") Customer customer) {
        return "customers/new";
    }

    @PostMapping("/new")
    public String create(@Valid @ModelAttribute Customer customer, BindingResult result) {
        if (result.hasErrors()) {
            System.out.println(result.getAllErrors());
            return "customers/new";
        }
        customersService.save(customer);
        return "redirect:/customers";
    }

    @GetMapping("/{id}/delete")
    public String delete(@PathVariable Long id) {
        purchasesService.deleteByCustomerId(id);
        customersService.delete(id);
        return "redirect:/customers";
    }
}
