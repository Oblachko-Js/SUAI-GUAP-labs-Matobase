import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.sql.SQLException;

public class DeleteServlet extends HttpServlet {
    private String responseTemplate =
            "<html>\n"+
                    "<body>\n"+
                    "<h2>Schedule of students' classes</h2>\n"+
                        "<form method='post'>" +
                            "<input name='group'><input type='submit' value='Delete by group'><br>" +
                        "</form>\n"+
                    "</body>\n"+
                 "</html>";


    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        try {
            process(req,resp);
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    @Override
    protected void doPost(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        try {
            process(req,resp);
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    private void process(HttpServletRequest req, HttpServletResponse resp) throws IOException, SQLException {
        resp.setStatus(200);
        String group = req.getParameter("group");
        if(group!=null){
            DBHelper.deleteLessonByGroup(group);
        }
        resp.setContentType("text/html;charset=UTF-8");
        resp.getWriter().write(responseTemplate);

    }
}
