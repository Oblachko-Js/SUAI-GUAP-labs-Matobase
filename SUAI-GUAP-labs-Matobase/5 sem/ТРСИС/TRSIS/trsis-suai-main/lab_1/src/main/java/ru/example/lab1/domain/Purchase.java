package ru.example.lab1.domain;

public class Purchase {
    private Long id;
    private Long carId;
    private Long customerId;
    private String date;

    public Purchase(Long carId, Long customerId, String date) {
        this.carId = carId;
        this.customerId = customerId;
        this.date = date;
    }

    public Long getId() {
        return id;
    }

    public void setId(Long id) {
        this.id = id;
    }

    public Long getCarId() {
        return carId;
    }

    public void setCarId(Long carId) {
        this.carId = carId;
    }

    public Long getCustomerId() {
        return customerId;
    }

    public void setCustomerId(Long customerId) {
        this.customerId = customerId;
    }

    public String getDate() {
        return date;
    }

    public void setDate(String date) {
        this.date = date;
    }
}
