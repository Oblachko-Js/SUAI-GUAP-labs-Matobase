<!--manage_accounts.php-->
<?php
// Подключение к базе данных
include('classes.php');
$db = new DB('localhost', 'root', '1234', 'habit_tracker');

$action = $_POST['action'];
$username = $_POST['username'];
$email = $_POST['email'];
$password = $_POST['password'];

switch ($action) {
    case 'create':
        $user = new User($username, $email, $password);
        if ($user->save($db)) {
            echo "Пользователь успешно создан!";
        } else {
            echo "Ошибка при создании пользователя.";
        }
        break;
    case 'read':
        $sql = "SELECT * FROM users WHERE username=?";
        $result = $db->query($sql, [$username]);
        if ($result->num_rows > 0) {
            while ($row = $result->fetch_assoc()) {
                echo "Имя: " . $row["username"] . " - Email: " . $row["email"] . "<br>";
            }
        } else {
            echo "Пользователь не найден.";
        }
        break;
    case 'update':
        $sql = "UPDATE users SET email=?, password=? WHERE username=?";
        if ($db->query($sql, [$email, password_hash($password, PASSWORD_BCRYPT), $username])) {
            echo "Пользователь успешно обновлен!";
        } else {
            echo "Ошибка при обновлении пользователя.";
        }
        break;
    case 'delete':
        $sql = "DELETE FROM users WHERE username=?";
        if ($db->query($sql, [$username])) {
            echo "Пользователь удален.";
        } else {
            echo "Ошибка при удалении пользователя.";
        }
        break;
}

$db->close();
?>
