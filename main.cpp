#include "Matrix.h"

int main() {
	try {
		Matrix A(3, 3), B(3, 3);  //Create matrices (size 3 by 3)

		A.Random(0, 9); //Fill with random numbers from 0 to 9
		B.Random(0, 9);

		//Show matrix A and Matrix B
		cout << "Matrix A:" << endl << A << endl;
		cout << "Matrix B:" << endl << B << endl;

		//Sum of A and B
		cout << "A + B:" << endl;
		cout << A + B << endl;

		//Substraction A and B
		cout << "A - B:" << endl;
		cout << A - B << endl;

		//Production A and B
		cout << "A * B:" << endl;
		cout << A * B << endl;

		//Transposition of A
		cout << "Transposition A:" << endl;
		cout << A.Transposition() << endl;

		//Determinant of A
		cout << "Determinant" << endl;
		cout << A.Determinant() << endl;
	}
	catch (exception& err) { // Show exceptions
		cout << "Exception: " << err.what() << endl;
	}
	return EXIT_SUCCESS;
}
