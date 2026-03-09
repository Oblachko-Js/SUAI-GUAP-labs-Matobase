import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.util.List;

public class ViewServlet extends HttpServlet {
    private String responseTemplate1 =
            "<html>\n"+
                    "<body>\n"+
                    "<h2>Schedule of students' classes</h2>\n"+
                    "<table>\n";
    private String responseTemplate2 =
                    "</table>\n"+
                            "</body>\n"+
                    "</html>";

    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        process(req,resp);
    }

    @Override
    protected void doPost(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        process(req,resp);
    }

    private void process(HttpServletRequest req, HttpServletResponse resp) throws IOException {
        resp.setStatus(200);
        resp.setContentType("text/html;charset=UTF-8");
        resp.getWriter().write(responseTemplate1);
        List<Lesson> tempList = DBHelper.getAllLessons();
        resp.getWriter().write("<tr>");
        resp.getWriter().write("<td> Number </td>");
        resp.getWriter().write("<td> Subject </td>");
        resp.getWriter().write("<td> Audience </td>");
        resp.getWriter().write("<td> Teacher </td>");
        resp.getWriter().write("<td> Group </td>");
        resp.getWriter().write("</tr>");
        for(int i=0;i<tempList.size();++i){
            resp.getWriter().write("<tr>");
            resp.getWriter().write("<td>" + tempList.get(i).getNumber() +"</td>");
            resp.getWriter().write("<td>" + tempList.get(i).getName() +"</td>");
            resp.getWriter().write("<td>" + tempList.get(i).getAudience() +"</td>");
            resp.getWriter().write("<td>" + tempList.get(i).getTeacher() +"</td>");
            resp.getWriter().write("<td>" + tempList.get(i).getGroup() +"</td>");
            resp.getWriter().write("</tr>");
        }
        resp.getWriter().write(responseTemplate2);
    }
}
