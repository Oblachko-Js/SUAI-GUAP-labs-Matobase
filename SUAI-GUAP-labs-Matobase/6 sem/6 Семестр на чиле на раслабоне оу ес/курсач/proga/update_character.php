<!--update_character.php-->
<?php
// Обновление прогресса персонажа после выполнения задачи
$task_id = $_POST['task_id'];
$user_id = $_POST['user_id'];

// Логика обновления (например, увеличение уровня)
$sql = "UPDATE characters SET level = level + 1 WHERE user_id = $user_id";
$conn->query($sql);

echo "Персонаж улучшен!";
?>