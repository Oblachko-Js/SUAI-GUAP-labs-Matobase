<?php
header('Content-Type: text/plain'); // Важно: текстовый ответ

$conn = new mysqli('localhost', 'root', '', 'robots_db');
if ($conn->connect_error) {
    die("DB connection error");
}

if (isset($_POST['check_price'])) {
    $price = (float)$_POST['price'];
    $result = $conn->query("SELECT 1 FROM robots WHERE ROUND(price, 2) = ROUND($price, 2) LIMIT 1");
    echo ($result->num_rows > 0) ? "exists" : "available";
}

$conn->close();
?>