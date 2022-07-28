#include "Matrix.h"

int main() {
	try {
		Matrix A(3, 3), B(3, 3);  //Создаём 2 целочисленные матрицы размером 3 на 3

		A.fillRandom(0, 9); //Заполняем их случайными числами от 0 до 9
		B.fillRandom(0, 9);

		//Выводим их в консоль
		cout << "Matrix A:" << endl << A << endl;
		cout << "Matrix B:" << endl << B << endl;

		//Складываем
		cout << "A + B:" << endl;
		cout << A + B << endl;

		//Вычитаем
		cout << "A - B:" << endl;
		cout << A - B << endl;
		
		//Умножаем
		cout << "A * B:" << endl;
		cout << A * B << endl;

		//Транспонируем
		cout << "Transposition A:" << endl;
		cout << A.Transposition() << endl;

		//Вычисляем определитель
		cout << "Determinant of A:" << endl;
		cout << A.Determinant() << endl; 

		//Вычисляем обратную матрицу
		cout << "1/A :" << endl;
		cout << A.Inverse() << endl;

		//Проверка обратной матрицы
		cout << "A * 1/A :" << endl;
		cout << A * A.Inverse() << endl;

	}
	catch (exception& err) { // Вывод исключений
		cout << "Exception: " << err.what() << endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}