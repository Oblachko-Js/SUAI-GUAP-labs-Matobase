package com.example.Lab3;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

import java.util.List;

@RestController
@RequestMapping("/")
public class Controller {
    private final Service service;
    @Autowired
    public Controller(Service service){
        this.service = service;
    }

    @PostMapping("/lessons")
    public ResponseEntity<?> create(@RequestBody Lesson lesson){
        service.create(lesson);
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

    @DeleteMapping("/lessons/{group}")
    public ResponseEntity<?> delete(@PathVariable(name="group") String group){
        final boolean deleted = service.delete(group);
        return deleted
                ? new ResponseEntity<>(HttpStatus.OK)
                : new ResponseEntity<>(HttpStatus.NOT_MODIFIED);
    }
}