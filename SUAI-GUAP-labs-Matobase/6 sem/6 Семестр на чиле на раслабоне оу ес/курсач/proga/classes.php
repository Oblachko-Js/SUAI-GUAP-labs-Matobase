<!--classes.php-->
<?php
class DB {
    private $conn;

    public function __construct($servername, $username, $password, $dbname) {
        $this->conn = new mysqli($servername, $username, $password, $dbname);

        if ($this->conn->connect_error) {
            die("Connection failed: " . $this->conn->connect_error);
        }
    }

    // Публичный метод для получения ошибки
    public function getError() {
        return $this->conn->error;
    }

    // Выполнение запроса
    public function query($sql, $params = []) {
        $stmt = $this->conn->prepare($sql);
        if ($stmt === false) {
            die('Ошибка подготовки запроса: ' . $this->getError());
        }
        if ($params) {
            $types = str_repeat('s', count($params)); // Предполагаем, что все параметры строки
            $stmt->bind_param($types, ...$params);
        }
        if (!$stmt->execute()) {
            die('Ошибка выполнения запроса: ' . $this->getError());
        }
        return $stmt->get_result();
    }

    // Закрытие соединения
    public function close() {
        $this->conn->close();
    }
}

class Task {
    public $id;
    public $title;
    public $note;
    public $difficulty;
    public $tags;
    public $deadline;

    public function __construct($title, $note, $difficulty, $tags, $deadline, $id = null) {
        $this->id = $id;
        $this->title = $title;
        $this->note = $note;
        $this->difficulty = $difficulty;
        $this->tags = $tags;
        $this->deadline = $deadline;
    }

    public function save($db) {
        $sql = "INSERT INTO tasks (title, note, difficulty, tags, deadline) VALUES (?, ?, ?, ?, ?)";
        $result = $db->query($sql, [$this->title, $this->note, $this->difficulty, $this->tags, $this->deadline]);

        // Получаем ID только что вставленной записи
        if ($result) {
            $this->id = $db->conn->insert_id; // Присваиваем id, сгенерированный базой данных
        }

        return $result;
    }

    public function markComplete($db) {
        if ($this->id === null) {
            return false; // Нет id, задача не существует
        }

        $sql = "UPDATE tasks SET completed = 1 WHERE id = ?";
        return $db->query($sql, [$this->id]);
    }
}

class User {
    public $id;
    public $username;
    public $email;
    public $password;

    public function __construct($username, $email, $password) {
        $this->username = $username;
        $this->email = $email;
        $this->password = password_hash($password, PASSWORD_BCRYPT); // Хешируем пароль
    }

    public function save($db) {
        // Проверяем, существует ли уже такой пользователь
        $sql = "SELECT id FROM users WHERE email = ?";
        $result = $db->query($sql, [$this->email]);
        if ($result->num_rows > 0) {
            return false; // Такой пользователь уже существует
        }

        $sql = "INSERT INTO users (username, email, password) VALUES (?, ?, ?)";
        return $db->query($sql, [$this->username, $this->email, $this->password]);
    }

    public function login($db) {
        $sql = "SELECT * FROM users WHERE email = ?";
        $result = $db->query($sql, [$this->email]);

        if ($result->num_rows > 0) {
            $row = $result->fetch_assoc();
            if (password_verify($this->password, $row['password'])) {
                // Успешный вход
                $this->id = $row['id'];
                return true;
            }
        }
        return false;
    }
}
?>
