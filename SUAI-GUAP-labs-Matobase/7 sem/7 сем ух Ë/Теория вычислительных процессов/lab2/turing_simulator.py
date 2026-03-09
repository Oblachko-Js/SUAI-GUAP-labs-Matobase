import sys

# Функция для загрузки алфавита из файла
def load_alphabet(filename):
    with open(filename, 'r', encoding='utf-8') as f:
        return set(f.read().strip().split())  # Используем set для быстрого поиска

# Функция для загрузки переходов из файла
def load_transitions(filename, alphabet):
    transitions = {}
    with open(filename, 'r', encoding='utf-8') as f:
        for line_num, line in enumerate(f, 1):
            line = line.strip()
            if not line or line.startswith('#'):  # Пропускаем пустые строки или комментарии
                continue
            parts = line.split()
            if len(parts) != 6 or parts[2] != '->':
                print(f"Неверный формат в строке {line_num}: {line}", file=sys.stderr)
                continue
            curr_state, curr_sym, _, new_state, new_sym, direction = parts
            if curr_sym not in alphabet:
                print(f"Символ '{curr_sym}' отсутствует в алфавите в строке {line_num}", file=sys.stderr)
                continue
            if new_sym not in alphabet and new_sym != '!':  # Разрешаем '!' как специальный символ
                print(f"Новый символ '{new_sym}' отсутствует в алфавите в строке {line_num}", file=sys.stderr)
                continue
            if direction not in {'>', '<'}:
                print(f"Неверное направление '{direction}' в строке {line_num}", file=sys.stderr)
                continue
            transitions[(curr_state, curr_sym)] = (new_state, new_sym, direction)
    return transitions

# Функция для загрузки начальной ленты из файла
def load_tape(filename, alphabet, blank='_'):
    with open(filename, 'r', encoding='utf-8') as f:
        tape_str = f.read().strip()  # Предполагаем, что лента — это одна строка без пробелов
    tape = list(tape_str)
    for sym in tape:
        if sym not in alphabet:
            raise ValueError(f"Неверный символ '{sym}' на начальной ленте, отсутствует в алфавите")
    return tape

# Симуляция машины Тьюринга
def simulate_tm(transitions, tape, initial_state='q0', blank='_', output_file='output.txt'):
    current_state = initial_state
    head = 0  # Начало с позиции 0
    with open(output_file, 'w', encoding='utf-8') as out:
        while True:
            # Расширение ленты, если головка выходит за пределы
            while head < 0:
                tape.insert(0, blank)
                head += 1
            while head >= len(tape):
                tape.append(blank)
            
            curr_sym = tape[head]
            
            # Вывод текущего состояния ленты и позиции головки
            tape_out = ''.join(tape)
            out.write(tape_out + '\n')
            out.write(' ' * head + '^' + '\n')
            
            # Проверка перехода
            key = (current_state, curr_sym)
            if key not in transitions:
                out.write(f"Нет перехода для состояния {current_state} и символа {curr_sym}, остановка.\n")
                break
            
            new_state, new_sym, direction = transitions[key]
            
            # Вывод выполненной команды с пробелами
            dir_char = '＞' if direction == '>' else '＜'
            cmd = f"{current_state} {curr_sym} → {new_state} {new_sym} {dir_char}"
            out.write(cmd + '\n')
            
            # Применение перехода
            if new_sym == '!':
                out.write("Машина Тьюринга остановлена по команде '!'.\n")
                break
            tape[head] = new_sym
            if direction == '>':
                head += 1
            else:
                head -= 1
            current_state = new_state

# Главный блок выполнения
if __name__ == "__main__":
    try:
        alphabet = load_alphabet('alphabet.txt')
        transitions = load_transitions('program.txt', alphabet)
        tape = load_tape('tape.txt', alphabet)
        simulate_tm(transitions, tape)
        print("Симуляция завершена. Результат записан в output.txt")
    except Exception as e:
        print(f"Ошибка: {e}", file=sys.stderr)