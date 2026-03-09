import matplotlib.pyplot as plt
import networkx as nx

# Создаём граф
G = nx.DiGraph()

# Узлы — этапы преобразования
stages = [
    "НКНА\n(с ε-переходами)",
    "NFA\n(без ε-переходов)",
    "ДКА\n(возможно неполный)",
    "Полный ДКА\n(+ фиктивное Δ)"
]
G.add_nodes_from(stages)

# Рёбра с красивыми подписями
G.add_edge(stages[0], stages[1], 
           label="Устранение ε-переходов\nТеорема 3.6")
G.add_edge(stages[1], stages[2], 
           label="Детерминизация\n(конструкция подмножеств)\nТеорема 3.2")
G.add_edge(stages[2], stages[3], 
           label="Введение фиктивного\nсостояния Δ\n(завершение)")

# Горизонтальная раскладка
pos = {
    stages[0]: (0, 0),
    stages[1]: (3, 0),
    stages[2]: (6, 0),
    stages[3]: (9, 0)
}

plt.figure(figsize=(14, 5))

# Красивые узлы
nx.draw_networkx_nodes(G, pos, 
                       node_shape="s",          # квадратные блоки
                       node_size=8000,
                       node_color="#E3F2FD",
                       edgecolors="#1565C0",
                       linewidths=3)

# Текст внутри узлов
nx.draw_networkx_labels(G, pos, 
                        font_size=11, 
                        font_weight="bold",
                        font_family="sans-serif")

# Стрелки
nx.draw_networkx_edges(G, pos, 
                       arrows=True, 
                       arrowsize=30, 
                       arrowstyle="->", 
                       connectionstyle="arc3,rad=0.2",
                       width=3,
                       edge_color="#1565C0")

# Подписи к стрелкам
edge_labels = nx.get_edge_attributes(G, 'label')
nx.draw_networkx_edge_labels(G, pos, edge_labels, 
                             font_size=10, 
                             font_color="#d32f2f",
                             bbox=dict(boxstyle="round,pad=0.4", 
                                       facecolor="white", 
                                       edgecolor="none"))

plt.title("Цепочка эквивалентных преобразований по Рейуорду-Смиту (1988)\n"
          "от НКНА к полному детерминированному конечному автомату",
          fontsize=14, fontweight="bold", pad=30)

plt.axis("off")
plt.tight_layout()

# Сохраняем в высоком качестве
plt.savefig("chain_horizontal_beautiful.png", dpi=300, bbox_inches="tight")
plt.show()