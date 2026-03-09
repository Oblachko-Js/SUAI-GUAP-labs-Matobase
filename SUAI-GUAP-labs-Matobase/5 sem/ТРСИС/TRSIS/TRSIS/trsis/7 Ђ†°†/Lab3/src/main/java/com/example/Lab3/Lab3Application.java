package com.example.Lab3;

import com.google.gson.Gson;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.kafka.annotation.EnableKafka;
import org.springframework.kafka.annotation.KafkaListener;

@SpringBootApplication
public class Lab3Application {


    public static void main(String[] args) {
        SpringApplication.run(Lab3Application.class, args);
    }

}
