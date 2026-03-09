//lab7 var 9
#include <iostream>
#include <vector>
#include <list>

using namespace std;

class Graph {
private:
    int V;  // Количество вершин в графе
    list<int>* adj;  // Список смежности

public:
    Graph(int V) {
        this->V = V;
        adj = new list<int>[V];
    }

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void printEdges() {
        for (int i = 0; i < V; ++i) {
            for (auto v : adj[i]) {
                if (i < v) {
                    cout << i << " - " << v << endl;
                }
            }
        }
    }

    bool isEulerianCycle() {
        for (int i = 0; i < V; i++) {
            if (adj[i].size() % 2 != 0) {
                return false;
            }
        }
        return true;
    }

    void DFS(int v, vector<bool>& visited) {
        visited[v] = true;
        cout << v << " ";

        for (auto it = adj[v].begin(); it != adj[v].end(); ++it) {
            if (!visited[*it]) {
                DFS(*it, visited);
            }
        }
    }

    void findEulerianCycle() {
        if (!isEulerianCycle()) {
            cout << "Эйлеров цикл не существует." << endl;
            return;
        }
        cout << "Эйлеров цикл:" << endl;
        vector<bool> visited(V, false);

        for (int i = 0; i < V; i++) {
            if (!adj[i].empty()) {
                DFS(i, visited);
                break; // Найден Эйлеров цикл, завершаем цикл
            }
        }
        cout << endl;
    }
};

int main() {
    system("chcp 1251 > nul");
    int V, E;
    cout << "Введите количество вершин и рёбер: ";
    if (!(cin >> V >> E) || V < 1 || E < 0) {
        cout << "Неправильный ввод. Пожалуйста, введите положительное количество вершин и неотрицательное количество рёбер." << endl;
        return 1;
    }

    Graph graph(V);

    cout << "Введите рёбра (u v):" << endl;
    for (int i = 0; i < E; i++) {
        int u, v;
        cout << "Ребро " << i + 1 << ": ";
        if (!(cin >> u >> v) || u < 0 || u >= V || v < 0 || v >= V) {
            cout << "Неправильный ввод. Пожалуйста, введите верные номера вершин. Проверка на цикл не удалась." << endl;
            return 1;
        }
        graph.addEdge(u, v);
    }

    cout << "Список рёбер:" << endl;
    graph.printEdges();

    graph.findEulerianCycle();

    return 0;
}
