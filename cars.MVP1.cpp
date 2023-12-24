#include <iostream>
#include <ctime>
#include <conio.h>
#include <windows.h>

#define ROW 16 // Строки игрового поля
#define COL 11 // Колонки игрового поля
#define CAR 16 // Количество символов в машинке

using namespace std;

int mot = 0; // Движение машины игрока
int bot = 0;  // Определяет направление движения машины бота
int bot1 = 0;
bool stop = false; // Отвечает за разрешение переключения пути движения бота (переключение происходит 1 раз за верхней границей игрового поля
bool stop1 = false;
int score = 0;
int speed = 50;
bool gameOwer = false;
int level = 1;

int carX[CAR]{ 5,4,5,6,5,4,5,6 }; // Массив машинки игрока
int carY[CAR]{ ROW - 5, ROW - 4, ROW - 4, ROW - 4, ROW - 3, ROW - 2, ROW - 2, ROW - 2 };

int botX[CAR]{ 5,4,5,6,5,4,5,6,5,4,5,6,5,4,5,6 }; // Массив машинки бота
int botY[CAR]{ -3,-2,-2,-2,-1, 0, 0, 0,-11,-10,-10,-10,-9,-8,-8,-8 };

int botX1[CAR]{ 5,4,5,6,5,4,5,6,5,4,5,6,5,4,5,6 }; //Копия для обнуления и возвращения машины бота на нулевое значение
int botY1[CAR]{ -4,-3,-3,-3,-2,-1,-1,-1,-4,-3,-3,-3,-2,-1,-1,-1 };

void RandBot() { // Выбирает рандомно сторону движения машинки бота 
	int a = rand() % 3 + 1; // Создаем временные переменные
	int b = rand() % 3 + 1;

	if (a == b) { // Если значения равны - функция вызывается заного. Всетаки вкорячил рекурсию
		RandBot();
	}
	else {
		bot = a;
		bot1 = b;
	}
}

void Speed() {
	if (score < 10) { // Скорость движение машинки, сделать изменяемой
		level = 1;
		speed = 1;
		Sleep(80);
	}
	else if (score >= 10 && score < 20) {
		level = 2;
		speed = 2;
		Sleep(60);
	}
	else if (score >= 20 && score < 30) {
		level = 3;
		speed = 3;
		Sleep(45);
	}
	else if (score >= 30 && score < 40) {
		level = 4;
		speed = 4;
		Sleep(30);
	}
	else if (score >= 40 && score < 50) {
		level = 5;
		speed = 5;
		Sleep(15);
	}
	else if (score >= 50) {
		level = 6;
		speed = 6;
		Sleep(0);
	}
}

void Draw() { // Отрисовываем все элементы игрового поля
	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COL; j++) {
			if (i == 0 || i == ROW - 1) { // Границы игрового поля по вертикали
				cout << "#";
			}
			else if (j == 0 || j == COL - 1) { // Границы игрового поля по горизонтали
				cout << "#";
			}
			else {
				bool yas = false; // Переменная отвечающая за наличие других обьектов
				for (int k = 0; k < CAR; k++) {
					if (carY[k] == i && carX[k] == j) { // Рисуем машинку игрока
						yas = true;
						cout << "+";
					}
					else if (botY[k] == i && botX[k] == j) { // Рисуем машинку бота
						yas = true;
						cout << "+";
					}

				}
				if (yas == false) { // Рисуем пустоту
					cout << " ";
				}
			}
		}
		cout << endl;
	}
}

void Input() { // Отслеживаем нажатые клавиши игроком
	if (_kbhit()) {
		switch (_getch()) {
		case 'a':
			mot = 1; // Относительно нажатой клавиши - переключается место нахождения машинки
			break;
		case 'd':
			mot = 2;
			break;
		}
	}
}

void AvtoCar() { // Автоматическое смещение машинки бота
	if (stop == false) {
		RandBot();
		switch (bot) {
		case 1:
			for (int i = 0; i < CAR - 8; i++) {
				botX[i] -= 3;
				bot = 0;
				stop = true;
			}
			break;
		case 2:
			for (int i = 0; i < CAR - 8; i++) {
				botX[i] += 3;
				bot = 0;
				stop = true;
			}
			break;
		}
	}
	if (stop1 == false) {
		switch (bot1) {
		case 1:
			for (int i = 8; i < CAR; i++) {
				botX[i] -= 3;
				bot1 = 0;
				stop1 = true;
			}
			break;
		case 2:
			for (int i = 8; i < CAR; i++) {
				botX[i] += 3;
				bot1 = 0;
				stop1 = true;
			}
			break;
		}
	}
}

void Repeat() {

	for (int i = 0; i < CAR; i++) { // Движение машинки вниз 
		botY[i] ++;
	}
	for (int i = 0; i < CAR - 8; i++) { // Если машинка проехала поле, возвращаем её наместо, обновляя её массив и разрешаем новое переключение
		if (botY[i] == 16) {
			for (int j = 0; j < CAR - 8; j++) {
				if (j == 7) {
					stop = false;
				}
				botY[j] = botY1[j];
				botX[j] = botX1[j];
			}
			score++;
		}
	}

	for (int i = 8; i < CAR; i++) { // Если машинка проехала поле, возвращаем её наместо, обновляя её массив и разрешаем новое переключение
		if (botY[i] == 16) {
			for (int j = 8; j < CAR; j++) {
				/*if (i == 15) {
					stop1 = false;
				}*/
				botY[j] = botY1[j];
				botX[j] = botX1[j];
			}
			score++;
		}
	}
}

void Logik() { // Логика игры при управлении игрока
	int position = 0;
	if (carX[0] == 5) { //Определяем позицию машинки игрока, чтобы исключить переключение за границу поля
		position = 0;
	}
	else if (carX[0] == 2) {
		position = 1;
	}
	else if (carX[0] == 8) {
		position = 2;
	}

	switch (mot) { // Переключаем позицию машинки игрока
	case 1:
		for (int i = 0; i < CAR; i++) {
			if (position != 1) { // Условие запрещения переключения позиции машинки за пределы игрового поля
				carX[i] -= 3;
				mot = 0; // Запрещаем дальнейшее движение в сторону, после переключения 
			}
		}
		break;
	case 2:
		for (int i = 0; i < CAR; i++) {
			if (position != 2) {
				carX[i] += 3;
				mot = 0;
			}
		}
		break;
	}

}

int main() {
	setlocale(LC_ALL, "Russian");
	srand(time(NULL));

	while (!gameOwer) {
		system("cls");
		cout << "Score: " << score << " Level: " << level << " Speed: " << speed << endl;

		Draw();
		Speed();
		Input();
		AvtoCar();
		Repeat();
		Logik();
		

		if ((carX[0] == botX[6] && carY[0] == botY[6]) || (carX[0] == botX[14] && carY[0] == botY[14])) {
			gameOwer = true;
		}
		
	}

	cout << "\nGame Ower! " << "Score: " << score << endl;
	system("pause");
	return 0;
}