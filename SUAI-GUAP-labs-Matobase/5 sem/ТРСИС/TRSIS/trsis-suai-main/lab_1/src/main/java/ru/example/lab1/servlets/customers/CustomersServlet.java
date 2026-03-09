package ru.example.lab1.servlets.customers;

import ru.example.lab1.dao.CarsDao;
import ru.example.lab1.dao.CustomersDao;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

@WebServlet("/customers")
public class CustomersServlet extends HttpServlet {
    private final CustomersDao customersDao = CustomersDao.getInstance();

    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        resp.setContentType("text/html");
        req.setAttribute("customers", customersDao.findALl());
        req.getRequestDispatcher("/jsp/customers/list.jsp").forward(req, resp);
    }

    @Override
    protected void doPost(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        req.getRequestDispatcher("/jsp/customers/list.jsp").forward(req, resp);
    }
}
