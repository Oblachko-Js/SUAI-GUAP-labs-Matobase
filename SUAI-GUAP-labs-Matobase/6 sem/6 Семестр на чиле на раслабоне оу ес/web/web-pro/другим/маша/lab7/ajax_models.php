<?php
// Подключение к базе данных
$conn = new mysqli('localhost', 'root', '', 'supercomputers_db');
if ($conn->connect_error) {
    die("Ошибка подключения: " . $conn->connect_error);
}

// Получаем производителя из POST-запроса
$manufacturer = isset($_POST['manufacturer']) ? $conn->real_escape_string($_POST['manufacturer']) : '';

// Массив соответствия производителей и моделей 
$modelsData = [
    'IBM' => ['IBM Summit', 'IBM Sierra', 'IBM Watson'],
    'Cray' => ['Cray XT5', 'Cray XC50', 'Cray CS500'],
    'Fujitsu' => ['Fujitsu Fugaku', 'Fujitsu K computer'],
    'NVIDIA' => ['NVIDIA DGX-2', 'NVIDIA Selene'],
    'Intel' => ['Intel Aurora', 'Intel ASCI Red']
];

// Получаем модели для выбранного производителя
$models = isset($modelsData[$manufacturer]) ? $modelsData[$manufacturer] : [];

// Возвращаем данные в формате JSON
header('Content-Type: application/json');
echo json_encode($models);

$conn->close();
?>