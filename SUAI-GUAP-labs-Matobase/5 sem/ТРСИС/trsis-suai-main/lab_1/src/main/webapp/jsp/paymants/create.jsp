<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>Add New Paymant</title>
</head>
<body>
    <form method="post" action="${pageContext.request.contextPath}/paymants/create">
        <label for="electricityId">Electricity ID
            <input type="text" id="electricityId" name="electricityId">
        </label>
        <label for="waterId">Water ID
            <input type="text" id="waterId" name="waterId">
        </label>
        <label for="date">Date
            <input type="date" id="date" name="date">
        </label>
        <input type="submit" value="Add">
    </form>
</body>
</html>
