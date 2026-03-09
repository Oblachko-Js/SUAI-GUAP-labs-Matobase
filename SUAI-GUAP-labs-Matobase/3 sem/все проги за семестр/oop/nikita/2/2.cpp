//4 лаба
#include <iostream>
#include <cmath>

const float M_PI = 3.14;

class Angle {
protected:
    double degrees;

public:
    Angle(double initialDegrees = 0.0);

    void setDegrees(double newDegrees);

    double getDegrees() const;

    double getRadians() const;

    void add(const Angle& other);

    void subtract(double degrees);

    void normalize();
};

class Triangle : public Angle {
private:
    Angle angleB;
    Angle angleC;

public:
    Triangle(double aDegrees = 0.0, double bDegrees = 0.0, double cDegrees = 0.0);

    // Add methods to get angles in radians
    double getAngleAInRadians() const;
    double getAngleBInRadians() const;
    double getAngleCInRadians() const;

    // Add a method to get angleB in degrees
    double getAngleB() const;

    void setAngleC(double cDegrees);

    double getAngleC() const;

    double getArea() const;

    bool isTriangleValid() const;
};

Angle::Angle(double initialDegrees) : degrees(initialDegrees) {
    normalize();
}

void Angle::setDegrees(double newDegrees) {
    if (newDegrees > 0) {
        degrees = newDegrees;
    }
    else {
        std::cerr << "Ошибка: Градусы должны быть положительными." << std::endl;
    }
    normalize();
}

double Angle::getDegrees() const {
    return degrees;
}

double Angle::getRadians() const {
    return degrees * M_PI / 180.0;
}

void Angle::add(const Angle& other) {
    degrees += other.degrees;
    normalize();
}

void Angle::subtract(double degrees) {
    this->degrees -= degrees;
    normalize();
}

void Angle::normalize() {
    while (degrees >= 360.0) {
        degrees -= 360.0;
    }
    while (degrees < 0.0) {
        degrees += 360.0;
    }
}

Triangle::Triangle(double aDegrees, double bDegrees, double cDegrees)
    : Angle(aDegrees), angleB(bDegrees), angleC(cDegrees) {
    setAngleC(cDegrees);
}

void Triangle::setAngleC(double cDegrees) {
    if (cDegrees > 0) {
        angleC.setDegrees(cDegrees);
    }
    else {
        std::cerr << "Ошибка: Градусы должны быть положительными." << std::endl;
    }
}

double Triangle::getAngleAInRadians() const {
    return getRadians();
}

double Triangle::getAngleB() const {
    return angleB.getDegrees();
}

double Triangle::getAngleBInRadians() const {
    return angleB.getRadians();
}

double Triangle::getAngleCInRadians() const {
    return angleC.getRadians();
}

double Triangle::getAngleC() const {
    return angleC.getDegrees();
}

double Triangle::getArea() const {
    double a = sin(getAngleAInRadians());
    double b = sin(getAngleBInRadians());
    double c = sin(getAngleCInRadians());

    double s = (a + b + c) / 2.0;
    double area = std::sqrt(s * (s - a) * (s - b) * (s - c));

    return area;
}

bool Triangle::isTriangleValid() const {
    return getDegrees() + angleC.getDegrees() + getAngleC() == 180.0;
}

int main() {
    system("chcp 1251 > nul");
    system("color 71");

    double angle1Value, angle2Value;
    do {
        std::cout << "Введите значение угла 1 (в градусах): ";
        std::cin >> angle1Value;
        std::cout << "Введите значение угла 2 (в градусах): ";
        std::cin >> angle2Value;
        if (angle1Value <= 0 || angle2Value <= 0) {
            std::cerr << "Ошибка: Градусы должны быть положительными." << std::endl;
        }
    } while (angle1Value <= 0 || angle2Value <= 0 || angle1Value + angle2Value >= 180);

    Angle angle1(angle1Value);
    Angle angle2(angle2Value);

    std::cout << "Исходные углы:" << std::endl;
    std::cout << "Угол 1: " << angle1Value << " градусов, " << angle1.getRadians() << " радиан" << std::endl;
    std::cout << "Угол 2: " << angle2Value << " градусов, " << angle2.getRadians() << " радиан" << std::endl;

    angle1.add(angle2);
    angle2.subtract(angle1Value);

    std::cout << "Измененные углы:" << std::endl;
    std::cout << "Сумма углов: " << angle1.getDegrees() << " градусов, " << angle1.getRadians() << " радиан" << std::endl;
    std::cout << "Разность углов: " << angle2.getDegrees() << " градусов, " << angle2.getRadians() << " радиан" << std::endl;

    double angleAValue, angleBValue, angleCValue;
    do {
        std::cout << "Введите значение угла A (в градусах): ";
        std::cin >> angleAValue;
        std::cout << "Введите значение угла B (в градусах): ";
        std::cin >> angleBValue;
        std::cout << "Введите значение угла C (в градусах): ";
        std::cin >> angleCValue;

        if (angleAValue <= 0 || angleBValue <= 0 || angleCValue <= 0) {
            std::cerr << "Ошибка: Градусы должны быть положительными." << std::endl;
        }
        if (angleAValue + angleBValue + angleCValue != 180) {
            std::cerr << "Ошибка: Сумма углов треугольника должна быть равна 180 градусов." << std::endl;
        }
    } while (angleAValue <= 0 || angleBValue <= 0 || angleCValue <= 0 || angleAValue + angleBValue + angleCValue != 180);

    Triangle triangle(angleAValue, angleBValue, angleCValue);

    std::cout << "Углы треугольника:" << std::endl;
    std::cout << "Угол A: " << triangle.getDegrees() << " градусов, " << triangle.getAngleAInRadians() << " радиан" << std::endl;
    std::cout << "Угол B: " << triangle.getAngleB() << " градусов, " << triangle.getAngleBInRadians() << " радиан" << std::endl;
    std::cout << "Угол C: " << triangle.getAngleC() << " градусов, " << triangle.getAngleCInRadians() << " радиан" << std::endl;
    std::cout << "Площадь треугольника: " << triangle.getArea() << std::endl;

    return 0;
}