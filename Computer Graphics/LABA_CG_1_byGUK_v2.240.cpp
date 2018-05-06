//-------------------------------INCLUDE-BLOCK----------------------------------

#include "stdafx.h"
#include "stdio.h"
#include "iostream"
#include "windowsx.h"
#include "locale.h"
#define _AFXDLL
#include "afxwin.h"
using namespace std;

//-------------------------------SET-UP-BLOCK-----------------------------------

#define YELLOW_C RGB(255, 202, 64) //так легко задавать цвета
#define PINK_C RGB(148, 4, 119)
#define RED_C RGB(255, 0, 0)
#define BLUE_C RGB(92, 204, 204)
#define GRIN_C RGB(152, 211, 13)
#define SPACE_LEFT 20   //параметры смещения от верхнего левого угла консоли
#define SPACE_UP 300

//2 координаты - всего то
struct dot
{
	int x;
	int y;
};

// все необходимые параметры сетки
struct grid
{
	unsigned int size = 14;
	unsigned int width = 32;
	unsigned int height = 32;
};

void PutDot(HDC *hDC, int x, int y, grid isGrid);// тыкаем масштабированную точку
void DrawGrid(HDC *hDC, grid isGrid); //просто чертит сетку

									  //-----------------------------------MAIN---------------------------------------

void main()
{
	//---------------------------------------------------------------------------
	setlocale(LC_ALL, "RUS");
	system("mode con cols=140 lines=70");// расширяем консоль
	HWND hWnd = GetConsoleWindow(); // получаем идентификатор окна
	HDC hDC = GetDC(hWnd); // получаем контекст отображения
	HPEN whitePen = GetStockPen(WHITE_PEN); // создаем перо для рисования сетки. Перо участвует в отрисовке контуров
	HBRUSH pinkBrush = CreateSolidBrush(PINK_C);// вот так можно создать кисть. Кисть отвечает за цвет заливки фигур(в нашем случае - точки)
												//---------------------------------------------------------------------------
	SelectPen(hDC, whitePen);  // переключаем перо
	SelectBrush(hDC, pinkBrush);// и кисть
	grid generalGrid;
	char quest = NULL;
	cout << "Использовать дефолтные значения таблицы?{y or something}  ";cin >> quest;
	if (quest != 'y')
	{
		cout << "Введите размер сетки (2 числа) и размерность ячейки через пробел \n";// ячейки под ~30 - самое то
		cin >> generalGrid.width >> generalGrid.height >> generalGrid.size;
	}
	DrawGrid(&hDC, generalGrid);
	for (bool oops = true;oops;)// такой цикл, чтобы не выносить его в отдельный метод с if'ом или switch'ом
	{
		oops = false;
		dot qDot;// = { 5,5 }; // так тоже можно
		cout << "В какой клетке точку поставить?(x,y)      ";
		cin >> qDot.x >> qDot.y;
		PutDot(&hDC, qDot.x, qDot.y, generalGrid);
		cout << "Продолжить?{y or something}  ";cin >> quest; // "еще разок?" 
		oops = quest == 'y';
	}
	//---------------------------------------------------------------------------
	DeleteObject(whitePen);// не забыть почистить за собой
	DeleteObject(pinkBrush);
	ReleaseDC(hWnd, hDC);
	system("pause");
}

//-----------------------------FUNCTIONAL-BLOCK---------------------------------

void PutDot(HDC *hDC, int x, int y, grid isGrid)
{
	int yMax = isGrid.height*isGrid.size + SPACE_UP;
	int xMax = isGrid.width*isGrid.size + SPACE_LEFT;
	int xL = SPACE_LEFT + (x - 1)*isGrid.size, xR = SPACE_LEFT + x * isGrid.size;
	int yT = SPACE_UP + (y - 1)*isGrid.size, yD = SPACE_UP + y * isGrid.size;
	if ((xR>SPACE_LEFT) && (yD>SPACE_UP) && (yT<yMax) && (xL<xMax))// проверка по координатам, точка за пределами сетки просто не появится
		Ellipse(*hDC, xL, yT, xR, yD);
}
void DrawGrid(HDC *hDC, grid isGrid)
{
	int x, y, x1, y1;
	//устанавливаем начальное положение пера
	x = x1 = SPACE_LEFT;
	y = y1 = SPACE_UP;
	//рисование по y
	for (unsigned int i = 0; i <= isGrid.height; i++)
	{
		MoveToEx(*hDC, x, y, NULL);
		LineTo(*hDC, x + (isGrid.width*isGrid.size), y);
		y += (isGrid.size);
	}
	//рисование по x
	for (unsigned int j = 0; j <= isGrid.width; j++)
	{
		MoveToEx(*hDC, x1, y1, NULL);
		LineTo(*hDC, x1, y1 + (isGrid.height*isGrid.size));
		x1 += (isGrid.size);
	}
}