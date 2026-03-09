import re

def main():
    # Читать входной файл
    try:
        with open('fs.txt', 'r', encoding='utf-8') as file:
            content = file.read()
    except FileNotFoundError:
        print("Ошибка: Файл fs.txt не найден.")
        return

    # Парсинг секций
    alphabet = parse_section(content, r'A\s*=\s*\{(.*?)\};')
    variables = parse_section(content, r'X\s*=\s*\{(.*?)\};')
    axioms = parse_section(content, r'A1\s*=\s*\{(.*?)\};')
    rules_str = re.search(r'R\s*=\s*\{(.*?)\};', content, re.DOTALL)
    if rules_str:
        # Удаляем запятые и пробелы в конце строк правил
        rules = [line.strip().rstrip(',') for line in rules_str.group(1).split('\n') if '->' in line.strip()]
    else:
        print("Ошибка: Секция R не найдена.")
        return

    if not all([alphabet, variables, axioms, rules]):
        print("Ошибка: Не все секции найдены в файле.")
        return

    var_set = set(variables)
    alph_set = set(alphabet)

    # Отладочный вывод
    print("Алфавит:", alph_set)
    print("Переменные:", var_set)
    print("Аксиомы:", axioms)
    print("Правила:", rules)

    # Проверка входных данных на ошибки
    for ax in axioms:
        for c in ax:
            if c not in alph_set:
                print(f"Ошибка: Символ '{c}' в аксиоме '{ax}' не входит в алфавит {alph_set}.")
                return
    for rule in rules:
        try:
            left, right = rule.split('->')
            left = left.strip()
            right = right.strip()
            print(f"Проверка правила: {rule} (левая часть: '{left}', правая часть: '{right}')")
            for c in left:
                if c not in alph_set and c not in var_set:
                    print(f"Ошибка: Символ '{c}' в левой части правила '{rule}' не входит в алфавит {alph_set} или переменные {var_set}.")
                    return
            for c in right:
                if c and c not in alph_set and c not in var_set:
                    print(f"Ошибка: Символ '{c}' в правой части правила '{rule}' не входит в алфавит {alph_set} или переменные {var_set}.")
                    return
        except ValueError:
            print(f"Ошибка: Некорректный формат правила '{rule}'.")
            return

    # Симуляция для каждой аксиомы
    with open('result.txt', 'w', encoding='utf-8') as f:
        for axiom in axioms:
            current = axiom
            while True:
                applied = False
                for rule in rules:
                    left, right = rule.split('->')
                    left = left.strip()
                    right = right.strip()
                    # Построить parts
                    parts = []
                    for c in left:
                        if c in var_set:
                            parts.append(('var', c))
                        else:
                            parts.append(('fixed', c))
                    # Построить regex
                    group_idx = 1
                    var_groups = {}
                    pattern_parts = []
                    for typ, val in parts:
                        if typ == 'fixed':
                            pattern_parts.append(re.escape(val))
                        else:
                            pattern_parts.append('(.*)')
                            if val not in var_groups:
                                var_groups[val] = []
                            var_groups[val].append(group_idx)
                            group_idx += 1
                    pattern = ''.join(pattern_parts)
                    match = re.search(pattern, current)
                    if match:
                        # Проверить одинаковые значения для одинаковых переменных
                        sub = {}
                        consistent = True
                        for v, idxs in var_groups.items():
                            values = [match.group(idx) for idx in idxs]
                            if len(set(values)) != 1:
                                consistent = False
                                break
                            sub[v] = values[0]
                        if not consistent:
                            continue
                        # Построить right
                        right_build = ''
                        for c in right:
                            if c in var_set:
                                right_build += sub[c]
                            else:
                                right_build += c
                        # Заменить
                        start, end = match.span()
                        new_string = current[:start] + right_build + current[end:]
                        # Проверить символы в новой строке
                        for c in new_string:
                            if c not in alph_set:
                                print(f"Ошибка: В ходе вычисления произошла ошибка: Символ '{c}' не входит в алфавит {alph_set}.")
                                return
                        # Записать
                        f.write(current + '\n')
                        f.write(rule + '\n')
                        f.write(new_string + '\n\n')
                        current = new_string
                        applied = True
                        break
                if not applied:
                    break

    print("Вычисление прошло успешно.")

def parse_section(content, pattern):
    match = re.search(pattern, content, re.DOTALL)
    if match:
        items = [item.strip() for item in match.group(1).split(',') if item.strip()]
        return items
    return []

if __name__ == "__main__":
    main()