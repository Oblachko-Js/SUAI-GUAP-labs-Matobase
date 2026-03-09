package io.swagger;

import io.swagger.model.Lesson;
import io.swagger.model.Lessons;

public class DBHelper {
    static public Lessons db = new Lessons() {{
        new Lesson().numGroup("4131").audience("23-08").teacher("Ivanov").name("History").number(3);
        new Lesson().numGroup("4132").audience("23-10").teacher("Petrov").name("Physics").number(2);
        new Lesson().numGroup("4134").audience("22-18").teacher("Smirnov").name("Math").number(5);
    }};
}
