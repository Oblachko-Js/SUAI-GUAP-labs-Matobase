import random
import numpy as np
import matplotlib.pyplot as plt
import networkx as nx

class Node:
    def __init__(self, value, children=None):
        self.value = value
        self.children = children or []

def copy_tree(node):
    return Node(node.value, [copy_tree(c) for c in node.children])

def get_depth(node):
    if not node.children:
        return 1
    return 1 + max(get_depth(c) for c in node.children)

def create_full(arity, depth, functions, terminals):
    if depth == 1:
        return Node(random.choice(terminals))
    func = random.choice(functions)
    children = [create_full(arity, depth-1, functions, terminals) for _ in range(arity)]
    return Node(func, children)

def create_grow(arity, depth, functions, terminals):
    if depth == 1:
        return Node(random.choice(terminals))
    if random.random() < 0.5:
        return Node(random.choice(terminals))
    func = random.choice(functions)
    children = [create_grow(arity, depth-1, functions, terminals) for _ in range(arity)]
    return Node(func, children)

def get_random_subtree_root(node):
    nodes = []
    def collect(n, parent, idx):
        nodes.append((n, parent, idx))
        for i, child in enumerate(n.children):
            collect(child, n, i)
    collect(node, None, -1)
    return random.choice(nodes)

def crossover(p1, p2):
    c1 = copy_tree(p1)
    c2 = copy_tree(p2)
    sub1, par1, idx1 = get_random_subtree_root(c1)
    sub2, par2, idx2 = get_random_subtree_root(c2)
    if par1:
        par1.children[idx1] = sub2
    else:
        c1 = sub2
    if par2:
        par2.children[idx2] = sub1
    else:
        c2 = sub1
    return c1, c2

def mutation(ind, functions, terminals):
    c = copy_tree(ind)
    sub, par, idx = get_random_subtree_root(c)
    depth = random.randint(2,4)
    if random.random() < 0.5:
        new_sub = create_full(2, depth, functions, terminals)
    else:
        new_sub = create_grow(2, depth, functions, terminals)
    if par:
        par.children[idx] = new_sub
    else:
        c = new_sub
    return c

def evaluate(node, x):
    if node.value == 'x':
        return x
    if isinstance(node.value, int):
        return float(node.value)
    left = evaluate(node.children[0], x)
    right = evaluate(node.children[1], x)
    if node.value == '+':
        return left + right
    if node.value == '-':
        return left - right
    if node.value == '*':
        return left * right
    if node.value == '/':
        if abs(right) < 1e-8:
            return 1.0
        return left / right

def fitness(ind, x_values, y_values):
    errors = 0.0
    for x, y in zip(x_values, y_values):
        try:
            pred = evaluate(ind, x)
            errors += (pred - y)**2
        except Exception as e:
            return float('inf')
    return errors / len(x_values)

def to_str(node):
    if node.value == 'x' or isinstance(node.value, int):
        return str(node.value)
    left = to_str(node.children[0])
    right = to_str(node.children[1])
    if node.value in ['+', '-']:
        left = '(' + left + ')' if node.value == '-' and node.children[0].children else left
        right = '(' + right + ')' if node.value == '-' and node.children[1].children else right
    else:
        left = '(' + left + ')'
        right = '(' + right + ')'
    return left + node.value + right

def draw_tree(node, gen):
    G = nx.DiGraph()
    pos = {}
    def add_nodes_edges(n, parent=None, level=0, pos_x=0):
        node_id = id(n)
        G.add_node(node_id, label=str(n.value))
        if parent is not None:
            G.add_edge(id(parent), node_id)
        pos[node_id] = (pos_x, -level)
        if n.children:
            child_count = len(n.children)
            child_spacing = 2 ** (5 - level)  # Adjust spacing based on level
            start_x = pos_x - (child_count - 1) * child_spacing / 2
            for i, child in enumerate(n.children):
                child_x = start_x + i * child_spacing
                add_nodes_edges(child, n, level + 1, child_x)
    add_nodes_edges(node)
    plt.figure(figsize=(12, 8))
    nx.draw(G, pos, with_labels=True, labels=nx.get_node_attributes(G, 'label'), 
            node_color='lightblue', node_size=500, font_size=10, arrows=True)
    plt.title(f"Tree at Generation {gen}")
    plt.show()

def tournament(pop, fits, k=4):
    indices = random.sample(range(len(pop)), k)
    best_idx = min(indices, key=lambda i: fits[i])
    return pop[best_idx]

# Main script
random.seed(42)
np.random.seed(42)
functions = ['+', '-', '*', '/']
terminals = ['x'] + list(range(-5, 6))
pop_size = 600
max_gen = 100
crossover_prob = 0.9
mutation_prob = 0.05
max_depth = 200
pop = []
for d in range(2,7):
    for _ in range(60):
        pop.append(create_full(2, d, functions, terminals))
        pop.append(create_grow(2, d, functions, terminals))
x_values = np.random.uniform(-1, 1, 20)
y_values = x_values**4 - x_values**3 + x_values**2 - x_values
print("x_values:", x_values)
print("y_values:", y_values)
for gen in range(max_gen):
    fits = [fitness(ind, x_values, y_values) for ind in pop]
    min_fit = min(fits)
    best_idx = fits.index(min_fit)
    best = pop[best_idx]
    if gen % 10 == 0 or gen == max_gen - 1:
        print(f"Generation {gen}: Best fitness {min_fit}")
        print("Formula: " + to_str(best))
        draw_tree(best, gen)
    new_pop = []
    while len(new_pop) < pop_size:
        parent1 = copy_tree(tournament(pop, fits))
        parent2 = copy_tree(tournament(pop, fits))
        if random.random() < crossover_prob:
            off1, off2 = crossover(parent1, parent2)
        else:
            off1 = parent1
            off2 = parent2
        if random.random() < mutation_prob:
            off1 = mutation(off1, functions, terminals)
        if random.random() < mutation_prob:
            off2 = mutation(off2, functions, terminals)
        if get_depth(off1) > max_depth:
            off1 = parent1
        if get_depth(off2) > max_depth:
            off2 = parent2
        new_pop.append(off1)
        new_pop.append(off2)
    pop = new_pop[:pop_size]
fits = [fitness(ind, x_values, y_values) for ind in pop]
min_fit = min(fits)
best_idx = fits.index(min_fit)
best = pop[best_idx]
print("Final Best fitness", min_fit)
print("Final Formula: " + to_str(best))
draw_tree(best, max_gen)
print("Original function: x^4 - x^3 + x^2 - x")
x_grid = np.linspace(-1,1,100)
y_original = x_grid**4 - x_grid**3 + x_grid**2 - x_grid
y_found = []
for x in x_grid:
    try:
        y_found.append(evaluate(best, x))
    except:
        y_found.append(0)
plt.plot(x_grid, y_original, label='Original', color='blue')
plt.plot(x_grid, y_found, label='Found', color='red')
plt.legend()
plt.title('Comparison of Original and Found Functions')
plt.show()
print("\nTable of parameters:")
print("Цель: Эволюции функции, аппроксимирующей данные")
print("Терминальное множество: Переменная x, Целые от -5 до +5")
print("Функциональное множество: ADD, SUB, MUL, DIV")
print("Мощность популяции: 600")
print("Вероятн. кроссинговера: 0.90")
print("Вероятность мутации: 0.05")
print("Отбор родителей: Турнирный, с мощностью тура 4")
print("Максимальное число поколений: 100")
print("Максимальная глубина после кроссинговера: 200")
print("Максимальная глубина мутации: 4")
print("Метод инициализации: Ramped half-and-half")
