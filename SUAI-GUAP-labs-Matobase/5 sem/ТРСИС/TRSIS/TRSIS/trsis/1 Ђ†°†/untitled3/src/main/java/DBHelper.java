import java.sql.*;
import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;

public class DBHelper {
    static List<Lesson> list = new ArrayList<>();
    DBHelper(){
        list.add(new Lesson(0,"4136","23-08","Ivanov","Physics",1));
        list.add(new Lesson(1,"4136","23-10","Smirnov","Math",4));
        list.add(new Lesson(2,"4136","23-11","Sidorov","English",3));
    }

    public static List<Lesson> getAllLessons(){
        return list;
    }
    public static void addLesson(String group,String audience, String teacher,String name,int number) throws SQLException {
        Lesson les = new Lesson(list.size(),group,audience,teacher,name,number);
        list.add(les);
    }
    public static void deleteLessonByGroup(String group){
        list.removeIf(lesson -> (lesson.getGroup().contentEquals(group)));
    }
}
