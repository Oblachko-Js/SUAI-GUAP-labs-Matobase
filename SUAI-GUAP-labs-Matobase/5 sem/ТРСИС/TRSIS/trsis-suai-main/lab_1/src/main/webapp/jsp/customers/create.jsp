<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>Title</title>
</head>
<body>
    <form method="post" action="${pageContext.request.contextPath}/customers/create">
        <label for="name">Name
            <input type="text" id="name" name="name">
        </label>
        <label for="birthDate">BirthDate
            <input type="text" id="birthDate" name="birthDate">
        </label>
        <input type="submit" value="Add">
    </form>
</body>
</html>