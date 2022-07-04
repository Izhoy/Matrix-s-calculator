#include "Matrix.h"

int main() {
	try {
		Matrix A(3, 3), B(3, 3);

		A.Random(0, 9);
		B.Random(0, 9);

		cout << "Matrix A:" << endl << A << endl;
		cout << "Matrix B:" << endl << B << endl;

		cout << "A + B:" << endl;
		cout << A + B << endl;

		cout << "A - B:" << endl;
		cout << A - B << endl;

		cout << "A * B:" << endl;
		cout << A * B << endl;

		cout << "Transponation A:" << endl;
		cout << A.Transpotion() << endl;
	}
	catch (exception& err) {
		cout << "Exception: " << err.what() << endl;
	}
	return EXIT_SUCCESS;
}