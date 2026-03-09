package ru.example.lab1.domain;

public class Paymant {
    private Long id;
    private Long electricityId;
    private Long waterId;
    private String date;

    public Paymant(Long electricityId, Long waterId, String date) {
        this.electricityId = electricityId;
        this.waterId = waterId;
        this.date = date;
    }

    public Long getId() {
        return id;
    }

    public void setId(Long id) {
        this.id = id;
    }

    public Long getElectricityId() {
        return electricityId;
    }

    public void setElectricityId(Long electricityId) {
        this.electricityId = electricityId;
    }

    public Long getWaterId() {
        return waterId;
    }

    public void setWaterId(Long waterId) {
        this.waterId = waterId;
    }

    public String getDate() {
        return date;
    }

    public void setDate(String date) {
        this.date = date;
    }
}
