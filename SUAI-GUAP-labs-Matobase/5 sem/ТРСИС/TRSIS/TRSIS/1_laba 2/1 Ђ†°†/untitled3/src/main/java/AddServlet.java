import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.util.List;

public class AddServlet extends HttpServlet {
    private String responseTemplate =
                    "<html>\n"+
                        "<body>\n"+
                        "<h2>Schedule of students' classes</h2>\n"+
                            "<form method='post'>" +
                                "<label>Number</label><input name='number'><br>" +
                                "<label>Subject</label><input name='subject'><br>" +
                                "<label>Audience</label><input name='audience'><br>" +
                                "<label>Teacher</label><input name='teacher'><br>" +
                                "<label>Group</label><input name='group'><br>" +
                                "<input type='submit' value='Add'>"+
                            "</form>\n"+
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
        resp.getWriter().write(responseTemplate);
        String number = req.getParameter("number");
        String subject = req.getParameter("subject");
        String audience = req.getParameter("audience");
        String teacher = req.getParameter("teacher");
        String group = req.getParameter("group");
        if(number!=null && subject!=null && audience!=null && teacher!=null && group!=null){
            if(number!="" && subject!="" && audience!="" && teacher!="" && group!=""){
                try{
                    int num = Integer.parseInt(number);
                    DBHelper.addLesson(group,audience,teacher,subject,num);
                }catch(Exception ex){
                    System.out.println(ex);
                }
            }
        }
    }
}
