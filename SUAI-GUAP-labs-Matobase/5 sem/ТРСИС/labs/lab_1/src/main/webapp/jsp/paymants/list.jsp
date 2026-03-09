<%@ page contentType="text/html;charset=UTF-8" %>
<%@ taglib uri="http://java.sun.com/jsp/jstl/core" prefix="c" %>
<html>
<head>
    <title>Paymants</title>
    <style>
        table {
            width: 100%;
            border-collapse: collapse;
        }
        th, td {
            border: 1px solid black;
            padding: 8px;
            text-align: left;
        }
        th {
            background-color: #f2f2f2;
        }
        table a {
            color: red;
            text-decoration: none;
        }
    </style>
</head>
<body>
    <a href="${pageContext.request.contextPath}/">Home</a><br>
    <table>
        <tr>
            <th>Id</th>
            <th>Electricity ID</th>
            <th>Water ID</th>
            <th>Date</th>
            <th></th>
        </tr>
        <br>
        <c:forEach items="${paymants}" var="paymant">
            <tr>
                <td>${paymant.id}</td>
                <td>${paymant.electricityId}</td>
                <td>${paymant.waterId}</td>
                <td>${paymant.date}</td>
                <td><a href="${pageContext.servletContext.contextPath}/paymants/delete/${paymant.id}">Delete</a></td>
            </tr>
        </c:forEach>
    </table>
    <br>
    <a href="${pageContext.request.contextPath}/paymants/create">Add new paymant</a>
</body>
</html>
