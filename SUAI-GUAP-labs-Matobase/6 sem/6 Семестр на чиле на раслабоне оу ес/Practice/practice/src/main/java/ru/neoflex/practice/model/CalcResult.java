package ru.neoflex.practice.model;

import jakarta.persistence.*;

@Entity
public class CalcResult {
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Long id;

    private Integer a;
    private Integer b;
    private String operation;
    private Integer result;

    public CalcResult() {}

    public CalcResult(Long id, Integer a, Integer b, String operation, Integer result) {
        this.id = id;
        this.a = a;
        this.b = b;
        this.operation = operation;
        this.result = result;
    }

    // Геттеры и сеттеры
    public Long getId() { return id; }
    public void setId(Long id) { this.id = id; }
    public Integer getA() { return a; }
    public void setA(Integer a) { this.a = a; }
    public Integer getB() { return b; }
    public void setB(Integer b) { this.b = b; }
    public String getOperation() { return operation; }
    public void setOperation(String operation) { this.operation = operation; }
    public Integer getResult() { return result; }
    public void setResult(Integer result) { this.result = result; }
}