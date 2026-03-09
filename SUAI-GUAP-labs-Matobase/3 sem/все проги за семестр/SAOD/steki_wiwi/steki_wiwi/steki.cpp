#include <iostream>
#include <chrono>
#include <string>
#include <queue>
#include <stack>
#include <mutex>
#include <random>
#include <thread>

using namespace std;

const int MaxTasks = 3; // Максимальное количество задач в каждой очереди и стеке

struct Task {
    int priority;
    string name;
    chrono::time_point<chrono::steady_clock> arrivalTime;

    Task(int p, const string& n, chrono::time_point<chrono::steady_clock> time)
        : priority(p), name(n), arrivalTime(time) {}
};

mutex mtx;

void displayState(
    const queue<Task>& f0,
    queue<Task>& f1,
    queue<Task>& f2,
    stack<Task>& S,
    Task& currentTask,
    chrono::time_point<chrono::steady_clock> startTime
) {
    chrono::time_point<chrono::steady_clock> currentTime = chrono::steady_clock::now();
    chrono::duration<double> elapsedTime = currentTime - startTime;

    cout << "Очередь f0 (высший приоритет): ";
    queue<Task> tempQueue = f0;
    while (!tempQueue.empty()) {
        Task task = tempQueue.front();
        chrono::duration<double> taskArrivalTime = task.arrivalTime - startTime;
        cout << task.name << "(" << taskArrivalTime.count() << "s) ";
        tempQueue.pop();
    }
    cout << "\n";

    cout << "Очередь f1 (средний приоритет): ";
    tempQueue = f1;
    while (!tempQueue.empty()) {
        Task task = tempQueue.front();
        chrono::duration<double> taskArrivalTime = task.arrivalTime - startTime;
        cout << task.name << "(" << taskArrivalTime.count() << "s) ";
        tempQueue.pop();
    }
    cout << "\n";

    cout << "Очередь f2 (самый низкий приоритет): ";
    tempQueue = f2;
    while (!tempQueue.empty()) {
        Task task = tempQueue.front();
        chrono::duration<double> taskArrivalTime = task.arrivalTime - startTime;
        cout << task.name << "(" << taskArrivalTime.count() << "s) ";
        tempQueue.pop();
    }
    cout << "\n";

    cout << "Стек S: ";
    stack<Task> tempStack = S;
    while (!tempStack.empty()) {
        Task task = tempStack.top();
        chrono::duration<double> taskArrivalTime = task.arrivalTime - startTime;
        cout << task.name << "(" << taskArrivalTime.count() << "s) ";
        tempStack.pop();
    }
    cout << "\n";

    if (currentTask.priority >= 0) {
        chrono::duration<double> taskArrivalTime = currentTask.arrivalTime - startTime;
        cout << "Выполняется задача: " << currentTask.name << " (приоритет " << currentTask.priority << ", поступила через " << taskArrivalTime.count() << "s)\n";
    }
    else {
        cout << "Процессор свободен\n";
    }
    cout << "----------------------------------------\n";
}

void executeTask(Task& currentTask, queue<Task>& f0, queue<Task>& f1, queue<Task>& f2, stack<Task>& S, bool& taskFromStack, chrono::time_point<chrono::steady_clock> startTime) {
    while (true) {
        // Ждем до 15 секунд, вне зависимости от текущей задачи
        this_thread::sleep_for(chrono::seconds(15));

        {
            lock_guard<mutex> lock(mtx);
            chrono::time_point<chrono::steady_clock> currentTime = chrono::steady_clock::now();
            chrono::duration<double> elapsedTime = currentTime - startTime;

            if (currentTask.priority >= 0) {
                chrono::duration<double> taskArrivalTime = currentTask.arrivalTime - startTime;
                cout << "Задача выполнена: " << currentTask.name << " (приоритет " << currentTask.priority << ", поступила через " << taskArrivalTime.count() << "s)\n";
            }
        }
        currentTask.priority = -1;

        if (!f0.empty()) {
            currentTask = f0.front();
            f0.pop();
        }
        else if (!f1.empty()) {
            currentTask = f1.front();
            f1.pop();
        }
        else if (!f2.empty()) {
            currentTask = f2.front();
            f2.pop();
        }
        else if (!S.empty()) {
            Task stackTask = S.top();
            S.pop();
            taskFromStack = true;
            currentTask = stackTask;
        }
        else {
            taskFromStack = false;
            currentTask.priority = -1;
        }

        displayState(f0, f1, f2, S, currentTask, startTime);
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    queue<Task> f0, f1, f2;
    stack<Task> S;
    Task currentTask(-1, "", chrono::steady_clock::now());
    bool taskFromStack = false;

    chrono::time_point<chrono::steady_clock> startTime = chrono::steady_clock::now();
    thread stackThread(executeTask, ref(currentTask), ref(f0), ref(f1), ref(f2), ref(S), ref(taskFromStack), startTime);
    stackThread.detach();

    while (true) {
        cout << "Выберите действие (0 - добавить задачу в f0, 1 - добавить задачу в f1, 2 - добавить задачу в f2, 3 - создать случайную задачу, 9 - завершить): \n";
        int choice;
        cin >> choice;

        if (choice == 0 || choice == 1 || choice == 2) {
            if (f0.size() + f1.size() + f2.size() + S.size() >= 3 * MaxTasks) {
                cout << "Все очереди и стек полностью заполнены. Невозможно добавить новую задачу.\n";
            }
            else {
                string taskName;
                cout << "Введите имя задачи: ";
                cin.ignore();
                getline(cin, taskName);

                chrono::time_point<chrono::steady_clock> currentTime = chrono::steady_clock::now();
                if (choice == 0 && f0.size() < MaxTasks) {
                    f0.push(Task(0, taskName, currentTime));
                }
                else if (choice == 1 && f1.size() < MaxTasks) {
                    f1.push(Task(1, taskName, currentTime));
                }
                else if (choice == 2 && f2.size() < MaxTasks) {
                    f2.push(Task(2, taskName, currentTime));
                }
                else {
                    cout << "Очередь полностью заполнена. Задача не добавлена.\n";
                }

                if (!taskFromStack) {
                    if (currentTask.priority == -1 || currentTask.priority > choice) {
                        if (currentTask.priority != -1) {
                            if (currentTask.priority > choice) {
                                S.push(currentTask);
                                // Выбираем следующую задачу для выполнения с наивысшим приоритетом
                                if (!f0.empty()) {
                                    currentTask = f0.front();
                                    f0.pop();
                                }
                                else if (!f1.empty()) {
                                    currentTask = f1.front();
                                    f1.pop();
                                }
                                else if (!f2.empty()) {
                                    currentTask = f2.front();
                                    f2.pop();
                                }
                                else if (!S.empty()) {
                                    currentTask = S.top();
                                    S.pop();
                                }
                            }
                            else {
                                // Если текущая выполняющаяся задача имеет такой же приоритет, она останется в очереди
                                if (currentTask.priority == 0) {
                                    f0.push(currentTask);
                                }
                                else if (currentTask.priority == 1) {
                                    f1.push(currentTask);
                                }
                                else if (currentTask.priority == 2) {
                                    f2.push(currentTask);
                                }

                                // Здесь мы выбираем задачу с наивысшим приоритетом из всех доступных
                                if (!f0.empty()) {
                                    currentTask = f0.front();
                                    f0.pop();
                                }
                                else if (!f1.empty()) {
                                    currentTask = f1.front();
                                    f1.pop();
                                }
                                else if (!f2.empty()) {
                                    currentTask = f2.front();
                                    f2.pop();
                                }
                                else if (!S.empty()) {
                                    currentTask = S.top();
                                    S.pop();
                                }
                            }
                        }
                        else {
                            // Здесь мы выбираем задачу с наивысшим приоритетом из всех доступных
                            if (!f0.empty()) {
                                currentTask = f0.front();
                                f0.pop();
                            }
                            else if (!f1.empty()) {
                                currentTask = f1.front();
                                f1.pop();
                            }
                            else if (!f2.empty()) {
                                currentTask = f2.front();
                                f2.pop();
                            }
                            else if (!S.empty()) {
                                currentTask = S.top();
                                S.pop();
                            }
                        }
                    }
                }
            }
        }
        else if (choice == 3) {
            if (f0.size() + f1.size() + f2.size() + S.size() >= 3 * MaxTasks) {
                cout << "Все очереди и стек полностью заполнены. Невозможно создать случайную задачу.\n";
            }
            else {
                random_device rd;
                mt19937 gen(rd());
                uniform_int_distribution<int> priorityDist(0, 2);
                uniform_int_distribution<int> nameDist(1, 20);
                int randomPriority = priorityDist(gen);
                int randomName = nameDist(gen);
                string taskName = to_string(randomName);

                chrono::time_point<chrono::steady_clock> currentTime = chrono::steady_clock::now();
                if (randomPriority == 0 && f0.size() < MaxTasks) {
                    f0.push(Task(0, taskName, currentTime));
                }
                else if (randomPriority == 1 && f1.size() < MaxTasks) {
                    f1.push(Task(1, taskName, currentTime));
                }
                else if (randomPriority == 2 && f2.size() < MaxTasks) {
                    f2.push(Task(2, taskName, currentTime));
                }
                else {
                    cout << "Очередь полностью заполнена. Случайная задача не добавлена.\n";
                }

                if (!taskFromStack) {
                    if (currentTask.priority == -1 || currentTask.priority > randomPriority) {
                        if (currentTask.priority != -1) {
                            S.push(currentTask);
                        }
                        currentTask = (randomPriority == 0) ? f0.front() : (randomPriority == 1) ? f1.front() : f2.front();
                        if (randomPriority == 0 && !f0.empty()) {
                            f0.pop();
                        }
                        else if (randomPriority == 1 && !f1.empty()) {
                            f1.pop();
                        }
                        else if (randomPriority == 2 && !f2.empty()) {
                            f2.pop();
                        }
                    }
                }
            }
        }
        else if (choice == 9) {
            cout << "Программа завершена\n";
            break;
        }
        else {
            cout << "Недопустимый выбор. Пожалуйста, выберите 0, 1, 2, 3 или 9 (завершить).\n";
        }

        displayState(f0, f1, f2, S, currentTask, startTime);
    }

    return 0;
}
