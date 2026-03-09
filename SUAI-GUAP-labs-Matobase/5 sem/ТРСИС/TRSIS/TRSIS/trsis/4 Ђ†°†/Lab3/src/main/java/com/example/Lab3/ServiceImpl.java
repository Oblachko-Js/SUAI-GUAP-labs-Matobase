package com.example.Lab3;

import org.springframework.stereotype.Service;

import java.util.ArrayList;
import java.util.List;

@Service
public class ServiceImpl implements com.example.Lab3.Service {


    @Override
    public void create(String group, String audience, String teacher, String name, int number) {
        DBHelper.dbLesson.add(new Lesson(DBHelper.dbLesson.get(DBHelper.dbLesson.size()-1).getId()+1,
                group,
                audience,
                teacher,
                name,
                number
        ));

    }

    @Override
    public List<Lesson> getAll() {
        return DBHelper.dbLesson;
    }

    @Override
    public List<Lesson> getByGroup(String group) {
        List<Lesson> les = new ArrayList<>();
        for(int i = 0; i<DBHelper.dbLesson.size(); ++i){
            if(DBHelper.dbLesson.get(i).getGroup().contentEquals(group)){
                les.add(DBHelper.dbLesson.get(i));
            }
        }
        return les;
    }

    @Override
    public boolean delete(int id) {
        for(int i = 0; i<DBHelper.dbLesson.size(); ++i){
            if(DBHelper.dbLesson.get(i).getId() == id){
                DBHelper.dbLesson.remove(i);
                return true;
            }
        }
        return false;
    }
}
