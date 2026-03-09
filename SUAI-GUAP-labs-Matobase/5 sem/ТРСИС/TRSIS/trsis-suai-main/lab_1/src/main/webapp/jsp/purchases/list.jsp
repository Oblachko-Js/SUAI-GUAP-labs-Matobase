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
            <th>Car ID</th>
            <th>Customer ID</th>
            <th>Date</th>
            <th></th>
        </tr>
        <c:forEach items="${purchases}" var="purchase">
            <tr>
                <td>${purchase.id}</td>
                <td>${purchase.carId}</td>
                <td>${purchase.customerId}</td>
                <td>${purchase.date}</td>
                <td><a href="${pageContext.servletContext.contextPath}/purchases/delete/${purchase.id}">Delete</a></td>
            </tr>
        </c:forEach>
    </table>
    <a href="${pageContext.request.contextPath}/purchases/create">Add new purchase</a>
</body>
</html>
