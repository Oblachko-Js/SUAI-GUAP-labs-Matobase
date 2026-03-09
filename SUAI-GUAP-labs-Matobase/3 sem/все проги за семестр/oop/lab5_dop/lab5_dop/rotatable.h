#pragma once
// Файл rotatable.h
#ifndef ROTATABLE_H
#define ROTATABLE_H
class Rotatable { //Фигуры, пригодные к повороту
public:
	virtual void rotateLeft() = 0; //Повернуть влево
	virtual void rotateRight() = 0; //Повернуть вправо
};
#endif // ROTATABLE_H