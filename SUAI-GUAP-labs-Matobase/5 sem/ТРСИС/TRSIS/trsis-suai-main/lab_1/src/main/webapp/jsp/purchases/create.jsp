<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>Title</title>
</head>
<body>
    <form method="post" action="${pageContext.request.contextPath}/purchases/create">
        <label for="carId">Car ID
            <input type="text" id="carId" name="carId">
        </label>
        <label for="customerId">Customer ID
            <input type="text" id="customerId" name="customerId">
        </label>
        <label for="date">Date
            <input type="text" id="date" name="date">
        </label>
        <input type="submit" value="Add">
    </form>
</body>
</html>