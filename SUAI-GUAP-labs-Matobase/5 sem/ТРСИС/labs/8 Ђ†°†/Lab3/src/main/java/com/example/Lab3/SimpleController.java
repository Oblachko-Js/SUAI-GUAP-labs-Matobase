package com.example.Lab3;

import com.google.gson.Gson;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.kafka.annotation.EnableKafka;
import org.springframework.kafka.annotation.KafkaListener;
import org.springframework.kafka.core.KafkaTemplate;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.*;

import java.util.List;
import java.util.UUID;

@EnableKafka
@Controller
public class SimpleController {
    @Autowired
    private KafkaTemplate<String,String> kafkaTemplate;
    private final Service service;
    @Autowired
    public SimpleController(Service service){
        this.service = service;
    }

    @KafkaListener(topics = "test")
    public void lessonListener(String les){
        System.out.println("KafkaListener is called");
        Gson gson = new Gson();
        Lesson lesson = gson.fromJson(les,Lesson.class);
        service.create(lesson);
    }
    @PostMapping("/lessons/{group}/{audience}/{teacher}/{name}/{number}")
    public ResponseEntity<?> create(@PathVariable("group") String group,
                                    @PathVariable("audience") String audience,
                                    @PathVariable("teacher") String teacher,
                                    @PathVariable("name") String name,
                                    @PathVariable("number") int number){

        Lesson les = new Lesson(group,audience,teacher,name,number);
        Gson gson = new Gson();

        kafkaTemplate.send("test", UUID.randomUUID().toString(),gson.toJson(les));

//        service.create(group,audience,teacher,name,number);

        return new ResponseEntity<>(HttpStatus.CREATED);
    }

    @GetMapping("/lessons")
    public ResponseEntity<List<Lesson>> getAll(){
        final List<Lesson> lessons = service.getAll();
        return lessons!= null && !lessons.isEmpty()
                ? new ResponseEntity<>(lessons,HttpStatus.OK)
                : new ResponseEntity<>(HttpStatus.NOT_FOUND);
    }

    @DeleteMapping("/lessons/{id}")
    public ResponseEntity<?> delete(@PathVariable(name="id") int id){
        service.delete(id);
        return new ResponseEntity<>(HttpStatus.OK);

    }
}
