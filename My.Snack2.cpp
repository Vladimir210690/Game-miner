#include <iostream>
#include <ctime>
#include <conio.h>
#include <windows.h>

using namespace std;

class Snack{
private:
	int x = 0, y = 0, frX = 0, frY = 0, score = 0; // Переменные отвечающие за голову, фрукты и счет игры
	const int ROW = 20, COL = 40; // Переменные отвечающие за размер карты
	int TailX[50]{}, TailY[50]{}; // Массивы хвоста змейки
	int tx = 0, ty = 0, tx1 = 0, ty1 = 0, ntail = 0; // Переменные отвечающе за движение хвоста

	bool gameOver = true; // Переменная окончания игры
	enum Motion { // Перечисление отвечающее за направление движения змейки
		STOP = 0, UP = 1, DOWN = 2, LEFT = 3, RIGHT = 4
	};
	Motion Go;
public:
	Snack() { // Конструктор класса отвечающий за стартовое положение головы и фрукта
		gameOver = true;
		x = ROW / 2;
		y = COL / 2;
		frX = rand() % ROW + 1;
		frY = rand() % COL + 1;
	}
	void Draw() { // Метод отрисовки игрового поля
		for (int i = 0; i < ROW; i++) {
			for (int j = 0; j < COL; j++) {
				if (i == 0 || i == ROW - 1) {
					cout << "#";
				}
				else if (j == 0 || j == COL - 1) {
					cout << "#";
				}
				else if (i == x && j == y) {
					cout << "O";
				}
				else if (i == frX && j == frY) {
					cout << "*";
				}
				else {
					bool flag = false;
					for (int k = 0; k < ntail; k++) {
						if (TailX[k] == i && TailY[k] == j) {
							flag = true;
							cout << "o";
						}
					}
					if (flag == false) {
						cout << " ";
					}
				}
			}
			cout << endl;
		}
		cout << "Score: " << score;
	}
	void Input() { // Метод отслеживания кода нажатых клавиш
		if (_kbhit()) {
			switch (_getch()) {
			case 72:
				Go = UP;
				break;
			case 80:
				Go = DOWN;
				break;
			case 75:
				Go = LEFT;
				break;
			case 77:
				Go = RIGHT;
				break;
			}
		}
	}
	void Logik() { // Метод логики игры
		switch (Go) {
		case UP:
			x--;
			break;
		case DOWN:
			x++;
			break;
		case LEFT:
			y--;
			break;
		case RIGHT:
			y++;
			break;
		}
		
		tx = TailX[0];
		ty = TailY[0];
		tx1 = 0;
		ty1 = 0;
		TailX[0] = x;
		TailY[0] = y;

		for (int i = 1; i < ntail; i++) { // Прогоняем движение хвоста, помещая его в массивы
			
			tx1 = TailX[i];
			ty1 = TailY[i];

			TailX[i] = tx;
			TailY[i] = ty;

			tx = tx1;
			ty = ty1;
		}
	}
	void Rand() {
		if (x == frX && y == frY) { // Условие появления нового фрукта
			int ax = rand() % ROW; // назначаем временные переменные в которые генерируем новые координаты фрукта 
			int ay = rand() % COL;
			if (ax == 0 || ax == ROW - 1) { // Есди одна из координат попадает в 0 или ROW - 1, вызываем рекурсию
				Rand();	
			}
			else if (ay == 0 || ay == COL - 1) { // Тоже самое для колонок
				Rand();
			}
			else {
				frX = ax; // Иначе присваиваем значения координатам фрукта
				frY = ay;
				score += 1;
				ntail += 1;
			}
		}
	}
	void Revers() { // Доработать
		if (x == 0) { // Условие реверсирования через стены
			x = ROW - 2;
		}
		else if (x == ROW) {
			x = 1;
		}
		else if (y == 0) {
			y = COL - 2;
		}
		else if (y == COL) {
			y = 1;
		}
	}
};



int main() {
	srand(time(NULL));
	Snack Game;
	while (true) {
		system("cls");
		
		Game.Input();
		Game.Logik();
		Game.Rand();
		Game.Revers();
		Game.Draw();
		Sleep(100);
	}
	return 0;
}