#include "Matrix.h"

int main() {
	try {
		Matrix A(2, 3), B(2, 3);

		A.Random(10, 100);
		B.Random(10, 100);

		cout << A << endl << B << endl;

		Matrix C(2, 3);
		C = A + B;
		cout << C << endl;
	}
	catch (exception& err) {
		cout << "Exception:" << err.what() << endl;
	}
	return EXIT_SUCCESS;
}