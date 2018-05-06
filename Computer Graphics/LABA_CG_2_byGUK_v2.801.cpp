//-------------------------------INCLUDE-BLOCK----------------------------------

#include "stdafx.h"
#include "stdio.h"
#include "iostream"
#include "windowsx.h"
#include "locale.h"
#include "math.h"
#define _AFXDLL
#include "afxwin.h"
using namespace std;

//-------------------------------SET-UP-BLOCK-----------------------------------

#define YELLOW_C RGB(255, 202, 64)
#define PINK_C RGB(148, 4, 119)
#define RED_C RGB(255, 0, 0)
#define BLUE_C RGB(92, 204, 204)
#define GRIN_C RGB(152, 211, 13)
#define SKIN_C RGB(255, 178, 115)
#define PURPLE_C RGB(72, 3, 111)
#define ORANGE_C RGB(255 ,116, 0)

#define SPACE_LEFT 20
#define SPACE_UP 400
#define DEFAULT_RADIUS 24
struct grid
{
	unsigned int size = 14;
	unsigned int width = 32;
	unsigned int height = 32;
};
struct dot
{
	int x;
	int y;
};
void PutDot(HDC *hDC, int x, int y, grid isGrid);
void Cirle(HDC *hDC, grid isGrid, dot middle, int radius);// Окружность по заданному центру и радиусу
void LineBrez(HDC *hDC, grid isGrid, dot aa, dot bb);// Отрезок методом Брезенхема
void LineCDA(HDC *hDC, grid isGrid, dot b, dot e);// Отрезок методом ЦДА
void DrawGrid(HDC *hDC, grid isGrid);

//-----------------------------------MAIN---------------------------------------

int main()
{
	//---------------------------------------------------------------------------
	setlocale(LC_ALL, "RUS");
	system("mode con cols=140 lines=70");
	HWND hWnd = GetConsoleWindow(); // получаем идентификатор окна
	HDC hDC = GetDC(hWnd); // получаем контекст отображения
	HPEN whitePen = GetStockPen(WHITE_PEN); //создаем перо для рисования сетки
	HPEN hPen1 = CreatePen(PS_SOLID, 1, RGB(32, 7, 114));
	HPEN hPen2 = CreatePen(PS_SOLID, 1, RGB(110, 165, 110));
	HBRUSH grinBrush = CreateSolidBrush(GRIN_C);
	HBRUSH purpleBrush = CreateSolidBrush(PURPLE_C);
	HBRUSH orangeBrush = CreateSolidBrush(ORANGE_C);
	//---------------------------------------------------------------------------
	grid totalGrid;     /** - достаточно добавить последний '/' и строки раскомменчены/**/
						/**std::cout << "Введите размер сетки (2 числа) и размерность ячейки через пробел \n";// ячейки под ~12 - самое то
						cin >> totalGrid.width >> totalGrid.height >> totalGrid.size;/**/ //используем дефолт, иначе-раскомментить
	SelectPen(hDC, whitePen);
	DrawGrid(&hDC, totalGrid);
	short int question;
	std::cout << "\n Что интересует?   Ключи :1 -прямая алгоритмом ЦДА,\n 2 -прямая алгоритмом Брезенхема 3 -окружность\n";
	cin >> question;
	SelectPen(hDC, hPen1);
	switch (question)
	{
	case 1:
	{
		SelectBrush(hDC, purpleBrush);// для каждого вида - свой цвет
		LineCDA(&hDC, totalGrid, { 10, 15 }, { 15,10 });// ну ввод точек сделайте сами
		break;
	}
	case 2:
	{
		SelectBrush(hDC, grinBrush);
		LineBrez(&hDC, totalGrid, { 1, 4 }, { 12,2 });
		break;
	}
	case 3:
	{
		SelectBrush(hDC, orangeBrush);
		Cirle(&hDC, totalGrid, { 12,12 }, 10);
		break;
	}
	default:
	{
		std::cout << "введите корректно по ключам";
		break;
	}
	}
	//---------------------------------------------------------------------------
	DeleteObject(whitePen);
	DeleteObject(grinBrush);
	DeleteObject(purpleBrush);
	DeleteObject(orangeBrush);
	DeleteObject(hPen1);
	DeleteObject(hPen2);
	DeleteObject(whitePen);
	ReleaseDC(hWnd, hDC);
	system("pause");
	return 0;
}

//-----------------------------FUNCTIONAL-BLOCK---------------------------------

void PutDot(HDC *hDC, int x, int y, grid isGrid)
{
	int yMax = isGrid.height*isGrid.size + SPACE_UP;
	int xMax = isGrid.width*isGrid.size + SPACE_LEFT;
	int xL = SPACE_LEFT + (x - 1)*isGrid.size, xR = SPACE_LEFT + x * isGrid.size;
	int yT = SPACE_UP + (y - 1)*isGrid.size, yD = SPACE_UP + y * isGrid.size;
	if ((xR>SPACE_LEFT) && (yD>SPACE_UP) && (yT<yMax) && (xL<xMax))
		Ellipse(*hDC, xL, yT, xR, yD);
}
void Cirle(HDC *hDC, grid isGrid, dot middle, int radius)
{
	int y = 0; int x = radius;
	int xMiddle = middle.x; int yMiddle = middle.y;
	int trueRadius = radius / sqrt(2);// пройдемся только по дуге [0;PI/8]
	while (abs(x) >= trueRadius)
	{
		PutDot(hDC, xMiddle + x, yMiddle + y, isGrid);//отражаем 8 раз
		PutDot(hDC, xMiddle + x, yMiddle - y, isGrid);//прибавляем координаты центра для абсолютного смещения
		PutDot(hDC, xMiddle - x, yMiddle + y, isGrid);
		PutDot(hDC, xMiddle - x, yMiddle - y, isGrid);
		PutDot(hDC, xMiddle + y, yMiddle + x, isGrid);
		PutDot(hDC, xMiddle + y, yMiddle - x, isGrid);
		PutDot(hDC, xMiddle - y, yMiddle + x, isGrid);
		PutDot(hDC, xMiddle - y, yMiddle - x, isGrid);
		int dh = x * x + (y - 1)*(y - 1) - radius * radius;// точка выше прямо
		int dc = (x - 1)*(x - 1) + (y - 1)*(y - 1) - radius * radius;// точка выше левее
		if (abs(dh) > abs(dc)) x--;// какая из предполагаемых точек больше подходит под радиусное расстояние
		y--;//шаг
	}
}
void LineBrez(HDC *hDC, grid isGrid, dot aa, dot bb)
{
	int dx, dy, ch = 0, i = 0, e, dx2, dy2;
	bb.x -= aa.x; dx = abs(bb.x);
	bb.y -= aa.y; dy = abs(bb.y);
	int maxByX = max(bb.x, aa.x) + 1;
	int maxByY = max(bb.y, aa.y) + 1;
	if (bb.x) bb.x = bb.x < 0 ? -1 : 1;
	if (bb.y) bb.y = bb.y < 0 ? -1 : 1;
	if (dy > dx) { int t = dy; dy = dx; dx = t; ch = 1; } // меняем местами x и y
	dx2 = dx << 1; dy2 = dy << 1; // dx2 = 2*dx; dy2 = 2*dy;
	e = dy2 - dx; // Начальное значение ошибки;
	for (int i = 0; i <= dx + dy;i++)
	{
		PutDot(hDC, aa.x, aa.y, isGrid);
		if (e > 0) { if (ch) aa.x += bb.x; else aa.y += bb.y; e -= dx2; }
		else { if (ch) aa.y += bb.y; else aa.x += bb.x; e += dy2; }
	}
}
void LineCDA(HDC *hDC, grid isGrid, dot b, dot e)
{
	if (b.x > e.x)// сортируем начало и конец по ключу - х
	{
		dot temp = b;
		b = e;
		e = temp;
	}
	double step = (double)(e.y - b.y) / (e.x - b.x); //из формулы для вычисления у 
	int x = b.x;
	int y = b.y;
	for (double yDouble = b.y; (x <= e.x); x++)//на каждый целочисленный х приходится только 1 у, поэтому в вытянутых по вертикали линиях будут разрывы
	{
		PutDot(hDC, x, y, isGrid);
		yDouble += step;
		y = round(yDouble);
	}
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