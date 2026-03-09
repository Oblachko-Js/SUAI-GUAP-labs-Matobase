<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>Add New Water Record</title>
</head>
<body>
    <form method="post" action="${pageContext.request.contextPath}/waters/create">
        <label for="source">Source
            <input type="text" id="source" name="source">
        </label>
        <label for="volume">Volume (L)
            <input type="text" id="volume" name="volume">
        </label>
        <label for="usageDate">Usage Date
            <input type="date" id="usageDate" name="usageDate">
        </label>
        <input type="submit" value="Add">
    </form>
</body>
</html>
