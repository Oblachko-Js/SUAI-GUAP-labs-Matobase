package com.example.Lab3;

import com.example.Lab3.Lesson;

import java.util.List;

public interface Service{

    void create(String group,String audience,String teacher,String name,int number);

    List<Lesson> getAll();

    void delete(int id);
}