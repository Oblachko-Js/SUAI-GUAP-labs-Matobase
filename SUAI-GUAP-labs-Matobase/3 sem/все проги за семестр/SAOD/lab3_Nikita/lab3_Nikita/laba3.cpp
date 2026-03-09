#include <iostream>
#include <chrono>
#include <string>
#include <list>
#include <mutex>
#include <random>
#include <thread>

using namespace std;

struct Task {
    int priority;
    string name;
    chrono::time_point<chrono::steady_clock> arrivalTime;

    Task(int p, const string& n, chrono::time_point<chrono::steady_clock> time)
        : priority(p), name(n), arrivalTime(time) {}
};

mutex mtx;

void displayState(
    const list<Task>& f0,
    const list<Task>& f1,
    const list<Task>& f2,
    const list<Task>& S,
    const Task& currentTask,
    chrono::time_point<chrono::steady_clock> startTime
) {
    chrono::time_point<chrono::steady_clock> currentTime = chrono::steady_clock::now();
    chrono::duration<double> elapsedTime = currentTime - startTime;

    cout << "Высший приоритет: ";
    for (const Task& task : f0) {
        chrono::duration<double> taskArrivalTime = task.arrivalTime - startTime;
        cout << task.name << "(" << taskArrivalTime.count() << "s) ";
    }
    cout << "\n";

    cout << "Средний приоритет: ";
    for (const Task& task : f1) {
        chrono::duration<double> taskArrivalTime = task.arrivalTime - startTime;
        cout << task.name << "(" << taskArrivalTime.count() << "s) ";
    }
    cout << "\n";

    cout << "Низкий приоритет: ";
    for (const Task& task : f2) {
        chrono::duration<double> taskArrivalTime = task.arrivalTime - startTime;
        cout << task.name << "(" << taskArrivalTime.count() << "s) ";
    }
    cout << "\n";

    cout << "Стек S: ";
    for (const Task& task : S) {
        chrono::duration<double> taskArrivalTime = task.arrivalTime - startTime;
        cout << task.name << "(" << taskArrivalTime.count() << "s) ";
    }
    cout << "\n";

    if (currentTask.priority >= 0) {
        chrono::duration<double> taskArrivalTime = currentTask.arrivalTime - startTime;
        cout << "Выполняется задача: " << currentTask.name << " (приоритет " << currentTask.priority << ", поступила через " << taskArrivalTime.count() << "s)\n";
    }
    else {
        cout << "Процессор свободен\n";
    }
    cout << "\n";
}

void executeTask(Task& currentTask, list<Task>& f0, list<Task>& f1, list<Task>& f2, list<Task>& S, bool& taskFromStack, chrono::time_point<chrono::steady_clock> startTime) {
    while (true) {
        this_thread::sleep_for(chrono::seconds(5));
        {
            lock_guard<mutex> lock(mtx);
            chrono::time_point<chrono::steady_clock> currentTime = chrono::steady_clock::now();
            chrono::duration<double> elapsedTime = currentTime - startTime;

            cout << "Задача выполнена: " << currentTask.name << endl;

            if (!f0.empty()) {
                Task task = f0.front();
                chrono::duration<double> taskArrivalTime = task.arrivalTime - startTime;
            }
            else if (!f1.empty()) {
                Task task = f1.front();
                chrono::duration<double> taskArrivalTime = task.arrivalTime - startTime;
            }
            else if (!f2.empty()) {
                Task task = f2.front();
                chrono::duration<double> taskArrivalTime = task.arrivalTime - startTime;
            }
            else if (!S.empty()) {
                Task task = S.back();
                chrono::duration<double> taskArrivalTime = task.arrivalTime - startTime;
            }
        }
        currentTask.priority = -1;

        if (!f0.empty()) {
            currentTask = f0.front();
            f0.pop_front();
        }
        else if (!f1.empty()) {
            currentTask = f1.front();
            f1.pop_front();
        }
        else if (!f2.empty()) {
            currentTask = f2.front();
            f2.pop_front();
        }
        else if (!S.empty()) {
            Task stackTask = S.back();
            S.pop_back();
            taskFromStack = true;
            currentTask = stackTask;
        }
        else {
            taskFromStack = false;
            currentTask.priority = -1;
            break;
        }

        displayState(f0, f1, f2, S, currentTask, startTime);
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    list<Task> f0, f1, f2;
    list<Task> S;
    Task currentTask(-1, "", chrono::steady_clock::now());
    bool taskFromStack = false;

    chrono::time_point<chrono::steady_clock> startTime = chrono::steady_clock::now();
    thread stackThread(executeTask, ref(currentTask), ref(f0), ref(f1), ref(f2), ref(S), ref(taskFromStack), startTime);
    stackThread.detach();

    while (true) {
        cout << "Выберите действие: \n" << "(0 - Высший приоритет, 1 - Средний приоритет, 2 - Низкий приоритет, 3 - Рандомная задача, 9 - завершить):";
        int choice;
        cin >> choice;

        if (choice == 0 || choice == 1 || choice == 2) {
            string taskName;
            cout << "Введите имя задачи: ";
            cin.ignore();
            getline(cin, taskName);

            chrono::time_point<chrono::steady_clock> currentTime = chrono::steady_clock::now();
            if (choice == 0) {
                f0.push_back(Task(0, taskName, currentTime));
            }
            else if (choice == 1) {
                f1.push_back(Task(1, taskName, currentTime));
            }
            else if (choice == 2) {
                f2.push_back(Task(2, taskName, currentTime));
            }

            if (!taskFromStack) {
                if (currentTask.priority == -1 || currentTask.priority > choice) {
                    if (currentTask.priority != -1) {
                        S.push_back(currentTask);
                    }
                    currentTask = (choice == 0) ? f0.front() : (choice == 1) ? f1.front() : f2.front();
                    if (choice == 0) {
                        f0.pop_front();
                    }
                    else if (choice == 1) {
                        f1.pop_front();
                    }
                    else if (choice == 2) {
                        f2.pop_front();
                    }
                }
            }
        }
        else if (choice == 3) {
            random_device rd;
            mt19937 gen(rd());
            uniform_int_distribution<int> priorityDist(0, 2);
            uniform_int_distribution<int> nameDist(1, 20);
            int randomPriority = priorityDist(gen);
            int randomName = nameDist(gen);
            string taskName = to_string(randomName);

            chrono::time_point<chrono::steady_clock> currentTime = chrono::steady_clock::now();
            if (randomPriority == 0) {
                f0.push_back(Task(0, taskName, currentTime));
            }
            else if (randomPriority == 1) {
                f1.push_back(Task(1, taskName, currentTime));
            }
            else if (randomPriority == 2) {
                f2.push_back(Task(2, taskName, currentTime));
            }

            if (!taskFromStack) {
                if (currentTask.priority == -1 or currentTask.priority > randomPriority) {
                    if (currentTask.priority != -1) {
                        S.push_back(currentTask);
                    }
                    currentTask = (randomPriority == 0) ? f0.front() : (randomPriority == 1) ? f1.front() : f2.front();
                    if (randomPriority == 0) {
                        f0.pop_front();
                    }
                    else if (randomPriority == 1) {
                        f1.pop_front();
                    }
                    else if (randomPriority == 2) {
                        f2.pop_front();
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
