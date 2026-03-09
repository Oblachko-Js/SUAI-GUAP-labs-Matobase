public class Lesson {
    private int id;
    private String num_group; // номер группы
    private String audience; // номер аудитории
    private String teacher; // фамилия преподавателя
    private String name; // название предмета
    private int number; // порядковый номер пары
    public Lesson(int id,String group,String audience,String teacher,String name,int number){
        this.id = id;
        this.num_group = group;
        this.audience = audience;
        this.teacher = teacher;
        this.name = name;
        this.number = number;
    }
    int getId(){
        return id;
    }
    void setId(int id){
        this.id = id;
    }
    String getGroup(){
        return num_group;
    }
    void setGroup(String group){
        this.num_group = group;
    }
    String getAudience(){
        return audience;
    }
    void setAudience(String audience){
        this.audience = audience;
    }
    String getTeacher(){
        return teacher;
    }
    void setTeacher(String teacher){
        this.teacher = teacher;
    }
    String getName(){
        return name;
    }
    void setName(String name){
        this.name = name;
    }

    int getNumber(){
        return number;
    }
    void setNumber(int number){
        this.number = number;
    }

}
