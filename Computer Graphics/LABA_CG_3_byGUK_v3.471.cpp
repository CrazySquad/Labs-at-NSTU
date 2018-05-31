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
	unsigned int size = 8;
	unsigned int width = 90;
	unsigned int height = 90;
};
struct dot
{
	int x;
	int y;
};
void PutDot(HDC *hDC, int x, int y, grid isGrid);
dot getMiddleDot(dot a, dot b);// Получение средней точки отрезка-> Можно найти ~среднюю~ точку треугольника, чтобы начать заливку с неё
void DrawGrid(HDC *hDC, grid isGrid);
void LineBrez(HDC *hDC, grid isGrid, dot aa, dot bb);
void TriangleBrez(dot a, dot b, dot c, HDC *hDC, grid isGrid);// Треугольник по 3м точкам, которые соединяются отрезками методом Брезенхема
void Cirle(HDC *hDC, grid isGrid, dot middle, int radius);//
void PixelFillforBrez(HDC* hDC, grid isGrid, int x, int y, COLORREF BolderColor, COLORREF selfColor);// Заливка с затравкой с 8ми ходами
void PixelFillforCDA(HDC* hDC, grid isGrid, int x, int y, COLORREF BolderColor, COLORREF selfColor);// Заливка с затравкой с 4мя ходами
void LineCDAhalfY(HDC *hDC, grid isGrid, dot b, dot e);// Составляющая обычного ЦДА, с тем же содержанием, но шагом в у++
void LineCDA(HDC *hDC, grid isGrid, dot b, dot e);// Дополненный алгоритм ЦДА с проходом по х и по у, чтобы не было разрывов
void TriangleCDA(dot a, dot b, dot c, HDC *hDC, grid isGrid);// Треугольник по 3м точкам, которые соединяются отрезками ЦДА
void FilledTriangle(HDC* hDC, grid isGrid, dot a, dot b, dot c);// Треугольник методом реберных точек (тот же ЦДА и заполнение отрезка (x1 до x2,y++) между ребрами)

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
	HBRUSH yellowBrush = CreateSolidBrush(YELLOW_C); //создание кисти 
	HBRUSH pinkBrush = CreateSolidBrush(PINK_C);
	HBRUSH grinBrush = CreateSolidBrush(GRIN_C);
	HBRUSH redBrush = CreateSolidBrush(RED_C);
	HBRUSH blueBrush = CreateSolidBrush(BLUE_C);
	HBRUSH skinBrush = CreateSolidBrush(SKIN_C);
	HBRUSH purpleBrush = CreateSolidBrush(PURPLE_C);
	HBRUSH orangeBrush = CreateSolidBrush(ORANGE_C);
	//---------------------------------------------------------------------------
	grid myTable;// = { 6,80,80 };   на 15ой версии не работает(?)
	/**std::cout << "Введите размер сетки (2 числа) и размерность ячейки через пробел \n";/**/
	/*/cin >> myTable.width >> myTable.height >> myTable.size;/**/ //юзаем значения по умолчанию и не паримся
	/**SelectPen(hDC, whitePen);/*/SelectPen(hDC, hPen1);/**/   //это такой свитч для экспериментов
	DrawGrid(&hDC, myTable);
	/**SelectPen(hDC, whitePen);/*/SelectPen(hDC, hPen2);/**/
	for (bool t = true;t;)// опять же чтобы не делать отдельный метод, который бы вызывал сам себя
	{
		t = false;
		char quest = NULL, quest2 = NULL;
		std::cout << "Ключи: b - треугольник по Брезенхему, с - окружность\nt - треугольник ч/з ЦДА, f - залитый треугольник(методом реберных точек).\n Ответ:   ";
		std::cin >> quest;
		switch (quest)
		{
		case 'b':
		{
			SelectBrush(hDC, yellowBrush);// для каждого вида - свой цвет
			dot a = { 2,5 }, b = { 38,74 }, c{ 59,2 };//дефолт
			std::cout << "Использовать значения по умолчанию?[y or something else]  "; std::cin >> quest2;
			if (quest2 != 'y') { std::cout << "три точки(6 значений) : "; std::cin >> a.x >> a.y >> b.x >> b.y >> c.x >> c.y; }
			TriangleBrez(a, c, b, &hDC, myTable);
			std::cout << "Залить треугольник алгоритмом с затравкой?[y or something else]  "; std::cin >> quest2;
			if (quest2 == 'y')
			{
				SelectBrush(hDC, pinkBrush);// и цвет заливки тоже
				dot middle = getMiddleDot(a, getMiddleDot(b, c));
				PixelFillforBrez(&hDC, myTable, middle.x, middle.y, YELLOW_C, PINK_C);
			}
			break;
		}
		case 'c':
		{
			dot a = { 40,30 }; int radius = DEFAULT_RADIUS;//дефолт
			std::cout << "Использовать значения по умолчанию?[y or something else]  "; std::cin >> quest2;
			if (quest2 != 'y') { std::cout << "центр и радиус(3 значения) : "; std::cin >> a.x >> a.y >> radius; }
			SelectBrush(hDC, purpleBrush);
			Cirle(&hDC, myTable, a, radius);
			std::cout << "Залить круг алгоритмом с затравкой?[y or something else]  "; std::cin >> quest2;
			if (quest2 == 'y')
			{
				SelectBrush(hDC, orangeBrush);
				PixelFillforCDA(&hDC, myTable, a.x, a.y, PURPLE_C, ORANGE_C);
			}
			break;
		}
		case 't':
		{
			SelectBrush(hDC, blueBrush);
			dot a = { 74,27 }, b = { 38,71 }, c{ 39,2 };//дефолт
			std::cout << "Использовать значения по умолчанию?[y or something else]  "; std::cin >> quest2;
			if (quest2 != 'y') { std::cout << "три точки(6 значений) : "; std::cin >> a.x >> a.y >> b.x >> b.y >> c.x >> c.y; }
			TriangleCDA(a, c, b, &hDC, myTable);
			std::cout << "Залить треугольник алгоритмом с затравкой?[y or something else]  "; std::cin >> quest2;
			if (quest2 == 'y')
			{
				SelectBrush(hDC, redBrush);
				dot middle = getMiddleDot(a, getMiddleDot(b, c));
				PixelFillforCDA(&hDC, myTable, middle.x, middle.y, BLUE_C, RED_C);
			}
			break;
		}
		case 'f':
		{
			SelectBrush(hDC, grinBrush);
			dot a = { 21,58 }, b = { 14,76 }, c{ 78,38 };//дефолт
			std::cout << "Использовать значения по умолчанию?[y or something else]  "; std::cin >> quest2;
			if (quest2 != 'y') { std::cout << "три точки(6 значений) : "; std::cin >> a.x >> a.y >> b.x >> b.y >> c.x >> c.y; }
			FilledTriangle(&hDC, myTable, a, b, c);
			break;
		}
		default:
		{
		std:cout << "Несоответствие ключам!\n";
			break;
		}
		}
		quest = NULL;
		std::cout << "Продолжить?[y or something else]  ";
		std::cin >> quest;
		if (quest == 'y') t = true;
	}
	//---------------------------------------------------------------------------
	DeleteObject(whitePen);
	DeleteObject(yellowBrush);
	DeleteObject(skinBrush);
	DeleteObject(purpleBrush);
	DeleteObject(orangeBrush);
	DeleteObject(pinkBrush);
	DeleteObject(redBrush);
	DeleteObject(blueBrush);
	DeleteObject(grinBrush);
	DeleteObject(hPen1);
	DeleteObject(hPen2);
	ReleaseDC(hWnd, hDC);
	system("pause");
	//---------------------------------------------------------------------------
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
dot getMiddleDot(dot a, dot b)
{
	dot res;
	res.x = int(round((a.x + b.x) / 2));
	res.y = int(round((b.y + a.y) / 2));
	return res;
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
void TriangleBrez(dot a, dot b, dot c, HDC *hDC, grid isGrid)
{
	LineBrez(hDC, isGrid, a, b);
	LineBrez(hDC, isGrid, a, c);
	LineBrez(hDC, isGrid, c, b);
}
void Cirle(HDC *hDC, grid isGrid, dot middle, int radius)
{
	int y = 0; int x = radius;
	int xMiddle = middle.x; int yMiddle = middle.y;
	int trueRadius = radius / sqrt(2);
	while (abs(x) >= trueRadius)
	{
		PutDot(hDC, xMiddle + x, yMiddle + y, isGrid);
		PutDot(hDC, xMiddle + x, yMiddle - y, isGrid);
		PutDot(hDC, xMiddle - x, yMiddle + y, isGrid);
		PutDot(hDC, xMiddle - x, yMiddle - y, isGrid);
		PutDot(hDC, xMiddle + y, yMiddle + x, isGrid);
		PutDot(hDC, xMiddle + y, yMiddle - x, isGrid);
		PutDot(hDC, xMiddle - y, yMiddle + x, isGrid);
		PutDot(hDC, xMiddle - y, yMiddle - x, isGrid);
		int dh = x * x + (y - 1)*(y - 1) - radius * radius;
		int dc = (x - 1)*(x - 1) + (y - 1)*(y - 1) - radius * radius;
		if (abs(dh) > abs(dc)) x--;
		y--;
	}
}
void PixelFillforBrez(HDC* hDC, grid isGrid, int x, int y, COLORREF BolderColor, COLORREF selfColor)
{
	int yMax = isGrid.height*isGrid.size + SPACE_UP;
	int xMax = isGrid.width*isGrid.size + SPACE_LEFT;
	int xL = SPACE_LEFT + (x - 1)*isGrid.size, xR = SPACE_LEFT + x * isGrid.size;
	int yT = SPACE_UP + (y - 1)*isGrid.size, yD = SPACE_UP + y * isGrid.size;
	if ((xR > SPACE_LEFT) && (yD > SPACE_UP) && (yT < yMax) && (xL < xMax)) {// можно залить все вокруг фигуры и не поймать ошибку рантайма, несмотря на отсутствие цветных границ
		COLORREF c = GetPixel(*hDC, int((x - 0.5)*isGrid.size) + SPACE_LEFT, int((y - 0.5)*isGrid.size) + SPACE_UP);
		if ((c != BolderColor) && (c != selfColor))// чтобы упираться в границы фигуры и не перезаливать ее вечно(ошибка рантайма)
		{
			PutDot(hDC, x, y, isGrid);
			PixelFillforBrez(hDC, isGrid, x - 1, y, BolderColor, selfColor);//вот эти 8 направлений
			PixelFillforBrez(hDC, isGrid, x + 1, y, BolderColor, selfColor);
			PixelFillforBrez(hDC, isGrid, x, y - 1, BolderColor, selfColor);
			PixelFillforBrez(hDC, isGrid, x, y + 1, BolderColor, selfColor);
			PixelFillforBrez(hDC, isGrid, x - 1, y - 1, BolderColor, selfColor);
			PixelFillforBrez(hDC, isGrid, x + 1, y + 1, BolderColor, selfColor);
			PixelFillforBrez(hDC, isGrid, x + 1, y - 1, BolderColor, selfColor);
			PixelFillforBrez(hDC, isGrid, x - 1, y + 1, BolderColor, selfColor);
		}
	}
}
void PixelFillforCDA(HDC* hDC, grid isGrid, int x, int y, COLORREF BolderColor, COLORREF selfColor)
{
	int yMax = isGrid.height*isGrid.size + SPACE_UP;
	int xMax = isGrid.width*isGrid.size + SPACE_LEFT;
	int xL = SPACE_LEFT + (x - 1)*isGrid.size, xR = SPACE_LEFT + x * isGrid.size;
	int yT = SPACE_UP + (y - 1)*isGrid.size, yD = SPACE_UP + y * isGrid.size;
	if ((xR > SPACE_LEFT) && (yD > SPACE_UP) && (yT < yMax) && (xL < xMax)) {// можно залить все вокруг фигуры и не поймать ошибку рантайма, несмотря на отсутствие цветных границ
		COLORREF c = GetPixel(*hDC, int((x - 0.5)*isGrid.size) + SPACE_LEFT, int((y - 0.5)*isGrid.size) + SPACE_UP);
		if ((c != BolderColor) && (c != selfColor))// чтобы упираться в границы фигуры и не перезаливать ее вечно(ошибка рантайма)
		{
			PutDot(hDC, x, y, isGrid);
			PixelFillforCDA(hDC, isGrid, x - 1, y, BolderColor, selfColor);// а тут всего 4-никаких диагоналей
			PixelFillforCDA(hDC, isGrid, x + 1, y, BolderColor, selfColor);
			PixelFillforCDA(hDC, isGrid, x, y - 1, BolderColor, selfColor);
			PixelFillforCDA(hDC, isGrid, x, y + 1, BolderColor, selfColor);
		}
	}
}
void LineCDAhalfY(HDC *hDC, grid isGrid, dot b, dot e)
{
	if (b.y > e.y)
	{
		dot temp = b;
		b = e;
		e = temp;
	}
	double step = (double)(e.x - b.x) / (e.y - b.y);
	int x = b.x;
	int y = b.y;
	for (double xDouble = b.x; (y <= e.y); y++)
	{
		PutDot(hDC, x, y, isGrid);
		xDouble += step;
		x = round(xDouble);
	}
}
void LineCDA(HDC *hDC, grid isGrid, dot b, dot e)
{
	if (b.x > e.x)
	{
		dot temp = b;
		b = e;
		e = temp;
	}
	double step = (double)(e.y - b.y) / (e.x - b.x);
	int x = b.x;
	int y = b.y;
	for (double yDouble = b.y; (x <= e.x); x++)
	{
		PutDot(hDC, x, y, isGrid);
		yDouble += step;
		y = round(yDouble);
	}
	LineCDAhalfY(hDC, isGrid, b, e);
}
void TriangleCDA(dot a, dot b, dot c, HDC *hDC, grid isGrid)
{
	LineCDA(hDC, isGrid, a, b);
	LineCDA(hDC, isGrid, a, c);
	LineCDA(hDC, isGrid, c, b);
}
void FilledTriangle(HDC* hDC, grid isGrid, dot a, dot b, dot c)
{
	int tmp;
	int Y[3] = { a.y,b.y,c.y };
	int X[3] = { a.x,b.x,c.x };
	for (int i = 0; i<2;i++)//
		for (int j = 0; j<2;j++)
			if (Y[j]<Y[j + 1])
			{
				tmp = Y[j + 1];
				Y[j + 1] = Y[j];
				Y[j] = tmp;
				tmp = X[j + 1];
				X[j + 1] = X[j];
				X[j] = tmp;
			}
	c.y = Y[0];b.y = Y[1];a.y = Y[2];
	c.x = X[0];b.x = X[1];a.x = X[2];// сортировали тип
	int x1, x2, sy = c.y;
	for (; sy >= b.y; sy--)
	{
		x1 = c.x + int(round((a.x - c.x)*(sy - c.y) / (a.y - c.y)));// та же формула ЦДА
		x2 = c.x + int(round((b.x - c.x)*(sy - c.y) / (b.y - c.y)));
		LineCDA(hDC, isGrid, { x1, sy }, { x2, sy });
	}
	for (; sy >= a.y; sy--)
	{
		x1 = c.x + int(round((a.x - c.x)*(sy - c.y) / (a.y - c.y)));
		x2 = b.x + int(round((a.x - b.x)*(sy - b.y) / (a.y - b.y)));
		LineCDA(hDC, isGrid, { x1, sy }, { x2, sy });
	}
}
