#include "Matrix.h"

const char *err_dimension = "Dimensions are different";
const char* err_memory = "Not enough memory";

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

		for (int i = 0; i < this->Xdimension; ++i) {
			for (int j = 0; j < this->Ydimension; ++j) {
				element[i][j] = 0;
			}
		}
	}
	catch (bad_alloc& err) {
		err.what();
		throw invalid_argument(err_memory);
	}
}

Matrix::Matrix(const Matrix& A) {
	if (element != nullptr) {
		for (int i = 0; i < this->Xdimension; ++i) {
			if(element[i] != nullptr)
			delete[] element[i];
		}
		delete[] element;
	}

	this->Xdimension = A.Xdimension;
	this->Ydimension = A.Ydimension;

	try{
		this->element = new int* [this->Xdimension];
		for (int i = 0; i < this->Xdimension; ++i) {
			this->element[i] = new int[this->Ydimension];
		}

		for (int i = 0; i < this->Xdimension; ++i) {
			for (int j = 0; j < this->Ydimension; ++j) {
				this->element[i][j] = A.element[i][j];
			}
	}
	}catch (bad_alloc& err) {
		err.what();
		throw invalid_argument(err_memory);
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
	cout << "Destruction" << endl;
}

void Matrix::Random(int min, int max) {
	system_clock::time_point now = system_clock::now();
	chrono::nanoseconds d = now.time_since_epoch();
	chrono::microseconds microsec = chrono::duration_cast<chrono::microseconds>(d);
	srand(microsec.count());

	for (int i = 0; i < this->Xdimension; ++i) {
		for (int j = 0; j < this->Ydimension; ++j) {
			this->element[i][j] = min + (rand() % (max - min) + 1);
		}
	}
}

Matrix Matrix::operator=(const Matrix &A) {
	if (element != nullptr) {
		for (int i = 0; i < this->Xdimension; ++i) {
			if (element[i] != nullptr)
				delete[] element[i];
		}
		delete[] element;
	}

	this->Xdimension = A.Xdimension;
	this->Ydimension = A.Ydimension;

	try {
		element = new int* [this->Xdimension];
		for (int i = 0; i < this->Xdimension; ++i) {
			element[i] = new int[this->Ydimension];
		}

		for (int i = 0; i < this->Xdimension; ++i) {
			for (int j = 0; j < this->Ydimension; ++j) {
				this->element[i][j] = A.element[i][j];
			}
		}
	}
	catch (bad_alloc& err) {
			err.what();
			throw invalid_argument(err_memory);
	}

	return *this;
}

Matrix Matrix::operator+(const Matrix &A)
{
	if (this->Xdimension != A.Xdimension || this->Ydimension != A.Ydimension) {
		throw invalid_argument(err_dimension);
	}

	Matrix Sum(this->Xdimension, this->Ydimension);

	for (int i = 0; i < Sum.Xdimension; ++i) {
		for (int j = 0; j < Sum.Ydimension; ++j) {
			Sum.element[i][j] = this->element[i][j] + A.element[i][j];
		}
	}

	return Sum;
}

ostream& operator<<(ostream& out, Matrix& A) {
	for (int i = 0; i < A.Xdimension; ++i) {
		for (int j = 0; j < A.Ydimension; ++j) {
			out << A.element[i][j] << '\t';
		}
		out << endl;
	}

	return out;
}

istream& operator>>(istream& in, Matrix& A) {
	for (int i = 0; i < A.Xdimension; ++i) {
		for (int j = 0; j < A.Ydimension; ++j) {
			in >> A.element[i][j];
		}
	}

	return in;
}