<?php
header('Content-Type: application/json');

// Подключение к базе данных
$conn = new mysqli('localhost', 'root', '', 'supercomputers_db');
if ($conn->connect_error) {
    die(json_encode(['error' => "Ошибка подключения: " . $conn->connect_error]));
}

// Получаем данные о суперкомпьютерах
$result = $conn->query("SELECT name, performance, year FROM supercomputers ORDER BY year DESC LIMIT 5");
$specs = [];

while ($row = $result->fetch_assoc()) {
    $specs[] = [
        'name' => $row['name'],
        'performance' => $row['performance'],
        'year' => $row['year']
    ];
}

echo json_encode($specs);
$conn->close();
?>