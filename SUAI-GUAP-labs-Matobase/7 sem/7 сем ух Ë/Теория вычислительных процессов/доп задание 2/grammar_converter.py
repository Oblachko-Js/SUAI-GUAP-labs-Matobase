import os
from collections import defaultdict, deque
import pydot
import random

# =============================================
# Директория для результатов
# =============================================
RESULTS_DIR = "results"
os.makedirs(RESULTS_DIR, exist_ok=True)
print(f"📁 Результаты будут сохранены в папку: {RESULTS_DIR}")

# =============================================
# Парсинг контекстно-свободной грамматики из файла
# =============================================
def parse_grammar(file_path):
    grammar = defaultdict(list)
    non_terminals = set()
    terminals = set()
    start_symbol = None

    print(f"\n📂 Загрузка грамматики из файла: {file_path}")
    try:
        with open(file_path, 'r', encoding='utf-8') as f:
            for line_num, line in enumerate(f, 1):
                line = line.strip()
                if not line or line.startswith('#'):
                    continue
                if '->' not in line:
                    print(f"⚠️  Предупреждение: строка {line_num} пропущена (нет '->'): {line}")
                    continue
                
                if line.count('->') > 1:
                    print(f"❌ Ошибка в строке {line_num}: несколько '->' в одной строке")
                    return None, None, None, None
                
                left, right = line.split('->', 1)
                left = left.strip()
                
                if not left:
                    print(f"❌ Ошибка в строке {line_num}: отсутствует нетерминал слева от '->'")
                    return None, None, None, None
                
                if len(left.split()) > 1:
                    print(f"❌ Ошибка в строке {line_num}: несколько символов слева от '->' (не КС-грамматика)")
                    return None, None, None, None
                
                rights = [r.strip() for r in right.split('|')]
                if not start_symbol:
                    start_symbol = left
                
                non_terminals.add(left)
                grammar[left].extend(rights)
                
                for r in rights:
                    for sym in r.split():
                        if sym == "":
                            continue
                        if sym and (sym.islower() or not sym.isalpha() or sym in ('ε', 'epsilon')):
                            terminals.add(sym)
                        elif sym:
                            non_terminals.add(sym)
        
        if not start_symbol:
            print("❌ Ошибка: стартовый символ не определен")
            return None, None, None, None
            
        print("✅ Грамматика успешно загружена!")
        print(f"🎯 Стартовый символ: {start_symbol}")
        print(f"🔤 Нетерминалы: {sorted(non_terminals)}")
        print(f"🔡 Терминалы: {sorted(terminals)}")
        return grammar, start_symbol, terminals, non_terminals
    
    except FileNotFoundError:
        print(f"❌ Ошибка: файл '{file_path}' не найден.")
        return None, None, None, None
    except Exception as e:
        print(f"❌ Ошибка при чтении файла: {e}")
        return None, None, None, None

# =============================================
# Проверка корректности КС-грамматики
# =============================================
def is_valid_cfg(grammar, non_terminals, terminals):
    print("\n🔍 Проверка корректности грамматики...")
    
    for nt in non_terminals:
        if nt not in grammar:
            print(f"❌ Ошибка: нетерминал '{nt}' определен, но не имеет правил")
            return False
    
    for left in grammar:
        if not grammar[left]:
            print(f"❌ Ошибка: нетерминал '{left}' не имеет правил")
            return False
            
        for right in grammar[left]:
            if right == "" or right == "ε" or right == "epsilon":
                continue
                
            for sym in right.split():
                if sym not in non_terminals and sym not in terminals:
                    print(f"❌ Ошибка: символ '{sym}' в правиле '{left} -> {right}' не определён как терминал или нетерминал.")
                    return False
    
    print("✅ Грамматика корректна!")
    return True

# =============================================
# Устранение ε-продукций
# =============================================
def eliminate_epsilon(grammar, start_symbol, non_terminals):
    print("\n🌀 Устранение ε-продукций...")
    
    nullables = set()
    changed = True
    while changed:
        changed = False
        for left in grammar:
            for right in grammar[left]:
                if right == "" or right == "ε" or right == "epsilon":
                    if left not in nullables:
                        nullables.add(left)
                        changed = True
                else:
                    parts = right.split()
                    if all(p in nullables for p in parts):
                        if left not in nullables:
                            nullables.add(left)
                            changed = True
    
    print(f"✨ Nullable нетерминалы: {sorted(nullables)}")
    
    new_grammar = defaultdict(list)
    for left in grammar:
        for right in grammar[left]:
            if right == "" or right == "ε" or right == "epsilon":
                continue
                
            parts = right.split()
            combos = [[]]
            for p in parts:
                new_combos = []
                for c in combos:
                    new_combos.append(c + [p])
                    if p in nullables:
                        new_combos.append(c[:])
                combos = new_combos
            
            for combo in combos:
                if combo:
                    new_rule = ' '.join(combo)
                    if new_rule not in new_grammar[left]:
                        new_grammar[left].append(new_rule)
    
    if start_symbol in nullables:
        new_start = start_symbol + "'"
        new_grammar[new_start] = [start_symbol, '']
        start_symbol = new_start
        non_terminals.add(new_start)
        print(f"🆕 Добавлен новый стартовый символ: {start_symbol}")
    
    print("✅ ε-продукции устранены!")
    return new_grammar, start_symbol

# =============================================
# Устранение цепных продукций
# =============================================
def eliminate_unit_productions(grammar, start_symbol):
    print("\n⛓️  Устранение цепных продукций...")
    
    new_grammar = defaultdict(list)
    for left in grammar:
        reachable = set([left])
        queue = deque([left])
        
        while queue:
            current = queue.popleft()
            for right in grammar[current]:
                parts = right.split()
                if len(parts) == 1 and parts[0] in grammar and parts[0] not in reachable:
                    reachable.add(parts[0])
                    queue.append(parts[0])
        
        for reach in reachable:
            for right in grammar[reach]:
                parts = right.split()
                if not (len(parts) == 1 and parts[0] in grammar):
                    if right not in new_grammar[left]:
                        new_grammar[left].append(right)
    
    print("✅ Цепные продукции устранены!")
    return new_grammar, start_symbol

# =============================================
# Приведение к нормальной форме Хомского (CNF)
# =============================================
def to_chomsky_normal_form(grammar, start_symbol, non_terminals, terminals):
    print("\n🎯 Приведение к нормальной форме Хомского...")
    
    grammar, start_symbol = eliminate_epsilon(grammar, start_symbol, non_terminals.copy())
    grammar, start_symbol = eliminate_unit_productions(grammar, start_symbol)
    
    new_grammar = defaultdict(list)
    term_map = {}
    counter = 0
    
    for left in grammar:
        for right in grammar[left]:
            parts = right.split()
            if len(parts) == 1 and right in terminals:
                if right not in new_grammar[left]:
                    new_grammar[left].append(right)
            else:
                new_parts = []
                for p in parts:
                    if p in terminals:
                        if p not in term_map:
                            new_var = f"T{counter}"
                            counter += 1
                            term_map[p] = new_var
                            new_grammar[new_var].append(p)
                            non_terminals.add(new_var)
                        new_parts.append(term_map[p])
                    else:
                        new_parts.append(p)
                
                if len(new_parts) <= 2:
                    new_rule = ' '.join(new_parts)
                    if new_rule not in new_grammar[left]:
                        new_grammar[left].append(new_rule)
                else:
                    current = left
                    for i in range(len(new_parts) - 2):
                        new_var = f"B{counter}"
                        counter += 1
                        new_rule = f"{new_parts[i]} {new_var}"
                        if new_rule not in new_grammar[current]:
                            new_grammar[current].append(new_rule)
                        current = new_var
                        non_terminals.add(new_var)
                    
                    final_rule = f"{new_parts[-2]} {new_parts[-1]}"
                    if final_rule not in new_grammar[current]:
                        new_grammar[current].append(final_rule)
    
    print("✅ Нормальная форма Хомского получена!")
    return new_grammar, start_symbol

# =============================================
# Сохранение грамматики в файл
# =============================================
def save_grammar(filename, grammar, start_symbol):
    path = os.path.join(RESULTS_DIR, filename)
    with open(path, 'w', encoding='utf-8') as f:
        f.write(f"# Стартовый символ: {start_symbol}\n\n")
        for left in sorted(grammar):
            if '' in grammar[left]:
                rights = [r for r in grammar[left] if r != '']
                rights.append('ε')
                rights_str = ' | '.join(sorted(set(rights)))
            else:
                rights = sorted(set(grammar[left]))
                rights_str = ' | '.join(rights) if rights else 'ε'
            f.write(f"{left} -> {rights_str}\n")
    print(f"💾 Сохранено: {filename}")

# =============================================
# Построение дерева разбора
# =============================================
def build_parse_tree(grammar, start_symbol, terminals, max_depth=3):
    print("\n🌳 Построение дерева разбора...")
    
    if start_symbol not in grammar:
        print(f"❌ Ошибка: стартовый символ '{start_symbol}' отсутствует в грамматике")
        return
    
    graph = pydot.Dot(rankdir="TB", dpi=400)
    graph.set_node_defaults(shape="ellipse", style="filled", fontname="Arial", fontsize=16)

    node_counter = 0
    def create_node(label, parent=None, is_terminal=False):
        nonlocal node_counter
        nid = f"node{node_counter}"
        node_counter += 1
        color = "lightgreen" if is_terminal else "lightblue"
        graph.add_node(pydot.Node(nid, label=label, fillcolor=color))
        if parent is not None:
            graph.add_edge(pydot.Edge(parent, nid))
        return nid

    def build(sym, parent_nid, current_depth=0):
        if sym in terminals:
            create_node(sym, parent_nid, is_terminal=True)
            return
            
        if sym not in grammar:
            print(f"⚠️  Предупреждение: символ '{sym}' не имеет правил в грамматике")
            create_node(sym, parent_nid)
            return
        
        if current_depth >= max_depth:
            productions = grammar[sym]
            non_recursive_prods = [p for p in productions 
                                  if p and sym not in p.split()]
            if non_recursive_prods:
                prod = random.choice(non_recursive_prods)
            else:
                valid_prods = [p for p in productions if p]
                if valid_prods:
                    prod = random.choice(valid_prods)
                else:
                    prod = "ε"
        else:
            productions = grammar[sym]
            valid_prods = [p for p in productions if p]
            if not valid_prods:
                prod = "ε"
            else:
                recursive_prods = [p for p in valid_prods if sym in p.split()]
                non_recursive_prods = [p for p in valid_prods if p not in recursive_prods]
                
                if recursive_prods and random.random() < 0.7:
                    prod = random.choice(recursive_prods)
                elif non_recursive_prods:
                    prod = random.choice(non_recursive_prods)
                else:
                    prod = random.choice(valid_prods)
        
        if parent_nid is None:
            current_nid = create_node(sym)
        else:
            current_nid = create_node(sym, parent_nid)
        
        if prod == "" or prod == "ε" or prod == "epsilon":
            create_node("ε", current_nid, is_terminal=True)
            return
        
        for s in prod.split():
            if s in terminals:
                create_node(s, current_nid, is_terminal=True)
            else:
                build(s, current_nid, current_depth + 1)

    build(start_symbol, None)

    png_path = os.path.join(RESULTS_DIR, "parse_tree.png")
    pdf_path = os.path.join(RESULTS_DIR, "parse_tree.pdf")
    
    try:
        graph.write_png(png_path)
        graph.write_pdf(pdf_path)
        print("✅ Дерево разбора построено и сохранено!")
        print(f"   📸 {png_path}")
        print(f"   📄 {pdf_path}")
    except Exception as e:
        print(f"❌ Ошибка при сохранении дерева разбора: {e}")

# =============================================
# Основная функция
# =============================================
def main():
    print("🎉 === Обработка контекстно-свободной грамматики ===\n")
    
    file_name = input("📝 Введите имя файла с грамматикой (по умолчанию: input_grammar.txt): ").strip()
    if not file_name:
        file_name = "input_grammar.txt"
    
    grammar, start_symbol, terminals, non_terminals = parse_grammar(file_name)
    if grammar is None:
        print("\n🚫 Программа завершена из-за ошибок.")
        return
    
    if not is_valid_cfg(grammar, non_terminals, terminals):
        print("\n🚫 Грамматика содержит ошибки. Дальнейшая обработка невозможна.")
        return
    
    try:
        cnf_grammar, cnf_start = to_chomsky_normal_form(
            grammar.copy(), 
            start_symbol, 
            non_terminals.copy(), 
            terminals.copy()
        )
    except Exception as e:
        print(f"❌ Ошибка при приведении к нормальной форме Хомского: {e}")
        return
    
    save_grammar("original_grammar.txt", grammar, start_symbol)
    save_grammar("chomsky_normal_form.txt", cnf_grammar, cnf_start)
    
    try:
        build_parse_tree(grammar, start_symbol, terminals)
    except Exception as e:
        print(f"❌ Ошибка при построении дерева разбора: {e}")
    
    print("\n" + "="*60)
    print("🎊 Обработка завершена успешно!")
    print(f"📂 Все результаты сохранены в папке: {os.path.abspath(RESULTS_DIR)}")
    print("\n📋 Созданные файлы:")
    print("   • original_grammar.txt")
    print("   • chomsky_normal_form.txt  (нормальная форма Хомского)")
    print("   • parse_tree.png / parse_tree.pdf  (дерево разбора)")
    print("="*60)
    print("👋 До свидания!")

if __name__ == "__main__":
    main()