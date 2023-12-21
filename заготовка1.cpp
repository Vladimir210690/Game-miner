#include <iostream>
#include <ctime>

#define ROW 20 // Константа строк игрового поля
#define COL 40 // Константа колонок игрового поля
#define SIZE 100 // Константа максимального размера массива для бомб 

using namespace std;

void Draw(int arr[], int brr[], int a, int b) { // Функция отрисовки игрового поля
	for (int i = 0; i < b; i++) { // Отрисовывает верхнюю границу
		cout << "#";
	}
	cout << endl;

	for (int i = 0; i < a; i++) { // Отрисовка центра и всех деталей
		for (int j = 0; j < b; j++) {
			if (j == 0 || j == b - 1) {
				cout << "#";
			}
			
			else { // Отрисовка бомб и пустоты
				bool yas = false; // Проверяет наличие бомбы
				for (int k = 0; k < SIZE; k++) {
					if (arr[k] == i && brr[k] == j) {
						yas = true; // Если бомбы есть рисуем её
						cout << "*";
					}
				}
				if (yas == false) { // Если бомбы нет рисуем пустоту
					cout << " ";
				}
			}
		}
		cout << endl;
	}

	for (int i = 0; i < b; i++) { // Отрисовка нижней границы
		cout << "#";
	}
	cout << endl;
}

void Bomb(int arr[], int brr[], int totalbomb, int a) { // Функция генерирующая координаты бомб

	for (int i = 0; i < a; i++) {
		arr[i] = rand() % ROW;
		brr[i] = rand() % COL;
		totalbomb--; // Уменьшием количество бомб после каждой генерации
		if (totalbomb == 0)
			break; // Выходим из цикла, когда количество бомб заканчивается
	}
}

long main() {
	setlocale(LC_ALL, "Russian");
	srand(time(NULL));
	
	int totalbomb = 0; // Количество бомб на карте
	cout << "How many to do bomb: ";
	cin >> totalbomb;

	int bombX[SIZE]{}; // Хранит координаты бомбы по x
	int bombY[SIZE]{}; // Хранит координаты бомбы по y

	while (true) {
		system("cls");

		Bomb(bombX, bombY, totalbomb, SIZE);
		Draw(bombX, bombY, ROW, COL);
		
		system("pause");
	}
	return 0;
}