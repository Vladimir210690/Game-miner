#include <iostream>
#include <ctime>
#include <conio.h>
#include <windows.h>

using namespace std;

class Snacs{
private:
	int x = 0, y = 0, frX = 0, frY = 0, score = 0; // Переменные отвечающие за голову, фрукты и счет игры
	const int ROW = 20, COL = 40; // Переменные отвечающие за размер карты
	int TailX[50]{}, TailY[50]{}; // Массивы хвоста змейки
	int tx = 0, ty = 0, tx1 = 0, ty1 = 0; // Переменные отвечающе за движение хвоста

	bool gameOver = true; // Переменная окончания игры
	enum Motion { // Перечисление отвечающее за направление движения змейки
		STOP = 0, UP = 1, DOWN = 2, LEFT = 3, RIGHT = 4
	};
	Motion Go;
public:
	Snacs() { // Конструктор класса отвечающий за стартовое положение головы и фрукта
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
					cout << " ";
				}
			}
			cout << endl;
		}
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
	}
	void Rand() {
		if (x == frX && y == frY) { // Условие появления нового фрукта
			frX = rand() % ROW;
			frY = rand() % COL;
			if (frX == 0) {
				Rand();
			}
			
			score += 1;
		}
	}
	void Revers() {
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
	Snacs Game;
	while (true) {
		system("cls");
		Game.Draw();
		Game.Input();
		Game.Logik();
		Game.Rand();
		Game.Revers();
		Sleep(100);
	}
	return 0;
}
