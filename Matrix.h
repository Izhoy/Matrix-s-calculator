#pragma once

#include <iostream>
#include <stdexcept>
#include <chrono>

using namespace std;
using namespace std::chrono;

class Matrix
{
private:
	int Xdimension;
	int Ydimension;
	int **element;
public:
	Matrix(int Xdimension = 1, int Ydimension = 1);
	Matrix(const Matrix&);
	~Matrix();

	void Random(int, int);
	Matrix Transposition();
	int Determinant();

	Matrix operator=(const Matrix&);
	Matrix operator+(const Matrix&);
	Matrix operator-(const Matrix&);
	Matrix operator*(const Matrix&);

	friend ostream& operator<<(ostream&, Matrix);
	friend istream& operator>>(istream&, Matrix);
};

