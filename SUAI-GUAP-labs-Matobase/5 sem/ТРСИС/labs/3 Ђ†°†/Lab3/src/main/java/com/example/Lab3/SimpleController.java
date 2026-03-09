package com.example.Lab3;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.*;

import java.util.List;

@Controller
public class SimpleController {
    private final Service service;
    @Autowired
    public SimpleController(Service service){
        this.service = service;
    }

    @PostMapping("/lessons/{group}/{audience}/{teacher}/{name}/{number}")
    public ResponseEntity<?> create(@PathVariable("group") String group,
                                    @PathVariable("audience") String audience,
                                    @PathVariable("teacher") String teacher,
                                    @PathVariable("name") String name,
                                    @PathVariable("number") int number){
        service.create(group,audience,teacher,name,number);
        return new ResponseEntity<>(HttpStatus.CREATED);
    }

    @GetMapping("/lessons")
    public ResponseEntity<List<Lesson>> getAll(){
        final List<Lesson> lessons = service.getAll();
        return lessons!= null && !lessons.isEmpty()
                ? new ResponseEntity<>(lessons,HttpStatus.OK)
                : new ResponseEntity<>(HttpStatus.NOT_FOUND);
    }
    @GetMapping("/lessons/{group}")
    public ResponseEntity<List<Lesson>> getGroup(@PathVariable(name="group") String group){
        final List<Lesson> lessons = service.getByGroup(group);
        return lessons!= null && !lessons.isEmpty()
                ? new ResponseEntity<>(lessons,HttpStatus.OK)
                : new ResponseEntity<>(HttpStatus.NOT_FOUND);
    }

    @DeleteMapping("/lessons/{id}")
    public ResponseEntity<?> delete(@PathVariable(name="id") int id){
        final boolean deleted = service.delete(id);
        return deleted
                ? new ResponseEntity<>(HttpStatus.OK)
                : new ResponseEntity<>(HttpStatus.NOT_MODIFIED);
    }
}
