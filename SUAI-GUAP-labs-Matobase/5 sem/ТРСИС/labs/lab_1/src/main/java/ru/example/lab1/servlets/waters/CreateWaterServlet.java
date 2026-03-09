package ru.example.lab1.servlets.waters;

import ru.example.lab1.dao.WatersDao;
import ru.example.lab1.domain.Water;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

@WebServlet("/waters/create")
public class CreateWaterServlet extends HttpServlet {
    private final WatersDao watersDao = WatersDao.getInstance();

    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        resp.setContentType("text/html");
        req.getRequestDispatcher("/jsp/waters/create.jsp").forward(req, resp);
    }

    @Override
    protected void doPost(HttpServletRequest req, HttpServletResponse resp) throws IOException {
        String source = req.getParameter("source");
        Integer volume = Integer.parseInt(req.getParameter("volume"));
        String usageDate = req.getParameter("usageDate");

        Water water = new Water(source, volume, usageDate);
        watersDao.save(water);

        req.setAttribute("waters", watersDao.findALl()); // Обратите внимание на правильность метода findAll()
        resp.sendRedirect("/lab1/waters");
    }
}
