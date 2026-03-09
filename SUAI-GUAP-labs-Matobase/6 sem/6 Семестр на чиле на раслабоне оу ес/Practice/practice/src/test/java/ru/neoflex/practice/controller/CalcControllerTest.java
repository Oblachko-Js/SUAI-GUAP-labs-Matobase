package ru.neoflex.practice.controller;

import org.junit.jupiter.api.Test;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.autoconfigure.web.servlet.WebMvcTest;
import org.springframework.boot.test.mock.mockito.MockBean;
import org.springframework.test.web.servlet.MockMvc;
import ru.neoflex.practice.repository.CalcResultRepository;

import static org.springframework.test.web.servlet.request.MockMvcRequestBuilders.get;
import static org.springframework.test.web.servlet.result.MockMvcResultMatchers.*;

@WebMvcTest(CalcController.class)
public class CalcControllerTest {

    @Autowired
    private MockMvc mockMvc;

    @MockBean
    private CalcResultRepository repository;

    @Test
    void testPlus() throws Exception {
        mockMvc.perform(get("/plus/3/2"))
                .andExpect(status().isOk())
                .andExpect(content().string("5"));
    }

    @Test
    void testMinus() throws Exception {
        mockMvc.perform(get("/minus/3/2"))
                .andExpect(status().isOk())
                .andExpect(content().string("1"));
    }
}