<!DOCTYPE html>
<html lang="ru">
<head>
    <meta charset="UTF-8">
    <title>Суперкомпьютеры | Управление базой</title>
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
        input, button, textarea, select {
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
        .app-row {
            display: flex;
            gap: 10px;
            margin-bottom: 10px;
            align-items: center;
        }
        .app-row input, .app-row select, .app-row textarea {
            flex: 1;
        }
        .remove-app {
            background-color: #e74c3c;
            padding: 8px;
            color: white;
            border: none;
            cursor: pointer;
        }
        .remove-app:hover {
            background-color: #c0392b;
        }
        #add-app {
            margin-top: 10px;
            background-color: #2ecc71;
        }
        #add-app:hover {
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
        .echo-output table {
            width: auto;
            margin: 20px auto;
        }
        .echo-output th {
            background-color: #2c3e50;
        }
        .ajax-section {
            background-color: white;
            padding: 20px;
            margin: 20px 0;
            box-shadow: 0 0 10px rgba(0,0,0,0.1);
        }
    </style>
</head>
<body>
    <?php
    // Подключение к MySQL
    // http://localhost/phpmyadmin/index.php?route=/
    // http://localhost/lab6%C2%A0%E2%80%94%20%D0%BA%D0%BE%D0%BF%D0%B8%D1%8F/supercomputers.php
    $conn = new mysqli('localhost', 'root', '', 'supercomputers_db');
    if ($conn->connect_error) {
        die("Ошибка подключения: " . $conn->connect_error);
    }

    // Обработка CRUD операций
    if ($_SERVER['REQUEST_METHOD'] === 'POST') {
        if (isset($_POST['add']) || isset($_POST['update'])) {
            // Обработка основных данных суперкомпьютера
            $name = $conn->real_escape_string($_POST['name']);
            $country = $conn->real_escape_string($_POST['country']);
            $year = (int)$_POST['year'];
            $performance = $conn->real_escape_string($_POST['performance']);
            $description = $conn->real_escape_string($_POST['description']);

            if (isset($_POST['add'])) {
                $sql = "INSERT INTO supercomputers (name, country, year, performance, description) 
                        VALUES ('$name', '$country', $year, '$performance', '$description')";
                $conn->query($sql);
                $computer_id = $conn->insert_id;
            } else {
                $computer_id = (int)$_POST['id'];
                $sql = "UPDATE supercomputers SET 
                        name = '$name', 
                        country = '$country', 
                        year = $year, 
                        performance = '$performance', 
                        description = '$description' 
                        WHERE computer_id = $computer_id";
                $conn->query($sql);
            }

            // Обработка областей применения при обновлении
            if (isset($_POST['update'])) {
                // Получаем существующие области применения
                $existing_apps = [];
                $result = $conn->query("SELECT application_id FROM applications WHERE computer_id = $computer_id");
                while ($row = $result->fetch_assoc()) {
                    $existing_apps[] = $row['application_id'];
                }

                // Новые области применения из формы
                $submitted_apps = !empty($_POST['applications']) ? $_POST['applications'] : [];
                $submitted_app_ids = [];

                // Обновляем или добавляем области применения
                foreach ($submitted_apps as $index => $app) {
                    $name = $conn->real_escape_string($app['name']);
                    $desc = $conn->real_escape_string($app['description']);
                    $level = $conn->real_escape_string($app['level']);
                    
                    if (isset($app['application_id']) && !empty($app['application_id'])) {
                        // Обновляем существующую запись
                        $app_id = (int)$app['application_id'];
                        $conn->query("UPDATE applications SET 
                                     application_name = '$name', 
                                     application_description = '$desc', 
                                     importance_level = '$level' 
                                     WHERE application_id = $app_id AND computer_id = $computer_id");
                        $submitted_app_ids[] = $app_id;
                    } else {
                        // Добавляем новую запись
                        $conn->query("INSERT INTO applications (computer_id, application_name, application_description, importance_level) 
                                     VALUES ($computer_id, '$name', '$desc', '$level')");
                        $submitted_app_ids[] = $conn->insert_id;
                    }
                }

                // Удаляем области применения, которые не были отправлены в форме
                $apps_to_delete = array_diff($existing_apps, $submitted_app_ids);
                foreach ($apps_to_delete as $app_id) {
                    $conn->query("DELETE FROM applications WHERE application_id = $app_id AND computer_id = $computer_id");
                }
            } elseif (isset($_POST['add']) && !empty($_POST['applications'])) {
                // Добавляем области применения для нового суперкомпьютера
                foreach ($_POST['applications'] as $app) {
                    $name = $conn->real_escape_string($app['name']);
                    $desc = $conn->real_escape_string($app['description']);
                    $level = $conn->real_escape_string($app['level']);
                    $conn->query("INSERT INTO applications (computer_id, application_name, application_description, importance_level) 
                                 VALUES ($computer_id, '$name', '$desc', '$level')");
                }
            }
            
            header("Location: supercomputers.php");
            exit;
        }
    }

    if (isset($_GET['delete'])) {
        $id = (int)$_GET['delete'];
        $conn->query("DELETE FROM supercomputers WHERE computer_id = $id");
        header("Location: supercomputers.php");
        exit;
    }

    $edit_data = null;
    $apps_data = [];
    if (isset($_GET['edit'])) {
        $id = (int)$_GET['edit'];
        $result = $conn->query("SELECT * FROM supercomputers WHERE computer_id = $id");
        $edit_data = $result->fetch_assoc();
        
        // Получаем области применения
        $apps_result = $conn->query("SELECT * FROM applications WHERE computer_id = $id");
        while ($row = $apps_result->fetch_assoc()) {
            $apps_data[] = $row;
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
        
        // Находим и меняем местами максимальный и минимальный элементы в каждой строке
        $changes = [];
        for ($i = 0; $i < $n; $i++) {
            $minVal = $matrix[$i][0];
            $maxVal = $matrix[$i][0];
            $minIdx = 0;
            $maxIdx = 0;
            
            // Находим индексы мин и макс элементов
            for ($j = 1; $j < $m; $j++) {
                if ($matrix[$i][$j] < $minVal) {
                    $minVal = $matrix[$i][$j];
                    $minIdx = $j;
                }
                if ($matrix[$i][$j] > $maxVal) {
                    $maxVal = $matrix[$i][$j];
                    $maxIdx = $j;
                }
            }

            // Меняем местами
            $temp = $matrix[$i][$minIdx];
            $matrix[$i][$minIdx] = $matrix[$i][$maxIdx];
            $matrix[$i][$maxIdx] = $temp;
            
            $changes[] = "Строка " . ($i + 1) . ": мин ($minVal) и макс ($maxVal) поменяны местами";
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
        $matrixText = implode("\n", $changes);
    }

    // Обработка продвинутой части (рисование треугольного узора)
    if (isset($_POST['draw_pattern'])) {
        $rows = (int)$_POST['draw_rows'];
        $cols = (int)$_POST['draw_cols'];
        
        // Создаем "холст" в виде HTML таблицы
        $drawingHTML = '<table class="matrix-table">';
        for ($y = 0; $y < $rows; $y++) {
            $drawingHTML .= '<tr>';
            for ($x = 0; $x < $cols; $x++) {
                // Рисуем синие квадраты, если x меньше или равен номеру строки (y)
                $color = ($x <= $y) ? 'blue' : 'white';
                $drawingHTML .= '<td style="background-color: '.$color.'; width: 30px; height: 30px;"></td>';
            }
            $drawingHTML .= '</tr>';
        }
        $drawingHTML .= '</table>';
        
        $drawingResult = $drawingHTML;
    }
    ?>

    <h1>Управление базой данных суперкомпьютеров</h1>

    <!-- Вывод через echo (базовое задание) -->
    <div class="echo-output">
        <h2>Список суперкомпьютеров (вывод через echo)</h2>
        <?php
        $result = $conn->query("SELECT * FROM supercomputers");
        if ($result->num_rows > 0) {
            echo "<table border='1'>";
            echo "<tr><th>Название</th><th>Страна</th><th>Год</th><th>Производительность</th><th>Описание</th></tr>";
            while ($row = $result->fetch_assoc()) {
                echo "<tr>";
                echo "<td>" . htmlspecialchars($row['name']) . "</td>";
                echo "<td>" . htmlspecialchars($row['country']) . "</td>";
                echo "<td>" . $row['year'] . "</td>";
                echo "<td>" . htmlspecialchars($row['performance']) . "</td>";
                echo "<td>" . htmlspecialchars($row['description']) . "</td>";
                echo "</tr>";
            }
            echo "</table>";
        } else {
            echo "<p>Нет данных о суперкомпьютерах</p>";
        }
        ?>
    </div>

    <!-- AJAX-секция для подгрузки моделей -->
    <div class="ajax-section">
        <h2>AJAX-подгрузка моделей суперкомпьютеров</h2>
        <form id="ajax-form">
            <select id="manufacturer" name="manufacturer" required>
                <option value="">Выберите производителя</option>
                <option value="IBM">IBM</option>
                <option value="Cray">Cray</option>
                <option value="Fujitsu">Fujitsu</option>
                <option value="NVIDIA">NVIDIA</option>
                <option value="Intel">Intel</option>
            </select>
            
            <select id="model" name="model" disabled required>
                <option value="">Сначала выберите производителя</option>
            </select>
        </form>
    </div>

    <!-- Расширенный вывод через printf -->
    <table>
        <thead>
            <tr>
                <th>Название</th>
                <th>Страна</th>
                <th>Год создания</th>
                <th>Производительность</th>
                <th>Описание</th>
                <th>Области применения</th>
                <th>Действия</th>
            </tr>
        </thead>
        <tbody>
            <?php
            $result = $conn->query("
                SELECT s.*, 
                       GROUP_CONCAT(a.application_name SEPARATOR '; ') as applications
                FROM supercomputers s
                LEFT JOIN applications a ON s.computer_id = a.computer_id
                GROUP BY s.computer_id
            ");

            while ($row = $result->fetch_assoc()) {
                printf("<tr>
                    <td>%s</td>
                    <td>%s</td>
                    <td>%d</td>
                    <td>%s</td>
                    <td>%s</td>
                    <td>%s</td>
                    <td class='action-buttons'>
                        <a href='?edit=%d'><button>✏️</button></a>
                        <a href='?delete=%d' onclick='return confirm(\"Удалить суперкомпьютер?\")'><button>🗑️</button></a>
                    </td>
                </tr>",
                htmlspecialchars($row['name']),
                htmlspecialchars($row['country']),
                $row['year'],
                htmlspecialchars($row['performance']),
                htmlspecialchars($row['description']),
                htmlspecialchars($row['applications'] ?? 'Нет данных'),
                $row['computer_id'],
                $row['computer_id']);
            }
            ?>
        </tbody>
    </table>

    <div class="form-container">
        <h2><?= $edit_data ? 'Редактировать суперкомпьютер' : 'Добавить новый суперкомпьютер' ?></h2>
        <form method="POST">
            <?php if ($edit_data): ?>
                <input type="hidden" name="id" value="<?= $edit_data['computer_id'] ?>">
                <input type="hidden" name="update" value="1">
            <?php else: ?>
                <input type="hidden" name="add" value="1">
            <?php endif; ?>

            <input type="text" name="name" placeholder="Название" value="<?= $edit_data['name'] ?? '' ?>" required>
            <input type="text" name="country" placeholder="Страна" value="<?= $edit_data['country'] ?? '' ?>" required>
            <input type="number" name="year" placeholder="Год создания" min="1950" max="2025" value="<?= $edit_data['year'] ?? '' ?>" required>
            <input type="text" name="performance" placeholder="Производительность (флопс)" value="<?= $edit_data['performance'] ?? '' ?>" required>
            <textarea name="description" placeholder="Описание" required><?= $edit_data['description'] ?? '' ?></textarea>
            
            <!-- Секция областей применения -->
            <div id="apps-section">
                <h3>Области применения</h3>
                <div id="apps-container">
                    <?php if (!empty($apps_data)): ?>
                        <?php foreach ($apps_data as $index => $app): ?>
                            <div class="app-row">
                                <input type="text" name="applications[<?= $index ?>][name]" placeholder="Название области" value="<?= htmlspecialchars($app['application_name']) ?>" required>
                                <textarea name="applications[<?= $index ?>][description]" placeholder="Описание" required><?= htmlspecialchars($app['application_description']) ?></textarea>
                                <select name="applications[<?= $index ?>][level]" required>
                                    <option value="высокая" <?= $app['importance_level'] == 'высокая' ? 'selected' : '' ?>>Высокая</option>
                                    <option value="средняя" <?= $app['importance_level'] == 'средняя' ? 'selected' : '' ?>>Средняя</option>
                                    <option value="низкая" <?= $app['importance_level'] == 'низкая' ? 'selected' : '' ?>>Низкая</option>
                                </select>
                                <input type="hidden" name="applications[<?= $index ?>][application_id]" value="<?= $app['application_id'] ?>">
                                <button type="button" class="remove-app">Удалить</button>
                            </div>
                        <?php endforeach; ?>
                    <?php else: ?>
                        <div class="app-row">
                            <input type="text" name="applications[0][name]" placeholder="Название области" required>
                            <textarea name="applications[0][description]" placeholder="Описание" required></textarea>
                            <select name="applications[0][level]" required>
                                <option value="высокая">Высокая</option>
                                <option value="средняя">Средняя</option>
                                <option value="низкая">Низкая</option>
                            </select>
                            <button type="button" class="remove-app">Удалить</button>
                        </div>
                    <?php endif; ?>
                </div>
                <button type="button" id="add-app">Добавить область применения</button>
            </div>
            
            <button type="submit"><?= $edit_data ? 'Обновить' : 'Добавить' ?></button>
            <?php if ($edit_data): ?>
                <a href="supercomputers.php"><button type="button">Отмена</button></a>
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

    <!-- Расширеное задание AJAX -->
    <div class="ajax-extended-section" style="background-color: white; padding: 20px; margin: 20px 0; box-shadow: 0 0 10px rgba(0,0,0,0.1);">
        <h2>Расширенная работа с AJAX</h2>
        
        <div id="browser-info" style="margin-bottom: 20px; padding: 10px; background-color: #f8f9fa; border-radius: 5px;">
            <h3>Информация о браузере:</h3>
            <p id="browser-details">Определение браузера...</p>
            <p id="xhr-object">Объект XHR: загрузка информации...</p>
        </div>
        
        <div id="jquery-ajax-section" style="margin-top: 20px;">
            <h3>AJAX с использованием jQuery</h3>
            <button id="load-specs-btn" style="padding: 8px; background-color: #2ecc71; color: white; border: none; cursor: pointer;">
                Загрузить спецификации суперкомпьютеров
            </button>
            <div id="specs-results" style="margin-top: 10px;"></div>
        </div>
    </div>

    <!-- Подключаем jQuery -->
    <script src="https://code.jquery.com/jquery-3.6.0.min.js"></script>

    <script>
    // Скрипт для управления областями применения
    document.addEventListener('DOMContentLoaded', function() {
        const appsContainer = document.getElementById('apps-container');
        const addAppBtn = document.getElementById('add-app');
        
        addAppBtn.addEventListener('click', function() {
            const index = appsContainer.children.length;
            const div = document.createElement('div');
            div.className = 'app-row';
            div.innerHTML = `
                <input type="text" name="applications[${index}][name]" placeholder="Название области" required>
                <textarea name="applications[${index}][description]" placeholder="Описание" required></textarea>
                <select name="applications[${index}][level]" required>
                    <option value="высокая">Высокая</option>
                    <option value="средняя">Средняя</option>
                    <option value="низкая">Низкая</option>
                </select>
                <button type="button" class="remove-app">Удалить</button>
            `;
            appsContainer.appendChild(div);
        });
        
        appsContainer.addEventListener('click', function(e) {
            if (e.target.classList.contains('remove-app')) {
                e.target.parentElement.remove();
                // Перенумеровываем оставшиеся поля
                const rows = appsContainer.querySelectorAll('.app-row');
                rows.forEach((row, index) => {
                    row.querySelector('input[name^="applications"][name$="[name]"]').name = `applications[${index}][name]`;
                    row.querySelector('textarea[name^="applications"][name$="[description]"]').name = `applications[${index}][description]`;
                    row.querySelector('select[name^="applications"][name$="[level]"]').name = `applications[${index}][level]`;
                    const appIdInput = row.querySelector('input[name^="applications"][name$="[application_id]"]');
                    if (appIdInput) {
                        appIdInput.name = `applications[${index}][application_id]`;
                    }
                });
            }
        });

        // AJAX-подгрузка моделей суперкомпьютеров
        const manufacturerSelect = document.getElementById('manufacturer');
        const modelSelect = document.getElementById('model');
        
        manufacturerSelect.addEventListener('change', function() {
            const manufacturer = this.value;
            
            if (!manufacturer) {
                modelSelect.innerHTML = '<option value="">Сначала выберите производителя</option>';
                modelSelect.disabled = true;
                return;
            }
            
            // Создаем AJAX-запрос
            const xhr = new XMLHttpRequest();
            xhr.open('POST', 'ajax_models.php', true);
            xhr.setRequestHeader('Content-Type', 'application/x-www-form-urlencoded');
            
            xhr.onreadystatechange = function() {
                if (xhr.readyState === 4 && xhr.status === 200) {
                    const models = JSON.parse(xhr.responseText);
                    
                    modelSelect.innerHTML = '';
                    if (models.length > 0) {
                        modelSelect.disabled = false;
                        models.forEach(function(model) {
                            const option = document.createElement('option');
                            option.value = model;
                            option.textContent = model;
                            modelSelect.appendChild(option);
                        });
                    } else {
                        modelSelect.innerHTML = '<option value="">Нет моделей для этого производителя</option>';
                        modelSelect.disabled = true;
                    }
                }
            };
            
            xhr.send('manufacturer=' + encodeURIComponent(manufacturer));
        });
    });

    // Определение информации о браузере и объекте XHR
    document.addEventListener('DOMContentLoaded', function() {
        // Вывод информации о браузере
        const browserDetails = document.getElementById('browser-details');
        const userAgent = navigator.userAgent;
        let browserName;
        
        if (userAgent.indexOf("Firefox") > -1) {
            browserName = "Mozilla Firefox";
        } else if (userAgent.indexOf("SamsungBrowser") > -1) {
            browserName = "Samsung Internet";
        } else if (userAgent.indexOf("Opera") > -1 || userAgent.indexOf("OPR") > -1) {
            browserName = "Opera";
        } else if (userAgent.indexOf("Trident") > -1) {
            browserName = "Microsoft Internet Explorer";
        } else if (userAgent.indexOf("Edge") > -1) {
            browserName = "Microsoft Edge";
        } else if (userAgent.indexOf("Chrome") > -1) {
            browserName = "Google Chrome";
        } else if (userAgent.indexOf("Safari") > -1) {
            browserName = "Apple Safari";
        } else {
            browserName = "Неизвестный браузер";
        }
        
        browserDetails.innerHTML = `
            <strong>Браузер:</strong> ${browserName}<br>
            <strong>User Agent:</strong> ${userAgent}<br>
            <strong>Платформа:</strong> ${navigator.platform}
        `;
        
        // Вывод информации об объекте XHR
        const xhrObjectInfo = document.getElementById('xhr-object');
        const xhr = new XMLHttpRequest();
        const xhrMethods = [];
        const xhrProto = Object.getPrototypeOf(xhr);

        // Собираем только методы (функции)
        for (const prop of Object.getOwnPropertyNames(xhrProto)) {
            if (typeof xhr[prop] === 'function') {
                xhrMethods.push(prop);
            }
        }

        xhrObjectInfo.innerHTML = `
            <strong>Объект для асинхронного обмена:</strong> XMLHttpRequest<br>
            <strong>Основные методы:</strong> ${xhrMethods.join(', ')}<br>
            <small>(Полный список см. в консоли)</small>
        `;

        // Для отладки - вывод в консоль
        console.log('Все свойства XMLHttpRequest:', Object.getOwnPropertyNames(xhr));
        console.log('Методы XMLHttpRequest:', xhrMethods);
        
        // AJAX с использованием jQuery
        $('#load-specs-btn').click(function() {
            $.ajax({
                url: 'ajax_specs.php',
                type: 'GET',
                dataType: 'json',
                beforeSend: function() {
                    $('#specs-results').html('<p>Загрузка данных...</p>');
                },
                success: function(data) {
                    if (data && data.length > 0) {
                        let html = '<table style="width:100%; border-collapse: collapse; margin-top:10px;">';
                        html += '<tr><th style="padding:8px; border:1px solid #ddd;">Название</th><th style="padding:8px; border:1px solid #ddd;">Производительность</th><th style="padding:8px; border:1px solid #ddd;">Год</th></tr>';
                        
                        data.forEach(function(spec) {
                            html += `<tr>
                                <td style="padding:8px; border:1px solid #ddd;">${spec.name}</td>
                                <td style="padding:8px; border:1px solid #ddd;">${spec.performance}</td>
                                <td style="padding:8px; border:1px solid #ddd;">${spec.year}</td>
                            </tr>`;
                        });
                        
                        html += '</table>';
                        $('#specs-results').html(html);
                    } else {
                        $('#specs-results').html('<p>Нет данных о спецификациях</p>');
                    }
                },
                error: function() {
                    $('#specs-results').html('<p style="color:red;">Ошибка загрузки данных</p>');
                }
            });
        });
    });
    </script>

    <?php $conn->close(); ?>
</body>
</html>