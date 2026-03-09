package com.example.Lab3;

import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;

@SpringBootApplication
public class Lab3Application {

    public static void main(String[] args) {
        DBHelper.dbLesson.add(new Lesson(0, "4132", "23-09", "Ivanov", "Physics", 1));
        DBHelper.dbLesson.add(new Lesson(1, "4133", "23-08", "Petrov", "Math", 3));
        DBHelper.dbLesson.add(new Lesson(2, "4134", "23-10", "Smirnov", "Programmin", 5));
        SpringApplication.run(Lab3Application.class, args);
    }

}
