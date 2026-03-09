package ru.example.lab1.servlets.cars;

import ru.example.lab1.dao.CarsDao;
import ru.example.lab1.domain.Car;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

@WebServlet("/cars/create")
public class CreateCarServlet extends HttpServlet {
    private final CarsDao carsDao = CarsDao.getInstance();

    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        resp.setContentType("text/html");
        req.getRequestDispatcher("/jsp/cars/create.jsp").forward(req, resp);
    }

    @Override
    protected void doPost(HttpServletRequest req, HttpServletResponse resp) throws IOException {
        String brand = req.getParameter("brand");
        String year = req.getParameter("year");
        Integer price = Integer.parseInt(req.getParameter("price"));

        Car car = new Car(brand, year, price);
        carsDao.save(car);

        req.setAttribute("cars", carsDao.findALl());
        resp.sendRedirect("/cars");
    }
}
