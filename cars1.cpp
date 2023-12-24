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

int RandBot() { // Выбирает рандомно сторону движения машинки бота
	bot = rand() % 3 + 1;
	return bot;
}

void Draw(int carX[], int carY[], int botX[], int botY[]) { // Отрисовываем все элементы игрового поля
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

void AvtoCar(int botX[], int botY[], int botX1[], int botY1[], int RandBot()) { // Автоматическое движение машинки бота
	
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
		}
	}
}

void Logik(int carX[], int carY[]) { // Логика игры при управлении игрока
	switch (mot) { // Переключаем позицию машинки игрока
	case 1:
		for (int i = 0; i < CAR; i++) {
			carX[i] -=3;
			mot = 0; // Запрещаем дальнейшее движение в сторону, после переключения 
		}
		break;
	case 2:
		for (int i = 0; i < CAR; i++) {
			carX[i] +=3;
			mot = 0;
		}
		break;
	}
	/*for (int i = 0; i < CAR; i++) { // Эта часть кода должна была запрещать переключение машинки за игровое поле, но пока не работает
		
		if (carX[i] == COL - 3 || carX[i] == COL - COL + 3) {
			mot = 0;
		}
	
	}*/
}

int main() {
	setlocale(LC_ALL, "Russian");
	srand(time(NULL));
	
	int carX[CAR]{ 5,4,5,6,5,4,5,6 }; // Массив машинки игрока
	int carY[CAR]{ 10,11,11,11,12,13,13,13 };

	int botX[CAR]{ 5,4,5,6,5,4,5,6 }; // Массив машинки бота
	int botY[CAR]{ -4,-3,-3,-3,-2,-1,-1,-1 };

	int botX1[CAR]{ 5,4,5,6,5,4,5,6 }; //Копия для обнуления и возвращения машины бота на нулевое значение
	int botY1[CAR]{ -4,-3,-3,-3,-2,-1,-1,-1 };

	while (true) {
		system("cls");
		
		Draw(carX, carY, botX, botY);
		Sleep(50); // Скорость движение машинки, сделать изменяемой
		Input();
		AvtoCar(botX, botY, botX1, botY1, RandBot);
		Logik(carX, carY);
	}
	return 0;
}