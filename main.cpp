#include "Matrix.h"

int main() {
	try {
		Matrix A(3, 3), B(3, 3);  // Creating two integer matrices 3 by 3

		A.fillRandom(0, 9); // Fill in with random numbers from 0 to 9
		B.fillRandom(0, 9);

		// Output of matrices to the console
		cout << "Matrix A:" << endl << A << endl;
		cout << "Matrix B:" << endl << B << endl;

		//Sum
		cout << "A + B:" << endl;
		cout << A + B << endl;

		//Substraction
		cout << "A - B:" << endl;
		cout << A - B << endl;
		
		//Production
		cout << "A * B:" << endl;
		cout << A * B << endl;

		//Transpotion of matrix A
		cout << "Transposition A:" << endl;
		cout << A.Transposition() << endl;

		//Calculating the determinant
		cout << "Determinant of A:" << endl;
		cout << A.Determinant() << endl; 

		//Calculating the inverse matrix
		cout << "1/A :" << endl;
		cout << A.Inverse() << endl;

		//Checking of inverse matrix
		cout << "A * 1/A :" << endl;
		cout << A * A.Inverse() << endl;

	}
	catch (exception& err) { //Exception handling
		cout << "Exception: " << err.what() << endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
