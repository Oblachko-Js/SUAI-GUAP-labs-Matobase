package ru.example.lab1.servlets.customers;

import ru.example.lab1.dao.CustomersDao;
import ru.example.lab1.dao.PurchasesDao;
import ru.example.lab1.util.IdParser;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

@WebServlet("/customers/delete/*")
public class DeleteCustomerServlet extends HttpServlet {
    private final CustomersDao customersDao = CustomersDao.getInstance();
    private final PurchasesDao purchasesDao = PurchasesDao.getInstance();

    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        long id = IdParser.getId(req);
        customersDao.delete(id);
        purchasesDao.deleteByCustomerId(id);
        resp.setContentType("text/html");
        resp.sendRedirect("/customers");
    }
}
