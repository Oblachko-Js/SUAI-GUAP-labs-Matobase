package ru.example.lab1.servlets.paymants;

import ru.example.lab1.dao.PaymantsDao;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

@WebServlet("/paymants")
public class PaymantsServlet extends HttpServlet {
    private final PaymantsDao paymantsDao = PaymantsDao.getInstance();

    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        resp.setContentType("text/html");
        req.setAttribute("paymants", paymantsDao.findALl());
        req.getRequestDispatcher("/jsp/paymants/list.jsp").forward(req, resp);
    }

    @Override
    protected void doPost(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        req.getRequestDispatcher("/jsp/paymants/list.jsp").forward(req, resp);
    }
}
