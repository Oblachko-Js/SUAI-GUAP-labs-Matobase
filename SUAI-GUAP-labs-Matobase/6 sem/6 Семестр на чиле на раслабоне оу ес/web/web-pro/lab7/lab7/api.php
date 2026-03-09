<?php
header('Content-Type: application/json'); // Важно: заголовок JSON

// Подключение к базе
$conn = new mysqli('localhost', 'root', '', 'robots_db');
if ($conn->connect_error) {
    die(json_encode(['error' => 'Ошибка подключения к БД']));
}

// Обработка запроса JSON
if (isset($_GET['get_robot_json'])) {
    $id = (int)$_GET['id'];
    
    // Проверка существования робота
    $result = $conn->query("SELECT * FROM robots WHERE robot_id = $id");
    if ($result->num_rows === 0) {
        http_response_code(404);
        echo json_encode(['error' => 'Робот не найден']);
        $conn->close();
        exit();
    }
    
    // Получаем данные робота
    $robot = $result->fetch_assoc();
    
    // Получаем характеристики
    $features = [];
    $features_result = $conn->query("SELECT * FROM features WHERE robot_id = $id");
    while ($row = $features_result->fetch_assoc()) {
        $features[] = $row;
    }
    
    $robot['features'] = $features;
    echo json_encode($robot, JSON_UNESCAPED_UNICODE);
    $conn->close();
    exit();
}

// Если запрос не распознан
echo json_encode(['error' => 'Неверный запрос']);
?>