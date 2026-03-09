import sys
from tabulate import tabulate

counter = 0

class NFA:
    def __init__(self):
        self.start = None
        self.accept = None
        self.transitions = {}  
        self.epsilon = {}  

def create_basic(sym):
    global counter
    s = counter
    counter += 1
    f = counter
    counter += 1
    nfa = NFA()
    nfa.start = s
    nfa.accept = f
    if (s, sym) not in nfa.transitions:
        nfa.transitions[(s, sym)] = set()
    nfa.transitions[(s, sym)].add(f)
    return nfa

def or_nfa(n1, n2):
    global counter
    s = counter
    counter += 1
    f = counter
    counter += 1
    nfa = NFA()
    nfa.start = s
    nfa.accept = f
    if s not in nfa.epsilon:
        nfa.epsilon[s] = set()
    nfa.epsilon[s].update({n1.start, n2.start})
    if n1.accept not in nfa.epsilon:
        nfa.epsilon[n1.accept] = set()
    nfa.epsilon[n1.accept].add(f)
    if n2.accept not in nfa.epsilon:
        nfa.epsilon[n2.accept] = set()
    nfa.epsilon[n2.accept].add(f)
    nfa.transitions = {**n1.transitions, **n2.transitions}
    nfa.epsilon = {**n1.epsilon, **n2.epsilon, **nfa.epsilon}
    return nfa

def concat_nfa(n1, n2):
    global counter
    nfa = NFA()
    nfa.start = n1.start
    nfa.accept = n2.accept
    nfa.transitions = {**n1.transitions, **n2.transitions}
    nfa.epsilon = {**n1.epsilon, **n2.epsilon}
    if n1.accept not in nfa.epsilon:
        nfa.epsilon[n1.accept] = set()
    nfa.epsilon[n1.accept].add(n2.start)
    return nfa

def optional_nfa(n):
    global counter
    s = counter
    counter += 1
    f = counter
    counter += 1
    nfa = NFA()
    nfa.start = s
    nfa.accept = f
    if s not in nfa.epsilon:
        nfa.epsilon[s] = set()
    nfa.epsilon[s].update({n.start, f})
    if n.accept not in nfa.epsilon:
        nfa.epsilon[n.accept] = set()
    nfa.epsilon[n.accept].add(f)
    nfa.transitions = n.transitions.copy()
    nfa.epsilon = {**n.epsilon, **nfa.epsilon}
    return nfa

# Звезда Клини (0 или более повторений)
def star_nfa(n):
    global counter
    s = counter
    counter += 1
    f = counter
    counter += 1
    nfa = NFA()
    nfa.start = s
    nfa.accept = f
    
    # из нового старта: либо пропустить всё, либо зайти в n
    nfa.epsilon[s] = {n.start, f}
    
    # из конца n: либо закончить, либо повторить
    if n.accept not in nfa.epsilon:
        nfa.epsilon[n.accept] = set()
    nfa.epsilon[n.accept].update({n.start, f})
    
    # копируем все переходы и ε-переходы из под-NFA
    nfa.transitions = n.transitions.copy()
    nfa.epsilon = {**n.epsilon, **nfa.epsilon}
    
    return nfa

class Parser:
    def __init__(self, s):
        self.s = s
        self.pos = 0

    def parse(self):
        nfa = self.parse_expr()
        if self.pos != len(self.s):
            print("Warning: Not all input parsed", file=sys.stderr)
        return nfa

    def parse_expr(self):
        nfa = self.parse_term()
        while self.pos < len(self.s) and self.s[self.pos] == '|':
            self.pos += 1
            n2 = self.parse_term()
            nfa = or_nfa(nfa, n2)
        return nfa

    def parse_term(self):
        nfa = self.parse_factor()
        while self.pos < len(self.s) and self.s[self.pos] not in '|)>':
            n2 = self.parse_factor()
            nfa = concat_nfa(nfa, n2)
        return nfa

    def parse_factor(self):
        if self.pos >= len(self.s):
            print("Error: Unexpected end of input", file=sys.stderr)
            return create_basic('')
        ch = self.s[self.pos]
        if ch == '(':
            self.pos += 1
            nfa = self.parse_expr()
            if self.pos < len(self.s) and self.s[self.pos] == ')':
                self.pos += 1
            else:
                print("Error: Missing )", file=sys.stderr)
            return nfa
        elif ch == '<':
            self.pos += 1
            nfa = self.parse_expr()
            if self.pos < len(self.s) and self.s[self.pos] == '>':
                self.pos += 1
            else:
                print("Error: Missing >", file=sys.stderr)
            return star_nfa(nfa)        
        else:
            self.pos += 1
            return create_basic(ch)

def epsilon_closure(states, epsilon):
    closure = set(states)
    stack = list(states)
    while stack:
        state = stack.pop()
        for next_state in epsilon.get(state, set()):
            if next_state not in closure:
                closure.add(next_state)
                stack.append(next_state)
    return closure

def move(states, symbol, transitions):
    next_states = set()
    for state in states:
        next_states.update(transitions.get((state, symbol), set()))
    return next_states

def accepts(nfa, word):
    current_states = epsilon_closure({nfa.start}, nfa.epsilon)
    for symbol in word:
        current_states = epsilon_closure(move(current_states, symbol, nfa.transitions), nfa.epsilon)
        if not current_states:
            return False
    return nfa.accept in current_states

# Чтение регулярного выражения
try:
    with open('input.txt', 'r', encoding='utf-8') as file:
        regex = file.read().strip()
except FileNotFoundError:
    print("Error: input.txt not found", file=sys.stderr)
    sys.exit(1)

# Чтение входного слова
try:
    with open('input_text.txt', 'r', encoding='utf-8') as file:
        input_word = file.read().strip()
except FileNotFoundError:
    input_word = None
    print("Error: input_text.txt not found", file=sys.stderr)

counter = 0
parser = Parser(regex)
nfa = parser.parse()

# Формирование таблицы переходов
symbols = sorted(set(sym for _, sym in nfa.transitions.keys() if sym != ''))
table = []
headers = ["State"] + symbols + ["ε"]
for state in range(counter):
    row = [str(state)]
    for sym in symbols:
        nexts = nfa.transitions.get((state, sym), set())
        row.append(", ".join(map(str, sorted(nexts))) or "-")
    eps = nfa.epsilon.get(state, set())
    row.append(", ".join(map(str, sorted(eps))) or "-")
    table.append(row)

# Запись в файл output.txt
with open('output.txt', 'w', encoding='utf-8') as file:
    file.write(f"Start state: {nfa.start}\n")
    file.write(f"Accept state: {nfa.accept}\n")
    file.write(f"Number of states: {counter}\n")
    file.write(f"Alphabet (without ε): {' '.join(symbols) if symbols else '-'}\n")
    file.write("\nTransition Table:\n")
    file.write(tabulate(table, headers=headers, tablefmt="grid"))
    if input_word is not None:
        file.write(f"\n\nInput string: {input_word}\n")
        result = accepts(nfa, input_word)
        file.write(f"Result: String '{input_word}' is {'accepted' if result else 'rejected'}\n")
    else:
        file.write("\n\nInput string: None (input_text.txt not found)\n")