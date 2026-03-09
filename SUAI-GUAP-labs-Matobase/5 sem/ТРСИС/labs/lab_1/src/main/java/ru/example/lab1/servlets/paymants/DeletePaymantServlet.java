package ru.example.lab1.servlets.paymants;

import ru.example.lab1.dao.PaymantsDao;
import ru.example.lab1.util.IdParser;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

@WebServlet("/paymants/delete/*")
public class DeletePaymantServlet extends HttpServlet {
    private final PaymantsDao paymantsDao = PaymantsDao.getInstance();

    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        long id = IdParser.getId(req);
        paymantsDao.delete(id);
        resp.setContentType("text/html");
        resp.sendRedirect("/lab1/paymants");
    }
}
