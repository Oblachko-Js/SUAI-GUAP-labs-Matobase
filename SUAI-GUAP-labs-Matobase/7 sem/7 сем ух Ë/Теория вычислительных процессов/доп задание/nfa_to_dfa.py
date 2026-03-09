#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""ε-NFA → полный ДКА по Рейуорду-Смиту (1988, гл. 3)"""

import json
from collections import defaultdict, deque
import os
import argparse

try:
    import pydot
except ImportError:
    print("Установите pydot и graphviz: pip install pydot graphviz")
    exit(1)


def validate_json_structure(data):
    """Проверка структуры JSON файла"""
    required_fields = ["states", "alphabet", "start", "accept", "transitions"]
    for field in required_fields:
        if field not in data:
            raise ValueError(f"Отсутствует обязательное поле: {field}")
    
    if not isinstance(data["states"], list) or not data["states"]:
        raise ValueError("Поле 'states' должно быть непустым списком")
    
    if not isinstance(data["alphabet"], list):
        raise ValueError("Поле 'alphabet' должно быть списком")
    
    if not isinstance(data["transitions"], dict):
        raise ValueError("Поле 'transitions' должно быть словарем")


def validate_states(states):
    """Проверка, что состояния имеют формат q0, q1, q2, ..."""
    valid_states = set()
    for state in states:
        state_str = str(state)
        if not state_str.startswith('q') or not state_str[1:].isdigit():
            raise ValueError(f"Недопустимое состояние: {state}. Состояния должны быть в формате q0, q1, q2, ...")
        valid_states.add(state_str)
    return valid_states


def is_already_deterministic(automaton):
    """Проверка, является ли автомат уже детерминированным"""
    trans = automaton["trans"]
    
    for state in automaton["states"]:
        state_trans = trans.get(state, {})
        
        # Проверка на ε-переходы (признак недетерминизма)
        if "ε" in state_trans:
            return False
            
        # Проверка на множественные переходы по одному символу
        for symbol, targets in state_trans.items():
            if len(targets) > 1:
                return False
                
    return True


def load_automaton(path: str):
    """Загрузка и валидация ε-NFA из JSON"""
    try:
        with open(path, encoding="utf-8") as f:
            data = json.load(f)
    except json.JSONDecodeError as e:
        raise ValueError(f"Ошибка формата JSON: {e}")

    # Проверка структуры JSON
    validate_json_structure(data)

    # Проверка состояний
    states = validate_states(data["states"])
    
    # Проверка начального состояния
    start = str(data["start"])
    if start not in states:
        raise ValueError(f"Начальное состояние {start} не найдено в списке состояний")
    
    # Проверка конечных состояний
    accept = set(map(str, data["accept"]))
    invalid_accept = accept - states
    if invalid_accept:
        raise ValueError(f"Конечные состояния {invalid_accept} не найдены в списке состояний")

    # Проверка алфавита
    alphabet = data["alphabet"]
    if not all(isinstance(sym, str) for sym in alphabet):
        raise ValueError("Все символы алфавита должны быть строками")

    trans = defaultdict(lambda: defaultdict(list))

    # Проверка переходов
    for s, rules in data.get("transitions", {}).items():
        s = str(s)
        if s not in states:
            raise ValueError(f"Состояние {s} в переходах не найдено в списке состояний")
        
        for sym, targets in rules.items():
            if not isinstance(targets, list):
                raise ValueError(f"Цели перехода для {s}[{sym}] должны быть списком")
                
            for target in targets:
                target_str = str(target)
                if target_str not in states and target_str != "∅":
                    raise ValueError(f"Целевое состояние {target_str} не найдено в списке состояний")
                trans[s][sym].append(target_str)

    automaton = {"states": states, "alphabet": alphabet, "start": start, "accept": accept, "trans": trans}
    
    # Проверка на уже детерминированный автомат
    if is_already_deterministic(automaton):
        print("⚠️  Внимание: Автомат уже детерминированный. Преобразование может быть избыточным.")
    
    return automaton


def compute_epsilon_closure(automaton):
    """Вычисление ε-замыканий R(p) - все состояния, достижимые по ε-переходам"""
    trans = automaton["trans"]
    states = automaton["states"]
    closure = {}

    for state in states:
        visited = {state}
        queue = deque([state])
        while queue:
            cur = queue.popleft()
            # Добавляем все состояния, достижимые по ε-переходам
            for nxt in trans[cur].get("ε", []):
                if nxt not in visited:
                    visited.add(nxt)
                    queue.append(nxt)
        closure[state] = frozenset(visited)
    return closure


def eliminate_epsilon(automaton, epsilon_closure):
    """Этап 1: Устранение ε-переходов (Теорема 3.6)"""
    alphabet = automaton["alphabet"]
    old_trans = automaton["trans"]
    accept = automaton["accept"]
    new_trans = defaultdict(dict)
    new_accept = set()

    # Обновляем множество конечных состояний
    for s, cl in epsilon_closure.items():
        if cl & accept:  # Если в ε-замыкании есть конечное состояние
            new_accept.add(s)

    # Строим новые переходы без ε
    for state in automaton["states"]:
        cl = epsilon_closure[state]
        for sym in alphabet:
            targets = set()
            # Объединяем переходы по символу из всех состояний ε-замыкания
            for q in cl:
                targets.update(old_trans[q].get(sym, []))
            if targets:
                new_trans[state][sym] = list(targets)

    return {
        "states": automaton["states"],
        "alphabet": alphabet,
        "start": automaton["start"],
        "accept": new_accept,
        "trans": dict(new_trans)
    }


def subset_construction(nfa):
    """Этап 2: Детерминизация - алгоритм построения подмножеств"""
    trans = nfa["trans"]
    start_set = frozenset([nfa["start"]])
    alphabet = nfa["alphabet"]
    accept = nfa["accept"]

    state_map = {}  # Соответствие множеств состояний -> новые имена
    queue = deque([start_set])
    discovered = {start_set}
    new_trans = {}
    new_accept = set()
    counter = 0

    while queue:
        current = queue.popleft()
        # Создаем новое имя состояния для ДКА
        name = f"q{counter}"
        state_map[current] = name
        counter += 1

        # Если в текущем множестве есть конечное состояние НКА
        if current & accept:
            new_accept.add(name)

        new_trans[name] = {}
        for sym in alphabet:
            next_set = set()
            # Объединяем переходы по символу из всех состояний текущего множества
            for s in current:
                next_set.update(trans.get(s, {}).get(sym, []))
            next_froz = frozenset(next_set)
            new_trans[name][sym] = next_froz

            # Добавляем новое множество состояний в обработку
            if next_froz and next_froz not in discovered:
                discovered.add(next_froz)
                queue.append(next_froz)

    # Преобразуем множества состояний в имена
    final_trans = {}
    for name, rules in new_trans.items():
        final_trans[name] = {sym: state_map.get(target, "∅") for sym, target in rules.items()}

    return {
        "states": list(state_map.values()),
        "alphabet": alphabet,
        "start": state_map[start_set],
        "accept": new_accept,
        "trans": final_trans,
        "raw_sets": state_map
    }


def complete_dfa(dfa):
    """Этап 3: Добавление поглощающего состояния Δ для полного ДКА"""
    alphabet = dfa["alphabet"]
    states = dfa["states"][:]
    trans = {s: dict(dfa["trans"].get(s, {})) for s in dfa["states"]}
    start = dfa["start"]
    accept = dfa["accept"]

    # Создаем поглощающее состояние для отсутствующих переходов
    sink = "Δ"
    if sink not in states:
        states.append(sink)

    # Добавляем переходы в Δ где их нет
    for s in states:
        for sym in alphabet:
            if sym not in trans.get(s, {}) or trans[s][sym] == "∅":
                trans.setdefault(s, {})[sym] = sink

    # Поглощающее состояние ведет само в себя по всем символам
    trans[sink] = {sym: sink for sym in alphabet}

    return {"states": states, "alphabet": alphabet, "start": start, "accept": accept, "trans": trans}


def to_dot(automaton, title="Автомат", is_dfa=False):
    """Генерация графа в формате Graphviz DOT"""
    dot = pydot.Dot(title, rankdir="LR")
    dot.set_node_defaults(shape="circle", style="filled", fillcolor="white", fontsize="12")

    # Добавляем состояния
    for s in automaton["states"]:
        shape = "doublecircle" if s in automaton["accept"] else "circle"
        fillcolor = "lightgrey" if s in automaton["accept"] else "white"
        dot.add_node(pydot.Node(s, shape=shape, fillcolor=fillcolor))

    # Помечаем начальное состояние
    dot.add_node(pydot.Node(automaton["start"], peripheries=2))

    # Добавляем переходы
    for src in automaton["trans"]:
        for sym, targets in automaton["trans"][src].items():
            if isinstance(targets, str):
                targets = [targets]
            for t in targets:
                if t == "∅":
                    continue
                label = "ε" if sym == "ε" else sym
                color = "red" if is_dfa and t == "Δ" else "black"
                dot.add_edge(pydot.Edge(src, t, label=label, color=color))

    return dot


def main():
    parser = argparse.ArgumentParser(description="ε-NFA → полный ДКА (Рейуорд-Смит 1988)")
    parser.add_argument("json_file", help="JSON файл с описанием автомата")
    args = parser.parse_args()

    print(f"📁 Загрузка: {args.json_file}")
    try:
        auto = load_automaton(args.json_file)
    except (ValueError, KeyError) as e:
        print(f"❌ ОШИБКА ВАЛИДАЦИИ: {e}")
        print("💡 Состояния должны быть в формате q0, q1, q2, ...")
        exit(1)
    except FileNotFoundError:
        print(f"❌ Файл {args.json_file} не найден")
        exit(1)

    print("✅ Автомат загружен и проверен")
    print(f"   Состояния: {len(auto['states'])}, Символы: {auto['alphabet']}")

    print("\n1. 🔄 Устранение ε-переходов...")
    eps_cl = compute_epsilon_closure(auto)
    nfa = eliminate_epsilon(auto, eps_cl)

    print("2. 🎯 Детерминизация...")
    dfa = subset_construction(nfa)

    print("3. ✅ Завершение (добавление Δ)...")
    full_dfa = complete_dfa(dfa)

    # Создаем директорию для результатов
    os.makedirs("results", exist_ok=True)
    base = os.path.splitext(os.path.basename(args.json_file))[0]

    # Сохраняем графики
    to_dot(auto, "Исходный ε-NFA").write_png(f"results/{base}_nfa.png")
    to_dot(full_dfa, "Полный ДКА", is_dfa=True).write_png(f"results/{base}_full_dfa.png")

    # Сохраняем таблицу переходов
    with open(f"results/{base}_table.txt", "w", encoding="utf-8") as f:
        f.write("ПОЛНЫЙ ДКА\n")
        f.write(f"Состояний: {len(full_dfa['states'])}\n")
        f.write(f"Начальное: {full_dfa['start']}\n")
        f.write(f"Конечные: {', '.join(sorted(full_dfa['accept']))}\n\n")
        f.write("    │ " + "  ".join(full_dfa["alphabet"]) + "\n")
        f.write("────┼" + "───" * len(full_dfa["alphabet"]) + "\n")
        for s in sorted(full_dfa["states"], key=lambda x: (x != full_dfa["start"], x != "Δ", x)):
            f.write(f"{s:<3} │ " + "  ".join(full_dfa["trans"][s].get(a, "—") for a in full_dfa["alphabet"]) + "\n")

    print("\n🎉 ГОТОВО! Результаты в ./results/")
    print(f"📊 Состояний в ДКА: {len(full_dfa['states'])}")
    print(f"📁 Файлы:")
    print(f"   - {base}_nfa.png (график НКА)")
    print(f"   - {base}_full_dfa.png (график ДКА)")
    print(f"   - {base}_table.txt (таблица переходов)")


if __name__ == "__main__":
    main()