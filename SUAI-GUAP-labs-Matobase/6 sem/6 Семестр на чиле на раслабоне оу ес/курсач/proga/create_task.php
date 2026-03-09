<!--create_task.php-->
<?php
// Подключение к базе данных и классов
include('classes.php');

// Настройки подключения к базе данных
$db = new DB('localhost', 'root', '1234', 'habit_tracker');

// Проверка метода запроса
if ($_SERVER['REQUEST_METHOD'] == 'POST') {
    // Получение данных из формы
    $title = trim($_POST['title']);
    $note = trim($_POST['note']);
    $difficulty = $_POST['difficulty'];
    $tags = trim($_POST['tags']);
    $deadline = $_POST['deadline'];

    // Проверка на обязательные поля
    if (empty($title) || empty($deadline)) {
        die("Необходимо заполнить все обязательные поля.");
    }

    // Вставка данных в базу данных
    $task = new Task($title, $note, $difficulty, $tags, $deadline);
    $result = $task->save($db);

    // Обработка результата
    if ($result) {
        echo "Задача успешно создана!";
    } else {
        // Вывод подробной ошибки
        echo "Ошибка при создании задачи. Ошибка: " . $db->getError();
    }
} else {
    echo "Неверный метод запроса.";
}

$db->close();
?>
