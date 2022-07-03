#include <iostream>
#include "Matrix.h"

using namespace std;

int main() {
	Matrix A(2, 3), B(2, 3);

	A.Random(10, 100);
	B.Random(10, 100);

	cout << A << endl << B << endl;
	Matrix C = A + B;
	cout << C << endl;
	return EXIT_SUCCESS;
}