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
string err_squeeze = "Input Arguments are greater than matrix dimensions (squeeze function)";

template <typename T = int>
class Matrix
{
private:
	size_t RowCount;  // Number of rows
	size_t ColumnCount; // Number of columns
	T **matrix;  // Pointer to element of matrix

public:
	Matrix(size_t RowCount = 1, size_t ColumnCount = 1);  // Constructor
	Matrix(const Matrix<T>&); // Copy constructor
	Matrix(Matrix<T>&&);  // Move constructor
	~Matrix();  // Destructor

	const size_t getRowCount() { return RowCount; }  // Get methods
	const size_t getColumnCount() { return ColumnCount; }

	void setElement(unsigned int, unsigned int, T);  // Changing of element

	void fillRandom(int, int);  // Filling the matrix with random values
	const Matrix<T> Transposition(); // Transposition of matrix
	Matrix<T> Minor(unsigned int, unsigned int);  // Minor of matrix
	const T Determinant(); // Determinant of matrix
	Matrix<double> Inverse(); // Calculating inverse matrix
	static void to_square_size(Matrix<T>&, Matrix<T>&); // Addition to square matrices нулями
	Matrix<T> squeeze(size_t, size_t); // Compress to the desired size

	//overload of operators
	Matrix<T> operator=(const Matrix<T>&); // Assignment
	Matrix<T> operator=(Matrix<T>&&);  // Assignment with moving
	Matrix<T> operator+(const Matrix<T>&); // Addition
	Matrix<T> operator-(const Matrix<T>&); // Substraction
	Matrix<T> operator*(const Matrix<T>&); // Multiplication
	const T &operator()(unsigned int, unsigned int); // Indexing

	template <typename T>
	friend ostream& operator<<(ostream&, const Matrix<T>&); // Output stream
	template <typename T>
	friend istream& operator>>(istream&, const Matrix<T>&); // Input stream

	friend Matrix<double> operator*(const Matrix<double>, const Matrix<int>);  // template specialization
	friend Matrix<double> operator*(const Matrix<int>, const Matrix<double>);
};

// Constructor
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

// Copy constructor
template <typename T>
Matrix<T>::Matrix(const Matrix<T>& A)
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

// Move constructor
template <typename T>
Matrix<T>::Matrix(Matrix<T>&& A) :
	RowCount(A.RowCount), ColumnCount(A.ColumnCount), matrix(A.matrix) {
	A.RowCount = 0;
	A.ColumnCount = 0;
	A.matrix = nullptr;
}

// Destructor
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

// Changing of one element
template<typename T>
void Matrix<T>::setElement(unsigned int i, unsigned int j, T value){
	if (i > RowCount || j > ColumnCount)
		throw invalid_argument(err_arguments_set_element);

	matrix[i][j] = value;
}

// Filling matrix with random numbers
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

// Transposition of matrix
template <typename T>
const Matrix<T> Matrix<T>::Transposition() {
	Matrix<T> Tran = Matrix<T>(ColumnCount, RowCount);

	for (size_t i = 0; i < RowCount; ++i) {
		for (size_t j = 0; j < ColumnCount; ++j) {
			Tran.matrix[j][i] = matrix[i][j];
		}
	}
	return Tran;
}

// Minor of matrix
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

// Calculating determinant of matrix
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

// Calculating inverse matrix
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

template<typename T>
void Matrix<T>::to_square_size(Matrix<T>& A, Matrix<T>& B){
	size_t n = max(max(A.RowCount, A.ColumnCount), max(B.RowCount, B.ColumnCount));
	if (n % 2 != 0) ++n;

	Matrix<T> Atemp(n, n), Btemp(n, n);
	for (size_t i = 0; i < n; ++i) {
		for (size_t j = 0; j < n; ++j) {
			if (i > A.RowCount - 1 || j > A.ColumnCount - 1)
				Atemp.matrix[i][j] = 0;
			else
				Atemp.matrix[i][j] = A.matrix[i][j];
			if (i > B.RowCount - 1 || j > B.ColumnCount - 1)
				Btemp.matrix[i][j] = 0;
			else
				Btemp.matrix[i][j] = B.matrix[i][j];
		}
	}
	A = Atemp;
	B = Btemp;
}

template<typename T>
Matrix<T> Matrix<T>::squeeze(size_t x, size_t y){
	if (x > this->RowCount || y > this->ColumnCount)
		throw invalid_argument(err_squeeze);

	Matrix<T> Temp(x, y);
	for (size_t i = 0; i < x; ++i) {
		for (size_t j = 0; j < y; ++j) {
			Temp.matrix[i][j] = this->matrix[i][j];
		}
	}

	return Temp;
}

// Overload of assignment operator
template <typename T>
Matrix<T> Matrix<T>::operator=(const Matrix<T>& A) {
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

// Overload of assignment operator with moving
template <typename T>
Matrix<T> Matrix<T>::operator=(Matrix<T>&& A) {
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

// Overload of addition operator
template <typename T>
Matrix<T> Matrix<T>::operator+(const Matrix<T>& A) {

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

// Overload of substraction operator
template <typename T>
Matrix<T> Matrix<T>::operator-(const Matrix<T>& A) {
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

// Overload of multiplication operator
template <typename T>
Matrix<T> Matrix<T>::operator*(const Matrix<T>& A) {
	if (this->RowCount != Right.ColumnCount || this->ColumnCount != Right.RowCount)
		throw invalid_argument(err_dimension);

	// Base case
	if (this->ColumnCount == 1 && this->RowCount == 1 &&
		Right.ColumnCount == 1 && Right.RowCount == 1) {
		Matrix<T> XY(1, 1);
		XY.matrix[0][0] = this->matrix[0][0] * Right.matrix[0][0];
		return XY;
	}

	// We complement the matrices to even square matrices
	Matrix<T> X = *this, Y = Right;
	to_square_size(X, Y);
	size_t n = X.RowCount; // Size of matrices
	// Required variables
	Matrix<T> A(n / 2, n / 2), B(n / 2, n / 2), C(n / 2, n / 2), D(n / 2, n / 2),
		E(n / 2, n / 2), F(n / 2, n / 2), G(n / 2, n / 2), H(n / 2, n / 2),
		P1(n / 2, n / 2), P2(n / 2, n / 2), P3(n / 2, n / 2), P4(n / 2, n / 2),
		P5(n / 2, n / 2), P6(n / 2, n / 2), P7(n / 2, n / 2);
	
	for (size_t i = 0; i < n / 2; ++i) {
		for (size_t j = 0; j < n / 2; ++j) {
			A.matrix[i][j] = X.matrix[i][j];
			B.matrix[i][j] = X.matrix[i][j + n/2];
			C.matrix[i][j] = X.matrix[i + n/2][j];
			D.matrix[i][j] = X.matrix[i + n/2][j + n/2];
			E.matrix[i][j] = Y.matrix[i][j];
			F.matrix[i][j] = Y.matrix[i][j + n/2];
			G.matrix[i][j] = Y.matrix[i + n/2][j];
			H.matrix[i][j] = Y.matrix[i + n/2][j + n/2];
		}
	}
	// Recursively multiply
	P1 = A * (F - H);
	P2 = (A + B) * H;
	P3 = (C + D) * E;
	P4 = D * (G - E);
	P5 = (A + D) * (E + H);
	P6 = (B - D) * (G + H);
	P7 = (A - C) * (E + F);

	Matrix<T> XY11(n / 2, n / 2), XY12(n / 2, n / 2), XY21(n / 2, n / 2), XY22(n / 2, n / 2);

	XY11 = P5 + P4 - P2 + P6;
	XY12 = P1 + P2;
	XY21 = P3 + P4;
	XY22 = P1 + P5 - P3 - P7;
	Matrix<T> XY(n, n);
	// Filling in the final matrix
	for (size_t i = 0; i < n/2; ++i) {
		for (size_t j = 0; j < n/2; ++j) {
			XY.matrix[i][j] = XY11.matrix[i][j];
		}
	}
	for (size_t i = 0; i < n/2; ++i) {
		for (size_t j = n/2; j < n; ++j) {
			XY.matrix[i][j] = XY12.matrix[i][j - n/2];
		}
	}
	for (size_t i = n/2; i < n; ++i) {
		for (size_t j = 0; j < n/2; ++j) {
			XY.matrix[i][j] = XY21.matrix[i - n/2][j];
		}
	}
	for (size_t i = n/2; i < n; ++i) {
		for (size_t j = n/2; j < n; ++j) {
			XY.matrix[i][j] = XY22.matrix[i-n/2][j-n/2];
		}
	}
	// Deleting null rows and columns
	return XY.squeeze(this->RowCount, Right.ColumnCount);
}

// Overload of indexing
template <typename T>
const T& Matrix<T>::operator()(unsigned int Row, unsigned int Column) {
	if (Row == 0 || Column == 0 || Row > RowCount || Column > ColumnCount)
		throw invalid_argument(err_invalid_arguments_index);

	return matrix[Row - 1][Column - 1];
}

// Overload of output stream
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

// Overload of input stream
template <typename T>
istream& operator>>(istream& in, const Matrix<T>& A) {
	for (size_t i = 0; i < A.RowCount; ++i) {
		for (size_t j = 0; j < A.ColumnCount; ++j) {
			in >> A.matrix[i][j];
		}
	}

	return in;
}

// Template specialization for multiplication Matrix<double> and Matrix<int>
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

// Template specialization for multiplication Matrix<int> and Matrix<double>
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
