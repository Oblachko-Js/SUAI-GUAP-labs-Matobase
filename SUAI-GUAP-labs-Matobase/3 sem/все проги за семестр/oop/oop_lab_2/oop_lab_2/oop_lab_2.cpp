#include <iostream>
#include <cmath>
#include <limits> 

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

using namespace std;

class Triangle {
private:
    double a, b, c;

public:
    Triangle(double sideA, double sideB, double sideC);

    Triangle();

    Triangle(const Triangle& other);

    ~Triangle();

    void setSideA(double sideA);
    void setSideB(double sideB);
    void setSideC(double sideC);

    void calculateAngles();
};

Triangle::Triangle(double sideA, double sideB, double sideC) : a(sideA), b(sideB), c(sideC) {}

Triangle::Triangle() : a(0), b(0), c(0) {}

Triangle::Triangle(const Triangle& other) : a(other.a), b(other.b), c(other.c) {}

Triangle::~Triangle() {}

void Triangle::setSideA(double sideA) {
    a = sideA;
}

void Triangle::setSideB(double sideB) {
    b = sideB;
}

void Triangle::setSideC(double sideC) {
    c = sideC;
}

void Triangle::calculateAngles() {
    while (true) {
        if (a + b <= c || a + c <= b || b + c <= a) {
            cout << "Треугольник с такими сторонами не существует. Пожалуйста, введите корректные значения." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Введите длину стороны A: ";
            cin >> a;
            cout << "Введите длину стороны B: ";
            cin >> b;
            cout << "Введите длину стороны C: ";
            cin >> c;
        }
        else {
            break;
        }
    }

    double alpha = acos((b * b + c * c - a * a) / (2 * b * c));
    double beta = acos((a * a + c * c - b * b) / (2 * a * c));
    double gamma = acos((a * a + b * b - c * c) / (2 * a * b));

    alpha = alpha * 180.0 / M_PI;
    beta = beta * 180.0 / M_PI;
    gamma = gamma * 180.0 / M_PI;

    cout << "Угол a: " << alpha << " градусов" << endl;
    cout << "Угол b: " << beta << " градусов" << endl;
    cout << "Угол c: " << gamma << " градусов" << endl;
}

int main() {
    system("chcp 1251 > nul");
    system("color 71");
    double sideA1, sideB1, sideC1;
    cout << "Введите длину стороны A для первого треугольника: ";
    cin >> sideA1;
    cout << "Введите длину стороны B для первого треугольника: ";
    cin >> sideB1;
    cout << "Введите длину стороны C для первого треугольника: ";
    cin >> sideC1;
    cout << "Треугольник с использованием конструктора с параметрами введенными пользователем: \n";
    Triangle triangle1(sideA1, sideB1, sideC1);
    triangle1.calculateAngles();
    cout << "Треугольник с использованием конструктора по умолчанию с параметрами a = 3, b = 4 , c = 5: \n";
    Triangle triangle2;
    triangle2.setSideA(3.0);
    triangle2.setSideB(4.0);
    triangle2.setSideC(5.0);
    triangle2.calculateAngles();
    cout << "Треугольник с использованием конструктора копирования из конструктора с параметрами пользователя: \n";
    Triangle triangle3(triangle1);
    triangle3.calculateAngles();

    return 0;
}
