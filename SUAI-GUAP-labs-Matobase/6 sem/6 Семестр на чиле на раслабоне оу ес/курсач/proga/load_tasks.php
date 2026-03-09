<!--load_tasks.html-->
<?php
// Подключение к базе данных
$servername = "localhost";
$username = "root";
$password = "";
$dbname = "habit_tracker";

$conn = new mysqli($servername, $username, $password, $dbname);

if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}

// Загрузка задач из базы данных
$sql = "SELECT * FROM tasks";
$result = $conn->query($sql);

if ($result->num_rows > 0) {
    while($row = $result->fetch_assoc()) {
        echo "<li>" . $row["title"] . " (Сложность: " . $row["difficulty"] . ")</li>";
    }
} else {
    echo "<li>Нет задач</li>";
}

$conn->close();
?>