#include <iostream>
#include <ctime>
#include <conio.h>
#include <windows.h>

#define FIGUR 4 // Константа для масива фигуры (фигура не будет иметь больше 4 переменых)
#define BAG 100 // Константа для размера корзины

using namespace std;

//int cubic[2][2]{ {0,5}, {0,6} };

enum motion{ Down, Right, Left, Stop = 0, // Перечесления направлений движения фигуры
};
motion run;

void Input() { // Задаем и считываем клавиши управления
	if (_kbhit()) {
		switch (_getch()) {
		case 'a':
			run = Left;
			break;
		case 's':
			run = Right;
			break;
		}
	}
}

void Logik(int arrX[], int brrY[], int crrX[], int drrY[]) { // Логика игры
	run = Down;
	switch (run) { // Определение направления движения фигуры и смена направления
	case Left:
		for (int i = 0; i < FIGUR; i++) {
			arrX[i]--;
		}
		break;
	case Right:
		for (int i = 0; i < FIGUR; i++) {
			arrX[i]++;
		}
		break;
	case Down:
		for (int i = 0; i < FIGUR; i++) {
			brrY[i]++;
		}
		break;
	}
	for (int i = 0; i < FIGUR; i++) { // Если фигура уперлась в пол или другую фигуру - останавливаем её движение
		if (brrY[i] == BAG) {
			run = Stop;
		}
	}
	// Далее написать функцию, которае при run = stop перезаписывает значения из массива фигуры в массив корзины.
	//Массив корзины при этом обнуляется и в него записываются координаты новой фигуры вверху корзины.
	// И новая фигура так-же начинает опускаться вниз
}

int main() {
	int bagX[BAG]{}; // Массивы - корзина для фигур
	int bagY[BAG]{};

	int figuraX[FIGUR]{ 5,6,5,6 }; // Параметры фигуры по горизонтали
	int figuraY[FIGUR]{ 0,0,1,1 }; // Параметры фигуры по вертикали

	while (true) {
		system("cls");
		
		Input();
		Logik(figuraX, figuraY, bagX, bagY);
	}
	return 0;
}