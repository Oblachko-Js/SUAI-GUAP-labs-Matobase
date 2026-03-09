package ru.example.lab1.servlets.purchases;

import ru.example.lab1.dao.CustomersDao;
import ru.example.lab1.dao.PurchasesDao;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

@WebServlet("/purchases")
public class PurchasesServlet extends HttpServlet {
    private final PurchasesDao purchasesDao = PurchasesDao.getInstance();

    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        resp.setContentType("text/html");
        req.setAttribute("purchases", purchasesDao.findALl());
        req.getRequestDispatcher("/jsp/purchases/list.jsp").forward(req, resp);
    }

    @Override
    protected void doPost(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        req.getRequestDispatcher("/jsp/purchases/list.jsp").forward(req, resp);
    }
}
