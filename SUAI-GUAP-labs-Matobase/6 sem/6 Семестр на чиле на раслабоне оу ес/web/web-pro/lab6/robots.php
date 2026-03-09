<!DOCTYPE html>
<html lang="ru">
<head>
    <meta charset="UTF-8">
    <title>Роботы-игрушки | Управление базой</title>
    <style>
        body {
            font-family: Arial, sans-serif;
            margin: 20px;
            background-color: #f5f5f5;
        }
        h1 {
            color: #2c3e50;
            text-align: center;
        }
        table {
            width: 100%;
            border-collapse: collapse;
            margin: 20px 0;
            background-color: white;
            box-shadow: 0 0 10px rgba(0,0,0,0.1);
        }
        th, td {
            padding: 12px;
            text-align: left;
            border-bottom: 1px solid #ddd;
        }
        th {
            background-color: #3498db;
            color: white;
        }
        tr:hover {
            background-color: #f1f1f1;
        }
        .form-container {
            background-color: white;
            padding: 20px;
            margin: 20px 0;
            box-shadow: 0 0 10px rgba(0,0,0,0.1);
        }
        input, button, textarea {
            padding: 8px;
            margin: 5px 0;
            width: 100%;
            box-sizing: border-box;
        }
        button {
            background-color: #3498db;
            color: white;
            border: none;
            cursor: pointer;
            width: auto;
        }
        button:hover {
            background-color: #2980b9;
        }
        .action-buttons {
            display: flex;
            gap: 5px;
        }
        .matrix-section {
            background-color: white;
            padding: 20px;
            margin: 20px 0;
            box-shadow: 0 0 10px rgba(0,0,0,0.1);
        }
        canvas {
            border: 1px solid #ddd;
            margin-top: 10px;
        }
        /* Стили для характеристик */
        .feature-row {
            display: flex;
            gap: 10px;
            margin-bottom: 10px;
            align-items: center;
        }
        .feature-row input {
            flex: 1;
        }
        .remove-feature {
            background-color: #e74c3c;
            padding: 8px;
            color: white;
            border: none;
            cursor: pointer;
        }
        .remove-feature:hover {
            background-color: #c0392b;
        }
        #add-feature {
            margin-top: 10px;
            background-color: #2ecc71;
        }
        #add-feature:hover {
            background-color: #27ae60;
        }
        .matrix-table {
            border-collapse: collapse;
            margin: 10px 0;
        }
        .matrix-table td {
            border: 1px solid #ddd;
            padding: 5px;
            text-align: center;
        }
    </style>
</head>
<body>
    <?php
    //http://localhost/lab6/robots.php
    //http://localhost/phpmyadmin/
    // Подключение к MySQL
    $conn = new mysqli('localhost', 'root', '', 'robots_db');
    if ($conn->connect_error) {
        die("Ошибка подключения: " . $conn->connect_error);
    }

    // Обработка CRUD операций
    if ($_SERVER['REQUEST_METHOD'] === 'POST') {
        if (isset($_POST['add']) || isset($_POST['update'])) {
            // Обработка основных данных робота
            $name = $conn->real_escape_string($_POST['name']);
            $year = (int)$_POST['year'];
            $manufacturer = $conn->real_escape_string($_POST['manufacturer']);
            $price = (float)$_POST['price'];
            $description = $conn->real_escape_string($_POST['description']);

            if (isset($_POST['add'])) {
                $sql = "INSERT INTO robots (name, release_year, manufacturer, price, description) 
                        VALUES ('$name', $year, '$manufacturer', $price, '$description')";
                $conn->query($sql);
                $robot_id = $conn->insert_id;
            } else {
                $id = (int)$_POST['id'];
                $sql = "UPDATE robots SET 
                        name = '$name', 
                        release_year = $year, 
                        manufacturer = '$manufacturer', 
                        price = $price, 
                        description = '$description' 
                        WHERE robot_id = $id";
                $conn->query($sql);
                $robot_id = $id;
                
                // Удаляем старые характеристики
                $conn->query("DELETE FROM features WHERE robot_id = $robot_id");
            }

            // Добавляем новые характеристики
            if (!empty($_POST['features'])) {
                foreach ($_POST['features'] as $feature) {
                    $name = $conn->real_escape_string($feature['name']);
                    $value = $conn->real_escape_string($feature['value']);
                    $conn->query("INSERT INTO features (robot_id, feature_name, feature_value) 
                                 VALUES ($robot_id, '$name', '$value')");
                }
            }
            
            header("Location: robots.php");
            exit;
        }
    }

    if (isset($_GET['delete'])) {
        $id = (int)$_GET['delete'];
        $conn->query("DELETE FROM robots WHERE robot_id = $id");
        $conn->query("DELETE FROM features WHERE robot_id = $id");
        header("Location: robots.php");
        exit;
    }

    $edit_data = null;
    $features_data = [];
    if (isset($_GET['edit'])) {
        $id = (int)$_GET['edit'];
        $result = $conn->query("SELECT * FROM robots WHERE robot_id = $id");
        $edit_data = $result->fetch_assoc();
        
        // Получаем характеристики робота
        $features_result = $conn->query("SELECT * FROM features WHERE robot_id = $id");
        while ($row = $features_result->fetch_assoc()) {
            $features_data[] = $row;
        }
    }

    // Обработка матриц на PHP
    $matrixResult = '';
    $matrixText = '';
    $drawingResult = '';
    
    if (isset($_POST['generate_matrix'])) {
        $n = (int)$_POST['matrix_rows'];
        $m = (int)$_POST['matrix_cols'];
        
        // Генерация матрицы
        $matrix = [];
        for ($i = 0; $i < $n; $i++) {
            for ($j = 0; $j < $m; $j++) {
                $matrix[$i][$j] = rand(0, 99);
            }
        }
        
        // Расчет среднего
        $sum = 0;
        $count = 0;
        foreach ($matrix as $row) {
            foreach ($row as $value) {
                $sum += $value;
                $count++;
            }
        }
        $average = $sum / $count;
        
        // Подсчет элементов выше среднего по строкам
        $aboveAvgCounts = [];
        foreach ($matrix as $row) {
            $count = 0;
            foreach ($row as $value) {
                if ($value > $average) {
                    $count++;
                }
            }
            $aboveAvgCounts[] = $count;
        }
        
        // Формирование HTML для вывода матрицы
        $matrixHTML = '<table class="matrix-table">';
        foreach ($matrix as $row) {
            $matrixHTML .= '<tr>';
            foreach ($row as $value) {
                $matrixHTML .= '<td>' . $value . '</td>';
            }
            $matrixHTML .= '</tr>';
        }
        $matrixHTML .= '</table>';
        
        $matrixResult = $matrixHTML;
        $matrixText = "Среднее арифметическое: " . number_format($average, 2) . "\n";
        $matrixText .= "Элементов выше среднего, по строкам: " . implode(', ', $aboveAvgCounts);
    }

    // Обработка продвинутой части (рисование)
    if (isset($_POST['draw_pattern'])) {
        $rows = (int)$_POST['draw_rows'];
        $cols = (int)$_POST['draw_cols'];
        
        // Создаем "холст" в виде HTML таблицы
        $drawingHTML = '<table class="matrix-table">';
        for ($y = 0; $y < $rows; $y++) {
            $drawingHTML .= '<tr>';
            for ($x = 0; $x < $cols; $x++) {
                $color = ($x % 2 === 0) ? 'blue' : 'red';
                $drawingHTML .= '<td style="background-color: '.$color.'; width: 30px; height: 30px;"></td>';
            }
            $drawingHTML .= '</tr>';
        }
        $drawingHTML .= '</table>';
        
        $drawingResult = $drawingHTML;
    }
    ?>

    <h1>Управление базой роботов-игрушек</h1>

    <!-- Вывод через echo (базовое задание) -->
    <div class="echo-output">
        <h2>Вывод через echo (базовое задание)</h2>
        <?php
        $result = $conn->query("SELECT * FROM robots");
        if ($result->num_rows > 0) {
            echo "<table border='1'>";
            echo "<tr><th>Название</th><th>Год</th><th>Производитель</th><th>Цена</th><th>Описание</th></tr>";
            while ($row = $result->fetch_assoc()) {
                echo "<tr>";
                echo "<td>" . htmlspecialchars($row['name']) . "</td>";
                echo "<td>" . $row['release_year'] . "</td>";
                echo "<td>" . htmlspecialchars($row['manufacturer']) . "</td>";
                echo "<td>$" . $row['price'] . "</td>";
                echo "<td>" . htmlspecialchars($row['description']) . "</td>";
                echo "</tr>";
            }
            echo "</table>";
        } else {
            echo "<p>Нет данных о роботах</p>";
        }
        ?>
    </div>

    <!-- Расширенный вывод через printf -->
    <table>
        <thead>
            <tr>
                <th>Название</th>
                <th>Год выпуска</th>
                <th>Производитель</th>
                <th>Цена</th>
                <th>Описание</th>
                <th>Характеристики</th>
                <th>Дата добавления</th>
                <th>Действия</th>
            </tr>
        </thead>
        <tbody>
            <?php
            $result = $conn->query("
                SELECT r.*, 
                       GROUP_CONCAT(f.feature_name, ': ', f.feature_value SEPARATOR '; ') as features,
                       MAX(f.created_at) as last_feature_date
                FROM robots r
                LEFT JOIN features f ON r.robot_id = f.robot_id
                GROUP BY r.robot_id
            ");

            while ($row = $result->fetch_assoc()) {
                printf("<tr>
                    <td>%s</td>
                    <td>%d</td>
                    <td>%s</td>
                    <td>$%.2f</td>
                    <td>%s</td>
                    <td>%s</td>
                    <td>%s</td>
                    <td class='action-buttons'>
                        <a href='?edit=%d'><button>✏️</button></a>
                        <a href='?delete=%d' onclick='return confirm(\"Удалить робота?\")'><button>🗑️</button></a>
                    </td>
                </tr>",
                htmlspecialchars($row['name']),
                $row['release_year'],
                htmlspecialchars($row['manufacturer']),
                $row['price'],
                htmlspecialchars($row['description']),
                htmlspecialchars($row['features'] ?? 'Нет данных'),
                $row['last_feature_date'] ? date('d.m.Y H:i', strtotime($row['last_feature_date'])) : 'Нет данных',
                $row['robot_id'],
                $row['robot_id']);
            }
            ?>
        </tbody>
    </table>

    <div class="form-container">
        <h2><?= $edit_data ? 'Редактировать робота' : 'Добавить нового робота' ?></h2>
        <form method="POST">
            <?php if ($edit_data): ?>
                <input type="hidden" name="id" value="<?= $edit_data['robot_id'] ?>">
                <input type="hidden" name="update" value="1">
            <?php else: ?>
                <input type="hidden" name="add" value="1">
            <?php endif; ?>

            <input type="text" name="name" placeholder="Название" value="<?= $edit_data['name'] ?? '' ?>" required>
            <input type="number" name="year" placeholder="Год выпуска" value="<?= $edit_data['release_year'] ?? '' ?>" required>
            <input type="text" name="manufacturer" placeholder="Производитель" value="<?= $edit_data['manufacturer'] ?? '' ?>" required>
            <input type="number" step="0.01" name="price" placeholder="Цена" value="<?= $edit_data['price'] ?? '' ?>" required>
            <textarea name="description" placeholder="Описание" required><?= $edit_data['description'] ?? '' ?></textarea>
            
            <!-- Секция характеристик -->
            <div id="features-section">
                <h3>Характеристики</h3>
                <div id="features-container">
                    <?php if (!empty($features_data)): ?>
                        <?php foreach ($features_data as $index => $feature): ?>
                            <div class="feature-row">
                                <input type="text" name="features[<?= $index ?>][name]" placeholder="Название характеристики" 
                                       value="<?= htmlspecialchars($feature['feature_name']) ?>" required>
                                <input type="text" name="features[<?= $index ?>][value]" placeholder="Значение" 
                                       value="<?= htmlspecialchars($feature['feature_value']) ?>" required>
                                <button type="button" class="remove-feature">Удалить</button>
                            </div>
                        <?php endforeach; ?>
                    <?php else: ?>
                        <div class="feature-row">
                            <input type="text" name="features[0][name]" placeholder="Название характеристики" required>
                            <input type="text" name="features[0][value]" placeholder="Значение" required>
                            <button type="button" class="remove-feature">Удалить</button>
                        </div>
                    <?php endif; ?>
                </div>
                <button type="button" id="add-feature">Добавить характеристику</button>
            </div>
            
            <button type="submit"><?= $edit_data ? 'Обновить' : 'Добавить' ?></button>
            <?php if ($edit_data): ?>
                <a href="robots.php"><button type="button">Отмена</button></a>
            <?php endif; ?>
        </form>
    </div>

    <!-- Работа с матрицами -->
    <div class="matrix-section">
        <h2>Лабораторная работа №3 (Матрицы)</h2>
        
        <h3>Базовая часть</h3>
        <form method="POST">
            <input type="hidden" name="generate_matrix" value="1">
            <input type="number" name="matrix_rows" placeholder="Количество строк" value="5" required>
            <input type="number" name="matrix_cols" placeholder="Количество столбцов" value="5" required>
            <button type="submit">Сгенерировать матрицу</button>
        </form>
        <?= $matrixResult ?>
        <textarea rows="4" cols="50" readonly><?= $matrixText ?></textarea>
        
        <h3>Продвинутая часть</h3>
        <form method="POST">
            <input type="hidden" name="draw_pattern" value="1">
            <input type="number" name="draw_rows" placeholder="Количество рядов" value="6" required>
            <input type="number" name="draw_cols" placeholder="Количество колонок" value="6" required>
            <button type="submit">Нарисовать узор</button>
        </form>
        <?= $drawingResult ?>
    </div>

    <script>
    // Скрипт для управления характеристиками
    document.addEventListener('DOMContentLoaded', function() {
        const featuresContainer = document.getElementById('features-container');
        const addFeatureBtn = document.getElementById('add-feature');
        
        addFeatureBtn.addEventListener('click', function() {
            const index = featuresContainer.children.length;
            const div = document.createElement('div');
            div.className = 'feature-row';
            div.innerHTML = `
                <input type="text" name="features[${index}][name]" placeholder="Название характеристики" required>
                <input type="text" name="features[${index}][value]" placeholder="Значение" required>
                <button type="button" class="remove-feature">Удалить</button>
            `;
            featuresContainer.appendChild(div);
        });
        
        featuresContainer.addEventListener('click', function(e) {
            if (e.target.classList.contains('remove-feature')) {
                e.target.parentElement.remove();
                // Перенумеровываем оставшиеся поля
                const rows = featuresContainer.querySelectorAll('.feature-row');
                rows.forEach((row, index) => {
                    row.querySelector('input[name^="features"]').name = `features[${index}][name]`;
                    row.querySelector('input[name$="value]"]').name = `features[${index}][value]`;
                });
            }
        });
    });
    </script>

    <?php $conn->close(); ?>
</body>
</html>