#include <iostream>
#include <ctime>
#include <conio.h>
#include <windows.h>
#define ROW 15
#define COL 11

using namespace std;
int mot = 0;// Движение машины игрока

void Draw(int carX[], int carY[]) {
	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COL; j++) {
			if (i == 0 || i == ROW - 1) {
				cout << "#";
			}
			else if (j == 0 || j == COL - 1) {
				cout << "#";
			}
			else {
				bool yas = false;
				for (int k = 0; k < 8; k++) {
					if (carY[k] == i && carX[k] == j) {
						yas = true;
						cout << "+";
					}
				}
				if (yas == false) {
					cout << " ";
				}
			}
		}
		cout << endl;
	}
}

void Input() {
	if (_kbhit()) {
		switch (_getch()) {
		case 'a':
			mot = 1;
			break;
		case 'd':
			mot = 2;
			break;
		}
	}
}

void Logik(int carX[], int carY[]) {
	switch (mot) {
	case 1:
		for (int i = 0; i < 8; i++) {
			carX[i] -=3;
			mot = 0;
		}
		break;
	case 2:
		for (int i = 0; i < 8; i++) {
			carX[i] +=3;
			mot = 0;
		}
		break;
	}
	for (int i = 0; i < 8; i++) {
		
		if (carX[i] == COL - 3 || carX[i] == COL - COL + 3) {
			mot = 0;
		}
	
	}
}

int main() {
	
	int carX[8]{ 5,4,5,6,5,4,5,6 };
	int carY[8]{ 10,11,11,11,12,13,13,13 };

	while (true) {
		system("cls");
		

		Draw(carX, carY);
		Sleep(300);
		Input();
		Logik(carX, carY);
	}
	return 0;
}