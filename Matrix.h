#pragma once

#include <iostream>
#include <stdexcept>
#include <chrono>

using namespace std;
using namespace std::chrono;

class Matrix
{
private:
	int StringCount;  // ���������� �����
	int ColumnCount; // ���������� ��������
	int **element;  // ��������� �� ������� �������
public:
	Matrix(int StringCount = 1, int ColumnCount = 1);
	Matrix(const Matrix&);
	~Matrix();

	void Random(int, int);  // ������� ���������� ������� ���������� �������
	Matrix& Transposition(); // ���������������� �������
	Matrix& Minor(unsigned int, unsigned int);  // ��������� ������
	int Determinant(); // ������� ������������

	//���������� ����������
	Matrix& operator=(const Matrix&);
	Matrix& operator+(const Matrix&);
	Matrix& operator-(const Matrix&);
	Matrix& operator*(const Matrix&);

	friend ostream& operator<<(ostream&, Matrix&);
	friend istream& operator>>(istream&, Matrix&);
};

