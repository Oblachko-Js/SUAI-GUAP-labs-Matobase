package com.example.Lab3;

import com.example.Lab3.Lesson;

import java.util.List;

public interface Service{

    void create(Lesson lesson);

    List<Lesson> getAll();

    void delete(int id);
}