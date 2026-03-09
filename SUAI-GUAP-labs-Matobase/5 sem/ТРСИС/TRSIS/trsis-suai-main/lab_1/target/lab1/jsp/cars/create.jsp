<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>Title</title>
</head>
<body>
    <form method="post" action="${pageContext.request.contextPath}/cars/create">
        <label for="brand">Brand
            <input type="text" id="brand" name="brand">
        </label>
        <label for="year">Year
            <input type="text" id="year" name="year">
        </label>
        <label for="price">Price
            <input type="text" id="price" name="price">
        </label>
        <input type="submit" value="Add">
    </form>
</body>
</html>