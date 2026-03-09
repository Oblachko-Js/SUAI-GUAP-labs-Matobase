//лаба 7, вариант 7
#include <iostream>
#include <vector>

using namespace std;

class Graph {
private:
    int V;  // Количество вершин в графе
    vector<vector<bool>> adjacencyMatrix;  // Матрица смежности

public:
    Graph(int V) {
        this->V = V;
        adjacencyMatrix = vector<vector<bool>>(V, vector<bool>(V, false));
    }

    void addEdge(int u, int v) {
        adjacencyMatrix[u][v] = true;
        adjacencyMatrix[v][u] = true;
    }

    bool isConnected() {
        vector<int> degrees(V, 0);

        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                if (adjacencyMatrix[i][j]) {
                    degrees[i]++;
                }
            }
        }

        for (int i = 0; i < V; i++) {
            if (degrees[i] % 2 != 0) {
                cout << "Граф не связен или имеет вершину с нечетной степенью." << endl;
                return false;
            }
        }

        return true;
    }

    void DFS(int v, vector<bool>& visited) {
        visited[v] = true;
        cout << v << " ";

        for (int i = 0; i < V; i++) {
            if (adjacencyMatrix[v][i] && !visited[i]) {
                DFS(i, visited);
            }
        }
    }

    void findEulerianPath() {
        if (!isConnected()) {
            return;
        }

        vector<bool> visited(V, false);

        for (int i = 0; i < V; i++) {
            if (!visited[i] && count(adjacencyMatrix[i].begin(), adjacencyMatrix[i].end(), true) > 0) {
                cout << "Эйлеров цикл:" << endl;
                DFS(i, visited);
                cout << endl;
                return;
            }
        }
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
            cout << "Неправильный ввод. Пожалуйста, введите верные номера вершин." << endl;
            return 1;
        }
        graph.addEdge(u, v);
    }

    graph.findEulerianPath();

    return 0;
}
