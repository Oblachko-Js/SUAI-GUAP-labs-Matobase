package ru.example.lab1.servlets.waters;

import ru.example.lab1.dao.WatersDao;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

@WebServlet("/waters")
public class WatersServlet extends HttpServlet {
    private final WatersDao watersDao = WatersDao.getInstance();

    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        resp.setContentType("text/html");
        req.setAttribute("waters", watersDao.findALl());
        req.getRequestDispatcher("/jsp/waters/list.jsp").forward(req, resp);
    }

    @Override
    protected void doPost(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        req.getRequestDispatcher("/jsp/waters/list.jsp").forward(req, resp);
    }
}
