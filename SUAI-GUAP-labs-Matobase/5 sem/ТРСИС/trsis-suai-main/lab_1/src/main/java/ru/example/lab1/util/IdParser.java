package ru.example.lab1.util;

import javax.servlet.http.HttpServletRequest;

public class IdParser {
    public static long getId(HttpServletRequest req) {
        String url = req.getRequestURL().toString();
        return Long.parseLong(url.substring(url.lastIndexOf('/') + 1));
    }
}
