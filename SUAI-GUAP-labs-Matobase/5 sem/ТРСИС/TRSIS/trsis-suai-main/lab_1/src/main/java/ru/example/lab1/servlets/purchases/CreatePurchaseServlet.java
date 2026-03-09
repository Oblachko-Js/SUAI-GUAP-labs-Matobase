package ru.example.lab1.servlets.purchases;

import ru.example.lab1.dao.CustomersDao;
import ru.example.lab1.dao.PurchasesDao;
import ru.example.lab1.domain.Customer;
import ru.example.lab1.domain.Purchase;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

@WebServlet("/purchases/create")
public class CreatePurchaseServlet extends HttpServlet {
    private final PurchasesDao purchasesDao = PurchasesDao.getInstance();

    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        resp.setContentType("text/html");
        req.getRequestDispatcher("/jsp/purchases/create.jsp").forward(req, resp);
    }

    @Override
    protected void doPost(HttpServletRequest req, HttpServletResponse resp) throws IOException {
        Long carId = Long.parseLong(req.getParameter("carId"));
        Long customerId = Long.parseLong(req.getParameter("customerId"));
        String date = req.getParameter("date");

        Purchase purchase = new Purchase(carId, customerId, date);
        purchasesDao.save(purchase);

        req.setAttribute("purchases", purchasesDao.findALl());
        resp.sendRedirect("/purchases");
    }
}
