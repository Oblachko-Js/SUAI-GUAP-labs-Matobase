<%@ page contentType="text/html;charset=UTF-8" %>
<%@ taglib uri="http://java.sun.com/jsp/jstl/core" prefix="c" %>
<html>
<head>
    <title>Water Management</title>
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
    <a href="${pageContext.request.contextPath}/">Home</a>
    <br>
    <table>
        <tr>
            <th>Id</th>
            <th>Source</th>
            <th>Volume (L)</th>
            <th>Usage Date</th>
            <th></th>
        </tr>
        <br>
        <c:forEach items="${waters}" var="water">
            <tr>
                <td>${water.id}</td>
                <td>${water.source}</td>
                <td>${water.volume}</td>
                <td>${water.usageDate}</td>
                <td><a href="${pageContext.servletContext.contextPath}/waters/delete/${water.id}">Delete</a></td>
            </tr>
        </c:forEach>
    </table>
    <br>
    <a href="${pageContext.request.contextPath}/waters/create">Add new water record</a>
</body>
</html>
