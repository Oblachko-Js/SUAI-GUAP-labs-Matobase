// Файл trapezoid.h
#ifndef TRAPEZOID_H
#define TRAPEZOID_H

#include "shape.h"
#include "line.h"
#include <memory>

// Класс Trapezoid наследуется от класса Shape
class Trapezoid : public Shape
{
private:
    // Уникальные указатели на объекты Line, представляющие стороны трапеции
    std::unique_ptr<Line> _topLeftToTopRight;
    std::unique_ptr<Line> _topRightToBottomRight;
    std::unique_ptr<Line> _bottomRightToBottomLeft;
    std::unique_ptr<Line> _bottomLeftToTopLeft;

public:
    // Конструктор, принимающий координаты вершин трапеции и создающий объекты Line для сторон
    Trapezoid(const Point& topLeft, const Point& topRight, const Point& bottomLeft, const Point& bottomRight);

    // Методы для отрисовки и перемещения трапеции
    void draw(Screen* screen) const override;
    void move(Point p) override;

    // Методы для получения координат вершин трапеции
    Point getLeftTop() const;
    Point getRightTop() const;
    Point getLeftBottom() const;
    Point getRightBottom() const;

    // Деструктор по умолчанию
    ~Trapezoid() override;
};

// Реализация конструктора Trapezoid
Trapezoid::Trapezoid(const Point& topLeft, const Point& topRight, const Point& bottomLeft, const Point& bottomRight)
    : _topLeftToTopRight(std::make_unique<Line>(topLeft, topRight)),
    _topRightToBottomRight(std::make_unique<Line>(topRight, bottomRight)),
    _bottomRightToBottomLeft(std::make_unique<Line>(bottomRight, bottomLeft)),
    _bottomLeftToTopLeft(std::make_unique<Line>(bottomLeft, topLeft))
{
}

// Реализация метода отрисовки трапеции
void Trapezoid::draw(Screen* screen) const
{
    _topLeftToTopRight->draw(screen);
    _topRightToBottomRight->draw(screen);
    _bottomRightToBottomLeft->draw(screen);
    _bottomLeftToTopLeft->draw(screen);
}

// Реализация метода перемещения трапеции
void Trapezoid::move(Point p)
{
    _topLeftToTopRight->move(p);
    _topRightToBottomRight->move(p);
    _bottomRightToBottomLeft->move(p);
    _bottomLeftToTopLeft->move(p);
}

// Реализация методов получения координат вершин трапеции
Point Trapezoid::getLeftTop() const
{
    return _topLeftToTopRight->getLeftTop();
}

Point Trapezoid::getRightTop() const
{
    return _topRightToBottomRight->getRightTop();
}

Point Trapezoid::getLeftBottom() const
{
    return _bottomLeftToTopLeft->getLeftBottom();
}

Point Trapezoid::getRightBottom() const
{
    return _bottomRightToBottomLeft->getRightBottom();
}

// Реализация деструктора по умолчанию
Trapezoid::~Trapezoid() = default;

#endif // TRAPEZOID_H
