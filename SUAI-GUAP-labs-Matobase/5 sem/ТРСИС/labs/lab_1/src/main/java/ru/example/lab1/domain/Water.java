package ru.example.lab1.domain;

public class Water {
    private Long id;
    private String source;
    private Integer volume;
    private String usageDate;

    public Water(String source, Integer volume, String usageDate) {
        this.source = source;
        this.volume = volume;
        this.usageDate = usageDate;
    }

    public Long getId() {
        return id;
    }

    public void setId(Long id) {
        this.id = id;
    }

    public String getSource() {
        return source;
    }

    public void setSource(String source) {
        this.source = source;
    }

    public Integer getVolume() {
        return volume;
    }

    public void setVolume(Integer volume) {
        this.volume = volume;
    }

    public String getUsageDate() {
        return usageDate;
    }

    public void setUsageDate(String usageDate) {
        this.usageDate = usageDate;
    }
}
