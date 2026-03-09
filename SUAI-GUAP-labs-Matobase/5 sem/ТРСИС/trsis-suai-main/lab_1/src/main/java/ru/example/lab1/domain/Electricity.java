package ru.example.lab1.domain;

public class Electricity {
    private Long id;
    private String type;
    private String power;
    private String installationDate;
    private Integer cost;

    // Конструктор с новыми полями
    public Electricity(String type, String power, String installationDate, Integer cost) {
        this.type = type;
        this.power = power;
        this.installationDate = installationDate;
        this.cost = cost;
    }

    // Геттеры и сеттеры для новых полей
    public Long getId() {
        return id;
    }

    public void setId(Long id) {
        this.id = id;
    }

    public String getType() {
        return type;
    }

    public void setType(String type) {
        this.type = type;
    }

    public String getPower() {
        return power;
    }

    public void setPower(String power) {
        this.power = power;
    }

    public String getInstallationDate() {
        return installationDate;
    }

    public void setInstallationDate(String installationDate) {
        this.installationDate = installationDate;
    }

    public Integer getCost() {
        return cost;
    }

    public void setCost(Integer cost) {
        this.cost = cost;
    }
}
