#include "Matrix.h"

int main() {
	try {
		Matrix A(3, 3), B(3, 3);  //������ 2 ������������� ������� �������� 3 �� 3

		A.fillRandom(0, 9); //��������� �� ���������� ������� �� 0 �� 9
		B.fillRandom(0, 9);

		//������� �� � �������
		cout << "Matrix A:" << endl << A << endl;
		cout << "Matrix B:" << endl << B << endl;

		//����������
		cout << "A + B:" << endl;
		cout << A + B << endl;

		//��������
		cout << "A - B:" << endl;
		cout << A - B << endl;
		
		//��������
		cout << "A * B:" << endl;
		cout << A * B << endl;

		//�������������
		cout << "Transposition A:" << endl;
		cout << A.Transposition() << endl;

		//��������� ������������
		cout << "Determinant of A:" << endl;
		cout << A.Determinant() << endl; 

		//��������� �������� �������
		cout << "1/A :" << endl;
		cout << A.Inverse() << endl;

		//�������� �������� �������
		cout << "A * 1/A :" << endl;
		cout << A * A.Inverse() << endl;

	}
	catch (exception& err) { // ����� ����������
		cout << "Exception: " << err.what() << endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}