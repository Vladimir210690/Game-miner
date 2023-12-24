#include <iostream>
#include <ctime>
#include <conio.h>
#include <windows.h>

#define ROW 15 // Строки игрового поля
#define COL 11 // Колонки игрового поля
#define CAR 8 // Количество символов в машинке

using namespace std;

int mot = 0; // Движение машины игрока
int bot = 0;  // Определяет направление движения машины бота
bool stop = false; // Отвечает за разрешение переключения пути движения бота (переключение происходит 1 раз за верхней границей игрового поля
int score = 0;
int speed = 50;
bool gameOwer = false;
int level = 1;

int carX[CAR]{ 5,4,5,6,5,4,5,6 }; // Массив машинки игрока
int carY[CAR]{ 10,11,11,11,12,13,13,13 };

int botX[CAR]{ 5,4,5,6,5,4,5,6 }; // Массив машинки бота
int botY[CAR]{ -4,-3,-3,-3,-2,-1,-1,-1 };

int botX1[CAR]{ 5,4,5,6,5,4,5,6 }; //Копия для обнуления и возвращения машины бота на нулевое значение
int botY1[CAR]{ -4,-3,-3,-3,-2,-1,-1,-1 };

int RandBot() { // Выбирает рандомно сторону движения машинки бота
	bot = rand() % 3 + 1;
	return bot;
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
void AvtoCar() { // Автоматическое движение машинки бота

	if (stop == false) { // Если переключение разрешено отслеживаем рандомное направление
		switch (RandBot()) {
		case 1:
			for (int i = 0; i < CAR; i++) {
				botX[i] -= 3;
				stop = true; // После переключения стороны запрещаем дальнейшие переключения по ходу движения
			}
			break;
		case 2:
			for (int i = 0; i < CAR; i++) {
				botX[i] += 3;
				stop = true;
			}
			break;
		case 3:
			stop = true;
			break;
		}
	}

	for (int i = 0; i < CAR; i++) { // Движение машинки вниз 
		botY[i] ++;
	}
	for (int i = 0; i < CAR; i++) { // Если машинка проехала поле, возвращаем её наместо, обновляя её массив и разрешаем новое переключение
		if (botY[i] == 18) {
			for (int j = 0; j < CAR; j++) {
				botY[j] = botY1[j];
				botX[j] = botX1[j];
				
			}
			stop = false;
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
		std::cout << "Score: " << score << " Level: " << level << " Speed: " << speed << endl;

		Draw();
		Speed();
		Input();
		AvtoCar();
		Logik();

		if (carX[0] == botX[6] && carY[0] == botY[6]) {
			gameOwer = true;
		}
	}

	std::cout << "\nGame Ower! " << "Score: " << score << endl;
	system("pause");
	return 0;
}