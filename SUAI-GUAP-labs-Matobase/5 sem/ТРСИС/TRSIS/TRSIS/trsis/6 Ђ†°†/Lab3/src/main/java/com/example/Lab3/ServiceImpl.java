package com.example.Lab3;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.ArrayList;
import java.util.List;

@Service
public class ServiceImpl implements com.example.Lab3.Service {

    @Autowired
    private LessonRepository LR;
    @Override
    public void create(String group, String audience, String teacher, String name, int number) {
        Lesson lesson = new Lesson(
                group,
                audience,
                teacher,
                name,
                number
        );
        LR.save(lesson);
    }

    @Override
    public List<Lesson> getAll() {
        List<Lesson> lessons = (List<Lesson>) LR.findAll();
        return lessons;
    }

    @Override
    public void delete(int id) {
        LR.deleteById((long) id);
    }
}
