#include <iostream>
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

using namespace std;

class Angle {
private:
    int gradus;
    int min;
    int sec;

public:
    void SetGradus(int g);
    void SetMin(int m);
    void SetSec(int s);
    void Display();
    double ToRadians();
};

void Angle::SetGradus(int g) {
    gradus = g;
}

void Angle::SetMin(int m) {
    min = m;
}

void Angle::SetSec(int s) {
    sec = s;
}

void Angle::Display() {
    cout << "Угол: " << gradus << " градусов, " << min << " минут, " << sec << " секунд" << endl;
}

double Angle::ToRadians() {
    double totalDegrees = gradus + min / 60.0 + sec / 3600.0;
    double radians = totalDegrees * M_PI / 180.0;
    return radians;
}

void InputAngle(Angle& angle) {
    int g, m, s;
    bool validInput = false;

    while (!validInput) {
        cout << "Введите градусы (от 0 до 360): ";
        cin >> g;
        if (cin.fail() || g < 0 || g > 360) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Некорректный ввод. Введите число от 0 до 360." << endl;
        }
        else {
            validInput = true;
        }
    }
    angle.SetGradus(g);

    validInput = false;
    while (!validInput) {
        cout << "Введите минуты (от 0 до 60): ";
        cin >> m;
        if (cin.fail() || m < 0 || m > 60) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Некорректный ввод. Введите число от 0 до 60." << endl;
        }
        else {
            validInput = true;
        }
    }
    angle.SetMin(m);

    validInput = false;
    while (!validInput) {
        cout << "Введите секунды (от 0 до 60): ";
        cin >> s;
        if (cin.fail() || s < 0 || s > 60) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Некорректный ввод. Введите число от 0 до 60." << endl;
        }
        else {
            validInput = true;
        }
    }
    angle.SetSec(s);
}


int main() {
    system("chcp 1251 > nul");
    system("color 71");
    Angle angle;
    InputAngle(angle);

    angle.Display();

    double radians = angle.ToRadians();
    cout << "Угол в радианах: " << radians << endl;

    return 0;
}
