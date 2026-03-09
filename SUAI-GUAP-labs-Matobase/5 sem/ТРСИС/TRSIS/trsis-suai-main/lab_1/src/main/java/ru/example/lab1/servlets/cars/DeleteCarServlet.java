package ru.example.lab1.servlets.cars;

import ru.example.lab1.dao.CarsDao;
import ru.example.lab1.dao.PurchasesDao;
import ru.example.lab1.util.IdParser;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

@WebServlet("/cars/delete/*")
public class DeleteCarServlet extends HttpServlet {
    private final CarsDao carsDao = CarsDao.getInstance();
    private final PurchasesDao purchasesDao = PurchasesDao.getInstance();

    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        long id = IdParser.getId(req);
        carsDao.delete(id);
        purchasesDao.deleteByCarId(id);
        resp.setContentType("text/html");
        resp.sendRedirect("/cars");
    }
}
