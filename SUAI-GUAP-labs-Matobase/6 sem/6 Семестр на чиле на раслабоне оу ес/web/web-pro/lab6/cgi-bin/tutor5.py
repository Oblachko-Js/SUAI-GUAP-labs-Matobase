#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import cgi
import cgitb
import sys
import os

# Включение отладки
cgitb.enable()

# Указываем кодировку для вывода
sys.stdout = open(sys.stdout.fileno(), mode='w', encoding='utf-8', buffering=1)

# Заголовок HTTP-ответа с указанием кодировки
print("Content-Type: text/html; charset=utf-8\n")

# Получаем данные формы
form = cgi.FieldStorage()

# Начало HTML-документа
html = """
<!DOCTYPE html>
<html>
<head>
    <meta charset="utf-8">
    <title>Анкета пользователя</title>
</head>
<body>
    <h1>Анкета пользователя</h1>
    <table border="2">
        <tr><th>Поле</th><th>Значение</th></tr>
"""

# Список полей для вывода
fields = [
    ('Фамилия', 'surname'),
    ('Имя', 'name'),
    ('Отчество', 'patronymic'),
    ('Тип робота', 'robot_type'),
    ('Функции робота', 'functions'),
    ('Возрастная категория', 'age_group'),
    ('Электронная почта', 'email'),
    ('Файл', 'file')
]

# Обработка данных формы
for field_name, field_key in fields:
    value = '(unknown)'
    if field_key in form:
        if field_key == 'file':
            file_item = form[field_key]
            if file_item.filename:
                # Сохраняем файл на сервере
                upload_dir = 'uploads'  # Папка для загрузки файлов
                if not os.path.exists(upload_dir):
                    os.makedirs(upload_dir)
                file_path = os.path.join(upload_dir, os.path.basename(file_item.filename))
                with open(file_path, 'wb') as f:
                    f.write(file_item.file.read())
                value = f'<img src="/{file_path}" alt="Загруженное изображение" width="200">'
        else:
            # Проверяем, является ли поле списком
            if isinstance(form[field_key], list):
                value = ', '.join([item.value for item in form[field_key]])
            else:
                value = form[field_key].value
    html += f'<tr><td>{field_name}</td><td>{value}</td></tr>'

# Формирование фразы
initials = f"{form['name'].value[0]}.{form['patronymic'].value[0]}." if 'patronymic' in form else f"{form['name'].value[0]}."
surname = form['surname'].value if 'surname' in form else '(unknown)'
robot_type = form['robot_type'].value if 'robot_type' in form else '(unknown)'

# Обработка поля functions (чекбоксы)
if 'functions' in form:
    if isinstance(form['functions'], list):
        functions = ', '.join([item.value for item in form['functions']])
    else:
        functions = form['functions'].value
else:
    functions = '(unknown)'

age_group = form['age_group'].value if 'age_group' in form else '(unknown)'

phrase = f"{initials} {surname} выбрал робота типа '{robot_type}', с функциями: {functions}, для возрастной категории: {age_group}."

# Добавление фразы в HTML
html += f"""
<h2>{phrase}</h2>
</table>
</body>
</html>
"""

# Запись данных в файл
data_to_save = [
    form['surname'].value if 'surname' in form else '(unknown)',
    form['name'].value if 'name' in form else '(unknown)',
    form['patronymic'].value if 'patronymic' in form else '(unknown)',
    form['robot_type'].value if 'robot_type' in form else '(unknown)',
    functions,
    age_group,
    form['email'].value if 'email' in form else '(unknown)'
]

with open('data.txt', 'a', encoding='utf-8') as f:
    f.write(' '.join(data_to_save) + '\n')

# Вывод HTML
print(html)