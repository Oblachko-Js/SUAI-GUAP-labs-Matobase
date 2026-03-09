package com.example.Lab3;

import org.springframework.stereotype.Service;

import java.util.ArrayList;
import java.util.List;

@Service
public class ServiceImpl implements com.example.Lab3.Service {


    @Override
    public void create(String group, String audience, String teacher, String name, int number) {

        DBHelper.db.add(new Lesson(DBHelper.db.get(DBHelper.db.size()-1).getId()+1,
                group,
                audience,
                teacher,
                name,
                number
        ));

    }

    @Override
    public List<Lesson> getAll() {
        return DBHelper.db;
    }

    @Override
    public List<Lesson> getByGroup(String group) {
        List<Lesson> les = new ArrayList<>();
        for(int i=0;i<DBHelper.db.size();++i){
            if(DBHelper.db.get(i).getGroup().contentEquals(group)){
                les.add(DBHelper.db.get(i));
            }
        }
        return les;
    }

    @Override
    public boolean delete(int id) {
        for(int i=0;i<DBHelper.db.size();++i){
            if(DBHelper.db.get(i).getId() == id){
                DBHelper.db.remove(i);
                return true;
            }
        }
        return false;
    }
}
