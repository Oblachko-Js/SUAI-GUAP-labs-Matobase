<%@ page contentType="text/html;charset=UTF-8" %>
<%@ taglib uri = "http://java.sun.com/jsp/jstl/core" prefix = "c" %>
<html>
<head>
    <title>Title</title>
</head>
<body>
    <a href="${pageContext.request.contextPath}/">Home</a>
    <table>
        <tr>
            <th>Id</th>
            <th>Name</th>
            <th>BirthDate</th>
            <th></th>
        </tr>
        <c:forEach items="${customers}" var="customer">
            <tr>
                <td>${customer.id}</td>
                <td>${customer.name}</td>
                <td>${customer.birthDate}</td>
                <td><a href="${pageContext.servletContext.contextPath}/customers/delete/${customer.id}">Delete</a></td>
            </tr>
        </c:forEach>
    </table>
    <a href="${pageContext.request.contextPath}/customers/create">Add new customer</a>
</body>
</html>
