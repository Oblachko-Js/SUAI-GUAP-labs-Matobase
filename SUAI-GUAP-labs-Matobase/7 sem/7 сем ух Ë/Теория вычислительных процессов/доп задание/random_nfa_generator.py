#!/usr/bin/env python3
# -*- coding: utf-8 -*-

"""
Генератор случайных ε-НКНА совместимых с nfa_to_dfa.py
Создаёт тесты от 10 до 100 состояний.
"""

import json
import random
import argparse
import os


def generate_random_nfa(n_states=6, alphabet=None,
                         max_targets_symbol=3,
                         max_targets_epsilon=2):
    """
    Создаёт случайный ε-НКНА в формате JSON:
    - n_states: количество состояний
    - alphabet: список символов (например ['a','b'])
    - max_targets_symbol: максимальное число переходов по одному символу
    - max_targets_epsilon: максимальное число ε-переходов из одного состояния
    """

    if alphabet is None:
        alphabet = ["a", "b"]

    states = [f"q{i}" for i in range(n_states)]
    start = "q0"
    accept = [random.choice(states)]

    transitions = {}

    for s in states:
        transitions[s] = {}

        # ε-переходы
        eps_count = random.randint(0, max_targets_epsilon)
        if eps_count > 0:
            transitions[s]["ε"] = random.sample(states, eps_count)

        # переходы по символам алфавита
        for sym in alphabet:
            t_count = random.randint(0, max_targets_symbol)
            if t_count > 0:
                transitions[s][sym] = random.sample(states, t_count)

    return {
        "states": states,
        "alphabet": alphabet,
        "start": start,
        "accept": accept,
        "transitions": transitions
    }


def save_json(data, path):
    """Сохранить автомат в JSON"""
    with open(path, "w", encoding="utf-8") as f:
        json.dump(data, f, indent=2, ensure_ascii=False)


def main():
    parser = argparse.ArgumentParser(description="Генератор случайных ε-НКНА")
    parser.add_argument("-n", "--num-tests", type=int, default=5,
                        help="Сколько тестовых автоматов создать")
    parser.add_argument("-s", "--states", type=int, nargs=2, default=[10, 100],
                        help="Диапазон числа состояний (min max)")
    parser.add_argument("-a", "--alphabet", type=str, default="ab",
                        help="Алфавит, например 'ab' или 'abc'")
    parser.add_argument("--out", type=str, default="random_tests",
                        help="Папка для сохранения файлов")

    args = parser.parse_args()

    os.makedirs(args.out, exist_ok=True)
    alphabet = list(args.alphabet)

    for i in range(args.num_tests):
        n = random.randint(args.states[0], args.states[1])

        nfa = generate_random_nfa(
            n_states=n,
            alphabet=alphabet,
            max_targets_symbol=3,
            max_targets_epsilon=2
        )

        filename = f"{args.out}/random_{n}_states_{i+1}.json"
        save_json(nfa, filename)

        print(f"✓ Создан файл: {filename}")

    print("\nГотово! Все файлы находятся в:", args.out)


if __name__ == "__main__":
    main()
