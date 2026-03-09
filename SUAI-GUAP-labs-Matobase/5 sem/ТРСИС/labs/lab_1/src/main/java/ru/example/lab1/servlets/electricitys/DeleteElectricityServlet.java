package ru.example.lab1.servlets.electricitys;

import ru.example.lab1.dao.ElectricitysDao;
import ru.example.lab1.dao.PaymantsDao;
import ru.example.lab1.util.IdParser;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

@WebServlet("/electricitys/delete/*")
public class DeleteElectricityServlet extends HttpServlet {
    private final ElectricitysDao electricitysDao = ElectricitysDao.getInstance();
    private final PaymantsDao paymantsDao = PaymantsDao.getInstance();

    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        long id = IdParser.getId(req);
        electricitysDao.delete(id);
        paymantsDao.deleteByElectricityId(id);
        resp.setContentType("text/html");
        resp.sendRedirect("/lab1/electricitys");
    }
}
