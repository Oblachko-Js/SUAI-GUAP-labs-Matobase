package ru.example.lab1.servlets.paymants;

import ru.example.lab1.dao.PaymantsDao;
import ru.example.lab1.domain.Paymant;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

@WebServlet("/paymants/create")
public class CreatePaymantServlet extends HttpServlet {
    private final PaymantsDao paymantsDao = PaymantsDao.getInstance();

    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        resp.setContentType("text/html");
        req.getRequestDispatcher("/jsp/paymants/create.jsp").forward(req, resp);
    }

    @Override
    protected void doPost(HttpServletRequest req, HttpServletResponse resp) throws IOException {
        Long electricityId = Long.parseLong(req.getParameter("electricityId"));
        Long waterId = Long.parseLong(req.getParameter("waterId"));
        String date = req.getParameter("date");

        Paymant paymant = new Paymant(electricityId, waterId, date);
        paymantsDao.save(paymant);

        req.setAttribute("paymants", paymantsDao.findALl());
        resp.sendRedirect("/lab1/paymants");
    }
}
