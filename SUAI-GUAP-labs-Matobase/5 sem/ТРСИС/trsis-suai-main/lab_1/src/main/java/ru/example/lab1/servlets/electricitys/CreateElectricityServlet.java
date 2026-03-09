package ru.example.lab1.servlets.electricitys;

import ru.example.lab1.dao.ElectricitysDao;
import ru.example.lab1.domain.Electricity;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

@WebServlet("/electricitys/create")
public class CreateElectricityServlet extends HttpServlet {
    private final ElectricitysDao electricitysDao = ElectricitysDao.getInstance();

    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        resp.setContentType("text/html");
        req.getRequestDispatcher("/jsp/electricitys/create.jsp").forward(req, resp);
    }

    @Override
    protected void doPost(HttpServletRequest req, HttpServletResponse resp) throws IOException {
        String type = req.getParameter("type");
        String power = req.getParameter("power");
        String installationDate = req.getParameter("installationDate");
        Integer cost = Integer.parseInt(req.getParameter("cost"));

        Electricity electricity = new Electricity(type, power, installationDate, cost);
        electricitysDao.save(electricity);

        req.setAttribute("electricitys", electricitysDao.findALl());
        resp.sendRedirect("/lab1/electricitys");
    }
}
