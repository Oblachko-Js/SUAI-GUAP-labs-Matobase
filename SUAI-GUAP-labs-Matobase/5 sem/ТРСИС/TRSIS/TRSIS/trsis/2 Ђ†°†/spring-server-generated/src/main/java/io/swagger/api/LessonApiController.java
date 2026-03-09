package io.swagger.api;

import io.swagger.DBHelper;
import io.swagger.model.Lesson;
import io.swagger.model.Lessons;
import com.fasterxml.jackson.databind.ObjectMapper;
import io.swagger.v3.oas.annotations.Parameter;
import io.swagger.v3.oas.annotations.enums.ParameterIn;
import io.swagger.v3.oas.annotations.media.Schema;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.RestController;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RequestBody;

import javax.validation.Valid;
import javax.servlet.http.HttpServletRequest;
import java.io.IOException;
import java.util.List;

@javax.annotation.Generated(value = "io.swagger.codegen.v3.generators.java.SpringCodegen", date = "2023-09-13T19:36:10.460669586Z[GMT]")
@RestController
public class LessonApiController implements LessonApi {

    private static final Logger log = LoggerFactory.getLogger(LessonApiController.class);

    private final ObjectMapper objectMapper;

    private final HttpServletRequest request;

    @org.springframework.beans.factory.annotation.Autowired
    public LessonApiController(ObjectMapper objectMapper, HttpServletRequest request) {
        this.objectMapper = objectMapper;
        this.request = request;
    }

    public ResponseEntity<List<Lesson>> addLesson(@Parameter(in = ParameterIn.DEFAULT, description = "Добавление нового занятие", required=true, schema=@Schema()) @Valid @RequestBody Lesson body) {
        String accept = request.getHeader("Accept");
        if (accept != null && accept.contains("application/json")) {
            DBHelper.db.add(body);
            return new ResponseEntity<List<Lesson>>(DBHelper.db, HttpStatus.OK);
        }

        return new ResponseEntity<List<Lesson>>(HttpStatus.NOT_FOUND);
    }

    public ResponseEntity<Void> deleteLesson(@Parameter(in = ParameterIn.PATH, description = "Номер группы", required=true, schema=@Schema()) @PathVariable("num_group") String numGroup) {
        String accept = request.getHeader("Accept");
        for(int i=0;i<DBHelper.db.size();++i){
            if(DBHelper.db.get(i).getNumGroup().contentEquals(numGroup)){
                DBHelper.db.remove(i);
                break;
            }
        }
        return new ResponseEntity<Void>(HttpStatus.OK);
    }

    public ResponseEntity<List<Lesson>> getAllLessons() {
        String accept = request.getHeader("Accept");
        if (accept != null && accept.contains("application/json")) {
            return new ResponseEntity<List<Lesson>>((Lessons)DBHelper.db, HttpStatus.OK);
        }

        return new ResponseEntity<List<Lesson>>(HttpStatus.NOT_FOUND);
    }

}
