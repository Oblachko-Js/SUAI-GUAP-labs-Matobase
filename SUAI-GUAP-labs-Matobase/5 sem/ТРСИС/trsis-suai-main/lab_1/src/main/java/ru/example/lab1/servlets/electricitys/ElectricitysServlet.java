package ru.example.lab1.servlets.electricitys;

import ru.example.lab1.dao.ElectricitysDao;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

@WebServlet("/electricitys")
public class ElectricitysServlet extends HttpServlet {
    private final ElectricitysDao electricitysDao = ElectricitysDao.getInstance();

    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        resp.setContentType("text/html");

        // Установка обновленного списка electricitys с новыми полями
        req.setAttribute("electricitys", electricitysDao.findALl());

        req.getRequestDispatcher("/jsp/electricitys/list.jsp").forward(req, resp);
    }

    @Override
    protected void doPost(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        req.getRequestDispatcher("/jsp/electricitys/list.jsp").forward(req, resp);
    }
}
