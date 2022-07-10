#pragma once

#include <iostream>
#include <stdexcept>
#include <chrono>

using namespace std;
using namespace std::chrono;

class Matrix
{
private:
	int StringCount;  // Количество строк
	int ColumnCount; // Количество столбцов
	int **element;  // Указатель на элемент матрицы
public:
	Matrix(int StringCount = 1, int ColumnCount = 1);
	Matrix(const Matrix&);
	~Matrix();

	void Random(int, int);  // Функция заполнения матрицы случайными числами
	Matrix& Transposition(); // Транспонирование матрицы
	Matrix& Minor(unsigned int, unsigned int);  // Выделение минора
	int Determinant(); // Подсчёт определителя

	//Перегрузка операторов
	Matrix& operator=(const Matrix&);
	Matrix& operator+(const Matrix&);
	Matrix& operator-(const Matrix&);
	Matrix& operator*(const Matrix&);

	friend ostream& operator<<(ostream&, Matrix&);
	friend istream& operator>>(istream&, Matrix&);
};

