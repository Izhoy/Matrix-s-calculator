#include "Matrix.h"

const char *err_arguments = "Matrix dimension must be greater than� zero (Matrix Constructor)";
const char *err_dimension = "Dimensions are different ('+', '-' or '*' overload)";
const char *err_memory = "Not enough memory";
const char *err_square_matrix = "Matrix is not square (Determinant function)";
const char *err_invalid_arguments = "Input atguments are not acceptable (Minor funstion)";

// ����������� (�� ��������� ��������� ����� 1)
Matrix::Matrix(int StringCount, int ColumnCount) {
	if (StringCount <= 0 || ColumnCount <= 0) {
		throw(invalid_argument(err_arguments));
	}
	else {
		this->StringCount = StringCount;
		this->ColumnCount = ColumnCount;
	}

	try {
		element = new int* [this->StringCount];
		for (int i = 0; i < this->StringCount; ++i) {
			element[i] = new int[this->ColumnCount];
		}
	} catch (bad_alloc& err) {
		cout << err.what() << endl;
		throw invalid_argument(err_memory);
	}
	// ��������� ������� ��������� ������
	for (int i = 0; i < this->StringCount; ++i) {
		for (int j = 0; j < this->ColumnCount; ++j) {
			element[i][j] = 0;
		}
	}
}

// ����������� �����������
Matrix::Matrix(const Matrix& A) {

	StringCount = A.StringCount;
	ColumnCount = A.ColumnCount;

	try{
		element = new int* [StringCount];
		for (int i = 0; i < StringCount; ++i) {
			element[i] = new int[ColumnCount];
		}
	}
	catch (bad_alloc& err) {
		cout << err.what() << endl;
		throw invalid_argument(err_memory);
	}

	for (int i = 0; i < StringCount; ++i) {
		for (int j = 0; j < ColumnCount; ++j) {
			element[i][j] = A.element[i][j];
		}
	}
	
}

// ����������
Matrix::~Matrix() {
	if (element != nullptr) {
		for (int i = 0; i < this->StringCount; ++i) {
			if (element[i] != nullptr)
				delete[] element[i];
		}
		delete[] element;
	}
}

// ����� ���������� ������� ���������� �������
void Matrix::Random(int min, int max) {
	/* ��� "srand(time(0);"
	�� �������� ������������ ��� ������ ������� �� ���� ������ ���������,
	������� ������ ��������� ������� srand ��������� ����� ����������� � �������������*/

	system_clock::time_point now = system_clock::now();
	chrono::nanoseconds d = now.time_since_epoch();
	chrono::microseconds microsec = chrono::duration_cast<chrono::microseconds>(d);
	srand((unsigned int)microsec.count());

	for (int i = 0; i < StringCount; ++i) {
		for (int j = 0; j < ColumnCount; ++j) {
			element[i][j] = min + (rand() % (max - min) + 1);
		}
	}
}

// ����� ���������������� �������
Matrix& Matrix::Transposition(){
	Matrix *T = new Matrix(ColumnCount, StringCount);

	for (int i = 0; i < StringCount; ++i) {
		for (int j = 0; j < ColumnCount; ++j) {
			T->element[j][i] = element[i][j];
		}
	}
	return *T;
}

// ����� ��������� ������ (��������� ��� �������� ������������)
Matrix& Matrix::Minor(unsigned int x, unsigned int y)
{
	if (x == 0 || y == 0 || x > (unsigned int)StringCount || y > (unsigned int)ColumnCount) 
		throw(invalid_argument(err_invalid_arguments));

	Matrix *M = new Matrix(StringCount - 1, ColumnCount - 1);

	int i = 0, j = 0, n = 0, m = 0;

	while (i < StringCount || n < M->StringCount) {
		if (i == x - 1) ++i;  // ���� ���������� �� ������, ������� ���������� ��������, �� ���������� �
		if (i == StringCount) break;
		while (j < ColumnCount || m < M->ColumnCount) {
			if (j == y - 1) ++j; // ���� ���������� �� �������, ������� ���������� ��������, �� ���������� ���
			M->element[n][m] = element[i][j];
			++j; ++m;
		}
		j = 0; m = 0;
		++i; ++n;
	}

	return *M;
}

// ����� �������� ������������
int Matrix::Determinant()
{
	if (StringCount != ColumnCount) throw(invalid_argument(err_square_matrix));

	int Det = 0;

	if (StringCount == 2) {
		Det = element[0][0] * element[1][1] - element[0][1] * element[1][0];
		return Det;
	}

	for (int i = 0; i < StringCount; ++i) {
		Det += (int)pow(-1, (i + 1) + 1) * element[0][i] * Minor(1, i + 1).Determinant();
	}

	return Det;
}

// ���������� ��������� ������������
Matrix& Matrix::operator=(const Matrix &A) {
	if (element != nullptr) {
		for (int i = 0; i < this->StringCount; ++i) {
			if (element[i] != nullptr)
				delete[] element[i];
		}
		delete[] element;
	}

	StringCount = A.StringCount;
	ColumnCount = A.ColumnCount;

	try {
		element = new int* [StringCount];
		for (int i = 0; i < StringCount; ++i) {
			element[i] = new int[ColumnCount];
		}
	}catch (bad_alloc& err) {
		cout << err.what() << endl;
		throw invalid_argument(err_memory);
	}
		
	for (int i = 0; i < StringCount; ++i) {
		for (int j = 0; j < ColumnCount; ++j) {
			element[i][j] = A.element[i][j];
		}
	}
	
	return *this;
}

// ���������� ��������� ��������
Matrix& Matrix::operator+(const Matrix &A){

	if (StringCount != A.StringCount || ColumnCount != A.ColumnCount) {
		throw invalid_argument(err_dimension);
	}

	Matrix *Sum = new Matrix(StringCount, ColumnCount);

	for (int i = 0; i < Sum->StringCount; ++i) {
		for (int j = 0; j < Sum->ColumnCount; ++j) {
			Sum->element[i][j] = element[i][j] + A.element[i][j];
		}
	}

	return *Sum;
}

// ���������� ��������� ���������
Matrix& Matrix::operator-(const Matrix &A){
	if (StringCount != A.StringCount || ColumnCount != A.ColumnCount) {
		throw invalid_argument(err_dimension);
	}

	Matrix *Sub = new Matrix(StringCount, ColumnCount);

	for (int i = 0; i < Sub->StringCount; ++i) {
		for (int j = 0; j < Sub->ColumnCount; ++j) {
			Sub->element[i][j] = element[i][j] - A.element[i][j];
		}
	}

	return *Sub;
}

// ���������� ��������� ���������
Matrix& Matrix::operator*(const Matrix &A){
	if (StringCount != A.ColumnCount || ColumnCount != A.StringCount) {
		throw invalid_argument(err_dimension);
	}

	Matrix *Product = new Matrix(StringCount, A.ColumnCount);

	for (int i = 0; i < Product->StringCount; ++i) {
		for (int j = 0; j < Product->ColumnCount; ++j) {
			for (int k = 0; k < ColumnCount; ++k) {
				Product->element[i][j] += element[i][k] * A.element[k][j];
			}
		}
	}

	return *Product;
}

// ���������� ��������� ��������� ������
ostream& operator<<(ostream& out, Matrix &A) {
	for (int i = 0; i < A.StringCount; ++i) {
		for (int j = 0; j < A.ColumnCount; ++j) {
			out << A.element[i][j] << '\t';
		}
		out << endl;
	}

	return out;
}

// ���������� ��������� �������� ������
istream& operator>>(istream& in, Matrix &A) {
	for (int i = 0; i < A.StringCount; ++i) {
		for (int j = 0; j < A.ColumnCount; ++j) {
			in >> A.element[i][j];
		}
	}

	return in;
}