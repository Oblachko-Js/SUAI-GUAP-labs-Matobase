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
            <th>Brand</th>
            <th>Year</th>
            <th>Price</th>
            <th></th>
        </tr>
        <c:forEach items="${cars}" var="car">
            <tr>
                <td>${car.id}</td>
                <td>${car.brand}</td>
                <td>${car.year}</td>
                <td>${car.price}</td>
                <td><a href="${pageContext.servletContext.contextPath}/cars/delete/${car.id}">Delete</a></td>
            </tr>
        </c:forEach>
    </table>
    <a href="${pageContext.request.contextPath}/cars/create">Add new car</a>
</body>
</html>
