#include <iostream>
#include <conio.h>
#include <ctime>
#include <windows.h>

using namespace std;

int row = 20; //Размер игрового поля
int col = 40;

class Ball { // Класс отвечающий за прыгающие мячи
public:
	int x = rand() % row + 1; // Координата мяча по x
	int y = rand() % col + 1; // Координата мяча по y
	int direction; // Направление полета мяча

	enum run {
		UPRIGHT, UPLEFT, DOWNRIGHT, DOWNLEFT
	};
	run go;

	void Motion() { // Метод определяет начальное направление полета мяча
		direction = 1;
		switch (direction) {
		case 0:
			go = UPRIGHT;
			break;
		case 1:
			go = UPLEFT;
			break;
		case 2:
			go = DOWNRIGHT;
			break;
		case 3:
			go = DOWNLEFT;
			break;
		}
	}
	
	void Fly() { // Движение мяча в зависимости от направления
		switch (go) {
		case UPRIGHT:
			x--;
			y++;
			break;
		case UPLEFT:
			x--;
			y--;
			break;
		case DOWNRIGHT:
			x++;
			y++;
			break;
		case DOWNLEFT:
			x++;
			y--;
			break;
		}
	}

	void Draw() { // Игровое поле
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				if (i == 0 || i == row - 1) {
					cout << "#";
				}
				else if (j == 0 || j == col - 1) {
					cout << "#";
				}
				else if (i == x && j == y) {
					cout << "O";
				}
				else {
					cout << " ";
				}
			}
			cout << endl;
		}
	}

	void Action() { // Функция переключения движения мяча при отбитии от стены
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				if (x == 1 && go == UPLEFT) {
					go = DOWNLEFT;
				}
				else if (y == 1 && go == DOWNLEFT) {
					go = DOWNRIGHT;
				}
				else if (x == row - 2 && go == DOWNRIGHT) {
					go = UPRIGHT;
				}
				else if (y == col - 2 && go == UPRIGHT) {
					go = UPLEFT;
				}
			}
		}
	}
};

int main() {
	srand(time(NULL));
	setlocale(LC_ALL, "Russian");

	Ball First;
	Ball Second;
	First.Motion();
	while (true) {
		system("cls");
		
		First.Draw();
		
		First.Fly();
		First.Action();
		
		Sleep(100);
	}
	return 0;
}