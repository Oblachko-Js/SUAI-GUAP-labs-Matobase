<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>Add New Electricity</title>
</head>
<body>
    <form method="post" action="${pageContext.request.contextPath}/electricitys/create">
        <label for="type">Type
            <input type="text" id="type" name="type">
        </label>
        <label for="power">Power (kW)
            <input type="text" id="power" name="power">
        </label>
        <label for="installationDate">Installation Date
            <input type="date" id="installationDate" name="installationDate">
        </label>
        <label for="cost">Cost
            <input type="text" id="cost" name="cost">
        </label>
        <input type="submit" value="Add">
    </form>
</body>
</html>
