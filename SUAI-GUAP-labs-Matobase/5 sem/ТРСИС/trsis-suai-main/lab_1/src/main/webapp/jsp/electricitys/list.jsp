<%@ page contentType="text/html;charset=UTF-8" %>
<%@ taglib uri="http://java.sun.com/jsp/jstl/core" prefix="c" %>
<html>
<head>
    <title>Electricitys</title>
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
            <th>Type</th>
            <th>Power (kW)</th>
            <th>Installation Date</th>
            <th>Cost</th>
            <th></th>
        </tr>
        <br>
        <c:forEach items="${electricitys}" var="electricity">
            <tr>
                <td>${electricity.id}</td>
                <td>${electricity.type}</td>
                <td>${electricity.power}</td>
                <td>${electricity.installationDate}</td>
                <td>${electricity.cost}</td>
                <td><a href="${pageContext.servletContext.contextPath}/electricitys/delete/${electricity.id}">Delete</a></td>
            </tr>
        </c:forEach>
    </table>
    <br>
    <a href="${pageContext.request.contextPath}/electricitys/create">Add new electricity</a>
</body>
</html>
