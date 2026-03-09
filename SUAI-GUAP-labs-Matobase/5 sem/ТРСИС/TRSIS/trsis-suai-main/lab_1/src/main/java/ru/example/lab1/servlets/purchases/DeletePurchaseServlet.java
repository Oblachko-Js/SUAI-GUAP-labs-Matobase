package ru.example.lab1.servlets.purchases;

import ru.example.lab1.dao.PurchasesDao;
import ru.example.lab1.util.IdParser;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

@WebServlet("/purchases/delete/*")
public class DeletePurchaseServlet extends HttpServlet {
    private final PurchasesDao purchasesDao = PurchasesDao.getInstance();

    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        long id = IdParser.getId(req);
        purchasesDao.delete(id);
        resp.setContentType("text/html");
        resp.sendRedirect("/purchases");
    }
}
