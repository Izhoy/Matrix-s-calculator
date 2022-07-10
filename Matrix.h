#pragma once

#include <iostream>
#include <stdexcept>
#include <chrono>

using namespace std;
using namespace std::chrono;

class Matrix
{
private:
	int StringCount;  // Number of strings
	int ColumnCount; // Number of columns
	int **element;  // Pointer of element
public:
	Matrix(int StringCount = 1, int ColumnCount = 1);
	Matrix(const Matrix&);
	~Matrix();

	void Random(int, int);  // Method that fill matrix with random numbers
	Matrix& Transposition(); // Transposition of matrix
	Matrix& Minor(unsigned int, unsigned int);  // Removal one string and one column from matrix
	int Determinant(); // Determinant of matrix

	// Operator`s overloads
	Matrix& operator=(const Matrix&);
	Matrix& operator+(const Matrix&);
	Matrix& operator-(const Matrix&);
	Matrix& operator*(const Matrix&);

	friend ostream& operator<<(ostream&, Matrix&);
	friend istream& operator>>(istream&, Matrix&);
};

