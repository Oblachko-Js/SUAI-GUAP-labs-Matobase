package com.example.Lab3;

import jakarta.persistence.*;

@Entity
public class Lesson {
    @Override
    public String toString() {
        return "group:" + num_group +", audience:"+audience + ", teacher:"+teacher+", subject:"+name+", number:"+number;
    }
    public Lesson() {
    }

    public Lesson(String num_group, String audience, String teacher, String name, int number) {
        this.num_group = num_group;
        this.audience = audience;
        this.teacher = teacher;
        this.name = name;
        this.number = number;
    }

    @Id
    @GeneratedValue(strategy = GenerationType.AUTO)
    private int id;
    private String num_group; // номер группы
    private String audience; // номер аудитории
    private String teacher; // фамилия преподавателя
    private String name; // название предмета
    private int number; // порядковый номер пары
//    public Lesson(int id,String group,String audience,String teacher,String name,int number){
//        this.id = id;
//        this.num_group = group;
//        this.audience = audience;
//        this.teacher = teacher;
//        this.name = name;
//        this.number = number;
//    }
    public int getId(){
        return id;
    }
    public void setId(int id){
        this.id = id;
    }
    public String getNum_group(){
        return num_group;
    }
    public void setNum_group(String num_group){
        this.num_group = num_group;
    }
    public String getAudience(){
        return audience;
    }
    public void setAudience(String audience){
        this.audience = audience;
    }
    public String getTeacher(){
        return teacher;
    }
    public void setTeacher(String teacher){
        this.teacher = teacher;
    }
    public String getName(){
        return name;
    }
    public void setName(String name){
        this.name = name;
    }

    public int getNumber(){
        return number;
    }
    public void setNumber(int number){
        this.number = number;
    }

}
