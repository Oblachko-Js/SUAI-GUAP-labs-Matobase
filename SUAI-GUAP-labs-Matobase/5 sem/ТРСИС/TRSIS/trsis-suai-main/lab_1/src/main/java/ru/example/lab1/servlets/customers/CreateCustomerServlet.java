package ru.example.lab1.servlets.customers;

import ru.example.lab1.dao.CustomersDao;
import ru.example.lab1.domain.Car;
import ru.example.lab1.domain.Customer;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

@WebServlet("/customers/create")
public class CreateCustomerServlet extends HttpServlet {
    private final CustomersDao customersDao = CustomersDao.getInstance();

    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        resp.setContentType("text/html");
        req.getRequestDispatcher("/jsp/customers/create.jsp").forward(req, resp);
    }

    @Override
    protected void doPost(HttpServletRequest req, HttpServletResponse resp) throws IOException {
        String name = req.getParameter("name");
        String birthDate = req.getParameter("birthDate");

        Customer customer = new Customer(name, birthDate);
        customersDao.save(customer);

        req.setAttribute("customers", customersDao.findALl());
        resp.sendRedirect("/customers");
    }
}
