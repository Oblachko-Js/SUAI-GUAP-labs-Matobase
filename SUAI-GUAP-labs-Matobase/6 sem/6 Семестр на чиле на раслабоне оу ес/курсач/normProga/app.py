from flask import Flask, render_template, request, jsonify, session, redirect, url_for
from models import db, User, Task, Habit, RPGCharacter, Bonus, Boss

app = Flask(__name__)
app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:///habits.db'
app.config['SQLALCHEMY_TRACK_MODIFICATIONS'] = False
app.secret_key = 'your_secret_key'  # Секретный ключ для сессий
db.init_app(app)

# Создание базы данных
with app.app_context():
    db.create_all()

# Главная страница (регистрация/авторизация)
@app.route('/')
def index():
    return render_template('index.html')

# Личный кабинет
@app.route('/dashboard')
def dashboard():
    if 'user_id' not in session:
        return redirect(url_for('index'))  # Перенаправляем на главную страницу, если пользователь не авторизован
    return render_template('dashboard.html')

# Страница сражений с боссами
@app.route('/boss_fight')
def boss_fight():
    if 'user_id' not in session:
        return redirect(url_for('index'))  # Перенаправляем на главную страницу, если пользователь не авторизован
    return render_template('boss_fight.html')

# Регистрация
@app.route('/register', methods=['POST'])
def register():
    data = request.json
    username = data['username']
    email = data['email']
    password = data['password']

    # Проверка, существует ли пользователь с таким email
    if User.query.filter_by(email=email).first():
        return jsonify({"message": "Email already exists"}), 400

    # Проверка, существует ли пользователь с таким username
    if User.query.filter_by(username=username).first():
        return jsonify({"message": "Username already exists"}), 400

    # Создание нового пользователя
    new_user = User(username=username, email=email)
    new_user.set_password(password)
    db.session.add(new_user)
    db.session.commit()

    return jsonify({"message": "User registered successfully!"})

# Авторизация
@app.route('/login', methods=['POST'])
def login():
    data = request.json
    username = data['username']
    password = data['password']

    user = User.query.filter_by(username=username).first()
    if user and user.check_password(password):
        session['user_id'] = user.id
        return jsonify({"message": "Login successful!", "redirect": url_for('dashboard')})
    return jsonify({"message": "Invalid username or password"}), 401

# Выход
@app.route('/logout')
def logout():
    session.pop('user_id', None)
    return redirect(url_for('index'))

# Создание задачи
@app.route('/create_task', methods=['POST'])
def create_task():
    data = request.json
    user_id = session.get('user_id')
    if not user_id:
        return jsonify({"message": "Unauthorized"}), 401

    new_task = Task(title=data['title'], user_id=user_id)
    db.session.add(new_task)
    db.session.commit()
    return jsonify({"message": "Task created successfully!"})

# Получение списка задач
@app.route('/tasks', methods=['GET'])
def get_tasks():
    user_id = session.get('user_id')
    if not user_id:
        return jsonify({"message": "Unauthorized"}), 401

    tasks = Task.query.filter_by(user_id=user_id).all()
    return jsonify([{"id": task.id, "title": task.title, "completed": task.completed} for task in tasks])

# Создание привычки
@app.route('/create_habit', methods=['POST'])
def create_habit():
    data = request.json
    user_id = session.get('user_id')
    if not user_id:
        return jsonify({"message": "Unauthorized"}), 401

    new_habit = Habit(name=data['name'], difficulty=data['difficulty'], user_id=user_id)
    db.session.add(new_habit)
    db.session.commit()
    return jsonify({"message": "Habit created successfully!"})

# Получение списка привычек
@app.route('/habits', methods=['GET'])
def get_habits():
    user_id = session.get('user_id')
    if not user_id:
        return jsonify({"message": "Unauthorized"}), 401

    habits = Habit.query.filter_by(user_id=user_id).all()
    return jsonify([{"id": habit.id, "name": habit.name, "status": habit.status, "difficulty": habit.difficulty} for habit in habits])

# Создание персонажа
@app.route('/create_character', methods=['POST'])
def create_character():
    data = request.json
    user_id = session.get('user_id')
    if not user_id:
        return jsonify({"message": "Unauthorized"}), 401

    # Проверяем, есть ли уже персонаж у пользователя
    existing_character = RPGCharacter.query.filter_by(user_id=user_id).first()
    if existing_character:
        return jsonify({"message": "Character already exists"}), 400

    # Создаем нового персонажа с начальными значениями
    new_character = RPGCharacter(
        name=data['name'],
        level=1,
        health=10,
        mana=5,
        user_id=user_id
    )
    db.session.add(new_character)
    db.session.commit()
    return jsonify({"message": "Character created successfully!"})

# Получение данных персонажа
@app.route('/character/<int:user_id>', methods=['GET'])
def get_character(user_id):
    character = RPGCharacter.query.filter_by(user_id=user_id).first()
    if character:
        return jsonify({"name": character.name, "level": character.level, "health": character.health, "mana": character.mana})
    return jsonify({"message": "Character not found"}), 404

# Добавление бонуса
@app.route('/add_bonus', methods=['POST'])
def add_bonus():
    data = request.json
    user_id = session.get('user_id')
    if not user_id:
        return jsonify({"message": "Unauthorized"}), 401

    new_bonus = Bonus(name=data['name'], description=data['description'], points=data['points'], user_id=user_id)
    db.session.add(new_bonus)
    db.session.commit()
    return jsonify({"message": "Bonus added successfully!"})

# Получение списка бонусов
@app.route('/bonuses', methods=['GET'])
def get_bonuses():
    user_id = session.get('user_id')
    if not user_id:
        return jsonify({"message": "Unauthorized"}), 401

    bonuses = Bonus.query.filter_by(user_id=user_id).all()
    return jsonify([{"id": bonus.id, "name": bonus.name, "description": bonus.description, "points": bonus.points} for bonus in bonuses])

# Получение списка боссов
@app.route('/bosses', methods=['GET'])
def get_bosses():
    bosses = Boss.query.all()
    return jsonify([{"id": boss.id, "name": boss.name, "health": boss.health, "level": boss.level} for boss in bosses])

# Сражение с боссом
@app.route('/attack_boss/<int:boss_id>', methods=['POST'])
def attack_boss(boss_id):
    user_id = session.get('user_id')
    if not user_id:
        return jsonify({"message": "Unauthorized"}), 401

    boss = Boss.query.get(boss_id)
    character = RPGCharacter.query.filter_by(user_id=user_id).first()

    if not boss or not character:
        return jsonify({"message": "Boss or character not found"}), 404

    damage = character.level * 10
    boss.health -= damage

    if boss.health <= 0:
        db.session.delete(boss)
        db.session.commit()
        return jsonify({"message": "Boss defeated!"})

    db.session.commit()
    return jsonify({"message": f"Boss health: {boss.health}"})

if __name__ == '__main__':
    app.run(debug=True)