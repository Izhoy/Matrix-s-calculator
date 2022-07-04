#include "Matrix.h"

const char *err_dimension = "Dimensions are different";
const char *err_memory = "Not enough memory";

Matrix::Matrix(int Xdimension, int Ydimension) {
	if (Xdimension <= 0 || Ydimension <= 0) {
		this->Xdimension = 1;
		this->Ydimension = 1;
	}
	else {
		this->Xdimension = Xdimension;
		this->Ydimension = Ydimension;
	}

	try {
		element = new int* [this->Xdimension];
		for (int i = 0; i < this->Xdimension; ++i) {
			element[i] = new int[this->Ydimension];
		}
	} catch (bad_alloc& err) {
		err.what();
		throw invalid_argument(err_memory);
	}

	for (int i = 0; i < this->Xdimension; ++i) {
		for (int j = 0; j < this->Ydimension; ++j) {
			element[i][j] = 0;
		}
	}
}

Matrix::Matrix(const Matrix& A) {

	Xdimension = A.Xdimension;
	Ydimension = A.Ydimension;

	try{
		element = new int* [Xdimension];
		for (int i = 0; i < Xdimension; ++i) {
			element[i] = new int[Ydimension];
		}
	}
	catch (bad_alloc& err) {
		err.what();
		throw invalid_argument(err_memory);
	}

	for (int i = 0; i < Xdimension; ++i) {
		for (int j = 0; j < Ydimension; ++j) {
			element[i][j] = A.element[i][j];
		}
	}
	
}

Matrix::~Matrix() {
	if (element != nullptr) {
		for (int i = 0; i < this->Xdimension; ++i) {
			if (element[i] != nullptr)
				delete[] element[i];
		}
		delete[] element;
	}
}

void Matrix::Random(int min, int max) {
	system_clock::time_point now = system_clock::now();
	chrono::nanoseconds d = now.time_since_epoch();
	chrono::microseconds microsec = chrono::duration_cast<chrono::microseconds>(d);
	srand(microsec.count());

	for (int i = 0; i < Xdimension; ++i) {
		for (int j = 0; j < Ydimension; ++j) {
			element[i][j] = min + (rand() % (max - min) + 1);
		}
	}
}

Matrix Matrix::Transposition(){
	Matrix T(Ydimension, Xdimension);

	for (int i = 0; i < Xdimension; ++i) {
		for (int j = 0; j < Ydimension; ++j) {
			T.element[j][i] = element[i][j];
		}
	}
	return T;
}

int Matrix::Determinant()
{
	return 0;
}

Matrix Matrix::operator=(const Matrix &A) {
	if (element != nullptr) {
		for (int i = 0; i < this->Xdimension; ++i) {
			if (element[i] != nullptr)
				delete[] element[i];
		}
		delete[] element;
	}

	Xdimension = A.Xdimension;
	Ydimension = A.Ydimension;

	try {
		element = new int* [Xdimension];
		for (int i = 0; i < Xdimension; ++i) {
			element[i] = new int[Ydimension];
		}
	}catch (bad_alloc& err) {
		err.what();
		throw invalid_argument(err_memory);
	}
		
	for (int i = 0; i < Xdimension; ++i) {
		for (int j = 0; j < Ydimension; ++j) {
			element[i][j] = A.element[i][j];
		}
	}
	
	return *this;
}

Matrix Matrix::operator+(const Matrix &A){

	if (Xdimension != A.Xdimension || Ydimension != A.Ydimension) {
		throw invalid_argument(err_dimension);
	}

	Matrix Sum(Xdimension, Ydimension);

	for (int i = 0; i < Sum.Xdimension; ++i) {
		for (int j = 0; j < Sum.Ydimension; ++j) {
			Sum.element[i][j] = element[i][j] + A.element[i][j];
		}
	}

	return Sum;
}

Matrix Matrix::operator-(const Matrix &A){
	if (Xdimension != A.Xdimension || Ydimension != A.Ydimension) {
		throw invalid_argument(err_dimension);
	}

	Matrix Sub(Xdimension, Ydimension);

	for (int i = 0; i < Sub.Xdimension; ++i) {
		for (int j = 0; j < Sub.Ydimension; ++j) {
			Sub.element[i][j] = element[i][j] - A.element[i][j];
		}
	}

	return Sub;
}

Matrix Matrix::operator*(const Matrix &A){
	if (Xdimension != A.Ydimension || Ydimension != A.Xdimension) {
		throw invalid_argument(err_dimension);
	}

	Matrix Production(Xdimension, A.Ydimension);

	for (int i = 0; i < Production.Xdimension; ++i) {
		for (int j = 0; j < Production.Ydimension; ++j) {
			for (int k = 0; k < Ydimension; ++k) {
				Production.element[i][j] += element[i][k] * A.element[k][j];
			}
		}
	}

	return Production;
}

ostream& operator<<(ostream& out, Matrix A) {
	for (int i = 0; i < A.Xdimension; ++i) {
		for (int j = 0; j < A.Ydimension; ++j) {
			out << A.element[i][j] << '\t';
		}
		out << endl;
	}

	return out;
}

istream& operator>>(istream& in, Matrix A) {
	for (int i = 0; i < A.Xdimension; ++i) {
		for (int j = 0; j < A.Ydimension; ++j) {
			in >> A.element[i][j];
		}
	}

	return in;
}