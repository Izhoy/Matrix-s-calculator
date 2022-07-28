#pragma once

#include <iostream>
#include <stdexcept>
#include <random>

using namespace std;

string err_arguments = "Matrix dimension must not be equal to zero (Matrix Constructor)";
string err_dimension = "Dimensions are different ('+', '-' or '*' overload)";
string err_memory = "Not enough memory";
string err_square_matrix = "Matrix is not square (Determinant function)";
string err_invalid_arguments_minor = "Input arguments are not acceptable (Minor funstion)";
string err_invalid_arguments_index = "Input argumants are not acceptable (operator () )";
string err_determinant_is_zero = "Determinant of matrix is equal to zero (Inverse function)";
string err_arguments_set_element = "Arguments are greater than matrix dimensions (setElement function)";

template <typename T = int>
class Matrix
{
private:
	size_t RowCount;  // Количество строк
	size_t ColumnCount; // Количество столбцов
	T **matrix;  // Указатель на элемент матрицы

public:
	Matrix(size_t RowCount = 1, size_t ColumnCount = 1);  // Конструктор
	Matrix(const Matrix&); // Конструктор копирования
	Matrix(Matrix&&);  // Конструктор перемещения
	~Matrix();  // Деструктор

	const size_t getRowCount() { return RowCount; }  // Get методы
	const size_t getColumnCount() { return ColumnCount; }

	void setElement(unsigned int, unsigned int, T);  // Изменение элемента матрицы

	void fillRandom(int, int);  // Функция заполнения матрицы случайными числами
	const Matrix<T> Transposition(); // Транспонирование матрицы
	Matrix<T> Minor(unsigned int, unsigned int);  // Выделение минора
	const T Determinant(); // Подсчёт определителя
	Matrix<double> Inverse(); // Подсчёт обратной матрицы

	//Перегрузка операторов
	Matrix operator=(const Matrix&); // Присваивание
	Matrix operator=(Matrix&&);  // Присваивание с перемещением
	Matrix operator+(const Matrix&); // Сложение
	Matrix operator-(const Matrix&); // Вычитание
	Matrix operator*(const Matrix&); // Умножение
	const T &operator()(unsigned int, unsigned int); // Индексация 

	template <typename T>
	friend ostream& operator<<(ostream&, const Matrix<T>&); // Выходной поток
	template <typename T>
	friend istream& operator>>(istream&, const Matrix<T>&); // Входной поток

	friend Matrix<double> operator*(const Matrix<double>, const Matrix<int>);  // Специализация для матриц double и int
	friend Matrix<double> operator*(const Matrix<int>, const Matrix<double>);
};

// Конструктор
template <typename T>
Matrix<T>::Matrix(size_t RowCount, size_t ColumnCount) {
	if (RowCount == 0 || ColumnCount == 0) {
		throw invalid_argument(err_arguments);
	}
	else {
		this->RowCount = RowCount;
		this->ColumnCount = ColumnCount;
	}
	size_t i = 0;
	try {
		matrix = new T * [this->RowCount];
		for (; i < this->RowCount; ++i) {
			matrix[i] = new T[this->ColumnCount];
		}
	}
	catch (bad_alloc& err) {
		for (size_t j = 0; j != i; ++j) {
			delete[] matrix[i];
		}
		delete[] matrix;

		cout << err.what() << endl;
		throw invalid_argument(err_memory);
	}
}

// Конструктор копирования
template <typename T>
Matrix<T>::Matrix(const Matrix& A)
	:RowCount(A.RowCount), ColumnCount(A.ColumnCount) {

	size_t i = 0;
	try {
		matrix = new T * [RowCount];
		for (; i < RowCount; ++i) {
			matrix[i] = new T[ColumnCount];
		}
	}
	catch (bad_alloc& err) {
		for (size_t j = 0; j != i; ++j) {
			delete[] matrix[i];
		}
		delete[] matrix;

		cout << err.what() << endl;
		throw invalid_argument(err_memory);
	}

	for (size_t i = 0; i < RowCount; ++i) {
		for (size_t j = 0; j < ColumnCount; ++j) {
			matrix[i][j] = A.matrix[i][j];
		}
	}
}

// Конструктор перемещения
template <typename T>
Matrix<T>::Matrix(Matrix&& A) :
	RowCount(A.RowCount), ColumnCount(A.ColumnCount), matrix(A.matrix) {
	A.RowCount = 0;
	A.ColumnCount = 0;
	A.matrix = nullptr;
}

// Деструктор
template <typename T>
Matrix<T>::~Matrix() {
	if (matrix != nullptr) {
		for (size_t i = 0; i < this->RowCount; ++i) {
			if (matrix[i] != nullptr)
				delete[] matrix[i];
		}
		delete[] matrix;
	}
}

// Изменение определённого элемента матрицы
template<typename T>
void Matrix<T>::setElement(unsigned int i, unsigned int j, T value){
	if (i > RowCount || j > ColumnCount)
		throw invalid_argument(err_arguments_set_element);

	matrix[i][j] = value;
}

//Метод заполнения матрицы случайными числами
template <typename T>
void Matrix<T>::fillRandom(int min, int max) {

	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> dist(min, max);

	for (size_t i = 0; i < RowCount; ++i) {
		for (size_t j = 0; j < ColumnCount; ++j) {
			matrix[i][j] = dist(gen);
		}
	}
}

// Метод транспонирования матрицы
template <typename T>
const Matrix<T> Matrix<T>::Transposition() {
	Matrix<T> Tran = Matrix(ColumnCount, RowCount);

	for (size_t i = 0; i < RowCount; ++i) {
		for (size_t j = 0; j < ColumnCount; ++j) {
			Tran.matrix[j][i] = matrix[i][j];
		}
	}
	return Tran;
}

// Метод выделения минора (необходим для подсчёта определителя)
template <typename T>
Matrix<T> Matrix<T>::Minor(unsigned int x, unsigned int y)
{
	if (x == 0 || y == 0 || x > RowCount || y > ColumnCount)
		throw invalid_argument(err_invalid_arguments_minor);

	Matrix<T> M = Matrix<T>(RowCount - 1, ColumnCount - 1);

	for (size_t i = 0, n = 0; i < RowCount - 1, n < RowCount; ++i, ++n) {
		if (n == x - 1) ++n;
		if (n == RowCount) break;
		for (size_t j = 0, m = 0; j < ColumnCount - 1, m < ColumnCount; ++j, ++m) {
			if (m == y - 1) ++m;
			M.matrix[i][j] = matrix[n][m];
		}
	}

	return M;
}

// Метод подсчёта определителя
template <typename T>
const T Matrix<T>::Determinant() {
	if (RowCount != ColumnCount) throw(invalid_argument(err_square_matrix));

	T Det = 0;

	if (RowCount == 2) {
		Det = matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
		return Det;
	}

	for (unsigned int i = 0; i < RowCount; ++i) {
		Det += (int)pow(-1, (i + 1) + 1) * matrix[0][i] * this->Minor(1, i + 1).Determinant();
	}
	return Det;
}

// Метод подсчёта обратной матрицы
template<typename T>
Matrix<double> Matrix<T>::Inverse(){
	double Det = (double)this->Determinant();
	if (Det == 0) throw invalid_argument(err_determinant_is_zero);

	Matrix<double> Inv(this->RowCount, this->ColumnCount);

	for (unsigned int i = 0; i < Inv.getRowCount(); ++i) {
		for (unsigned int j = 0; j < Inv.getColumnCount(); ++j) {
			Inv.setElement(i, j, (1 / Det) * pow(-1, i + j) * this->Minor(i + 1, j + 1).Determinant());
		}
	}

	return Inv.Transposition();
}

// Перегрузка оператора присваивания
template <typename T>
Matrix<T> Matrix<T>::operator=(const Matrix& A) {
	if (matrix != nullptr) {
		for (size_t i = 0; i < this->RowCount; ++i) {
			if (matrix[i] != nullptr)
				delete[] matrix[i];
		}
		delete[] matrix;
	}

	RowCount = A.RowCount;
	ColumnCount = A.ColumnCount;

	size_t i = 0;
	try {
		matrix = new T * [RowCount];
		for (; i < RowCount; ++i) {
			matrix[i] = new T[ColumnCount];
		}
	}
	catch (bad_alloc& err) {
		for (size_t j = 0; j != i; ++j) {
			delete[] matrix[i];
		}
		delete[] matrix;

		cout << err.what() << endl;
		throw invalid_argument(err_memory);
	}

	for (size_t i = 0; i < RowCount; ++i) {
		for (size_t j = 0; j < ColumnCount; ++j) {
			matrix[i][j] = A.matrix[i][j];
		}
	}

	return *this;
}

// Перегрузка оператора присваивания с перемещением
template <typename T>
Matrix<T> Matrix<T>::operator=(Matrix&& A) {
	if (matrix != nullptr) {
		for (size_t i = 0; i < this->RowCount; ++i) {
			if (matrix[i] != nullptr)
				delete[] matrix[i];
		}
		delete[] matrix;
	}
	RowCount = A.RowCount;
	ColumnCount = A.ColumnCount;
	matrix = A.matrix;


	A.RowCount = 0;
	A.ColumnCount = 0;
	A.matrix = nullptr;

	return *this;
}

// Перегрузка оператора сложения
template <typename T>
Matrix<T> Matrix<T>::operator+(const Matrix& A) {

	if (RowCount != A.RowCount || ColumnCount != A.ColumnCount) {
		throw invalid_argument(err_dimension);
	}

	Matrix<T> Sum = Matrix<T>(RowCount, ColumnCount);

	for (size_t i = 0; i < Sum.RowCount; ++i) {
		for (size_t j = 0; j < Sum.ColumnCount; ++j) {
			Sum.matrix[i][j] = matrix[i][j] + A.matrix[i][j];
		}
	}

	return Sum;
}

// Перегрузка оператора вычитания
template <typename T>
Matrix<T> Matrix<T>::operator-(const Matrix& A) {
	if (RowCount != A.RowCount || ColumnCount != A.ColumnCount) {
		throw invalid_argument(err_dimension);
	}

	Matrix<T> Sub = Matrix<T>(RowCount, ColumnCount);

	for (size_t i = 0; i < Sub.RowCount; ++i) {
		for (size_t j = 0; j < Sub.ColumnCount; ++j) {
			Sub.matrix[i][j] = matrix[i][j] - A.matrix[i][j];
		}
	}

	return Sub;
}

// Перегрузка оператора умножения
template <typename T>
Matrix<T> Matrix<T>::operator*(const Matrix& A) {
	if (RowCount != A.ColumnCount || ColumnCount != A.RowCount) {
		throw invalid_argument(err_dimension);
	}

	Matrix<T> Product = Matrix<T>(RowCount, A.ColumnCount);

	for (size_t i = 0; i < Product.RowCount; ++i) {
		for (size_t j = 0; j < Product.ColumnCount; ++j) {
			Product.matrix[i][j] = 0;
			for (size_t k = 0; k < ColumnCount; ++k) {
				Product.matrix[i][j] += matrix[i][k] * A.matrix[k][j];
			}
		}
	}

	return Product;
}

// Перегрузка индексации
template <typename T>
const T& Matrix<T>::operator()(unsigned int Row, unsigned int Column) {
	if (Row == 0 || Column == 0 || Row > RowCount || Column > ColumnCount)
		throw invalid_argument(err_invalid_arguments_index);

	return matrix[Row - 1][Column - 1];
}

// Перегрузка оператора выходного потока
template <typename T>
ostream& operator<<(ostream& out, const Matrix<T>& A) {
	out.setf(std::ios::fixed);
	out.precision(3);
	for (size_t i = 0; i < A.RowCount; ++i) {
		for (size_t j = 0; j < A.ColumnCount; ++j) {
			out << A.matrix[i][j] << '\t';
		}
		out << endl;
	}

	return out;
}

// Перегрузка оператора входного потока
template <typename T>
istream& operator>>(istream& in, const Matrix<T>& A) {
	for (size_t i = 0; i < A.RowCount; ++i) {
		for (size_t j = 0; j < A.ColumnCount; ++j) {
			in >> A.matrix[i][j];
		}
	}

	return in;
}

// Перегрузка оператора умножения с явной специализацией
Matrix<double> operator*(Matrix<double> Left, Matrix<int> Right) {
	if (Left.RowCount != Right.ColumnCount || Left.ColumnCount != Right.RowCount) {
		throw invalid_argument(err_dimension);
	}

	Matrix<double> Product = Matrix<double>(Left.RowCount, Right.ColumnCount);

	for (size_t i = 0; i < Product.RowCount; ++i) {
		for (size_t j = 0; j < Product.ColumnCount; ++j) {
			Product.matrix[i][j] = 0;
			for (size_t k = 0; k < Left.ColumnCount; ++k) {
				Product.matrix[i][j] += Left.matrix[i][k] * (double)Right.matrix[k][j];
			}
		}
	}

	return Product;
}

Matrix<double> operator*(Matrix<int> Left, Matrix<double> Right) {
	if (Left.RowCount != Right.ColumnCount || Left.ColumnCount != Right.RowCount) {
		throw invalid_argument(err_dimension);
	}

	Matrix<double> Product = Matrix<double>(Left.RowCount, Right.ColumnCount);

	for (size_t i = 0; i < Product.RowCount; ++i) {
		for (size_t j = 0; j < Product.ColumnCount; ++j) {
			Product.matrix[i][j] = 0;
			for (size_t k = 0; k < Left.ColumnCount; ++k) {
				Product.matrix[i][j] += Left.matrix[i][k] * (double)Right.matrix[k][j];
			}
		}
	}

	return Product;
}
