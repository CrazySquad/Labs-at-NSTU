//-------------------------------INCLUDE-BLOCK----------------------------------
#include "stdafx.h"
#include "stdio.h"
#include "iostream"
#include "windowsx.h"
#include "locale.h"
#include "math.h"
#include <ctime>
#define _AFXDLL
#include "afxwin.h"
#include "Colors.h"
using namespace std;

//-------------------------------SET-UP-BLOCK-----------------------------------
#define SPACE_LEFT 20
#define SPACE_UP 200
struct grid
{
	unsigned int size = 10;
	unsigned int width = 40;
	unsigned int height = 40;
};
struct dot
{
	int x;
	int y;
};

void PutDot(HDC *hDC, int x, int y, grid isGrid, int e, COLORREF isColor[5]);
void DrawGrid(HDC *hDC, grid isGrid);
void MyLine(HDC *hDC, grid isGrid, dot aa, dot bb, COLORREF isColor[4][5]);

int main()
{
	//--------------------------------------------------------------------------
	COLORREF colorArr[4][5];
	colorArr[0][0] = v5; colorArr[0][1] = v4;colorArr[0][2] = v3;colorArr[0][3] = v2;colorArr[0][4] = v1;
	colorArr[1][0] = e5; colorArr[1][1] = e4;colorArr[1][2] = e3;colorArr[1][3] = e2;colorArr[1][4] = e1;
	colorArr[2][0] = b5; colorArr[2][1] = b4;colorArr[2][2] = b3;colorArr[2][3] = b2;colorArr[2][4] = b1;
	colorArr[3][0] = p5; colorArr[3][1] = p4;colorArr[3][2] = p3;colorArr[3][3] = p2;colorArr[3][4] = p1;
	//--------------------------------------------------------------------------
	setlocale(LC_ALL, "RUS");
	system("mode con cols=140 lines=70");
	HWND hWnd = GetConsoleWindow(); // получаем идентификатор окна
	HDC hDC = GetDC(hWnd); // получаем контекст отображения
	HPEN whitePen = GetStockPen(WHITE_PEN); //создаем перо для рисования сетки
	//HPEN hPen1 = CreatePen(PS_SOLID, 1, RGB(32, 7, 114));
	HPEN hPen2 = CreatePen(PS_SOLID, 0, RGB(110, 165, 110));
	HBRUSH fdad = CreateSolidBrush(RGB(255,255,255));
	//---------------------------------------------------------------------------
	grid myTable;// = { 6,80,80 };   на 15ой версии не работает(?)
				 /**std::cout << "Введите размер сетки (2 числа) и размерность ячейки через пробел \n";/**/
				 /*/cin >> myTable.width >> myTable.height >> myTable.size;/**/ //юзаем значения по умолчанию и не паримся
	/**SelectPen(hDC, whitePen);/*/SelectPen(hDC, hPen2);/**/   //это такой свитч для экспериментов
	DrawGrid(&hDC, myTable);
	COLORREF OPO = RGB(255, 255, 255);
	for (int i = 1;i<=myTable.width+1;i++)//залить для контраста
		for (int j=1;j <= myTable.height;j++)
		{
			PutDot(&hDC, i, j, myTable, 0, &OPO);
		}
	/**SelectPen(hDC, whitePen);/*/SelectPen(hDC, hPen2);/**/
	MyLine(&hDC, myTable, { 1,1 }, { 28,16 },colorArr);
	MyLine(&hDC, myTable, { 31,31 }, { 4,31 }, colorArr);
	//---------------------------------------------------------------------------
	DeleteObject(whitePen);
	DeleteObject(fdad);
	DeleteObject(hPen2);
	ReleaseDC(hWnd, hDC);
	system("pause");
	//---------------------------------------------------------------------------
	return 0;
}

//-----------------------------FUNCTIONAL-BLOCK---------------------------------

void PutDot(HDC *hDC, int x, int y, grid isGrid,int e, COLORREF isColor[5])
{
		int xL = SPACE_LEFT + (x - 1)*isGrid.size, xR = SPACE_LEFT + x * isGrid.size;
		int yT = SPACE_UP + (y - 1)*isGrid.size, yD = SPACE_UP + y * isGrid.size;
		if ((x > 0) && (y > 0) && (y <= isGrid.height) && (x <= isGrid.width))
		{
			HBRUSH myBrush = CreateSolidBrush(isColor[e]);
			SelectBrush(*hDC, myBrush);
			Rectangle(*hDC, xL, yT, xR, yD);
			DeleteObject(myBrush);
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
void MyLine(HDC *hDC, grid isGrid, dot aa, dot bb, COLORREF isColor[4][5])
{
	srand((int)time(NULL)*rand());
	int randNum = abs((rand()-1)%5);
	int x0, y0;// = min(aa.y, bb.y);
	int xLen = max(aa.x, bb.x) -min(aa.x, bb.x);int yLen = max(aa.y, bb.y) - min(aa.y, bb.y);
	bool xMore = xLen >= yLen;//вытянутость по x
	if(xMore)
	{
		if (aa.x >= bb.x) { x0 = bb.x;y0 = bb.y;xLen = aa.x - bb.x;yLen = aa.y - bb.y;}
		else { x0 = aa.x;y0 = aa.y;xLen = bb.x - aa.x;yLen = bb.y - aa.y; }
	}
	else
	{
		if (aa.y >= bb.y) { y0 = bb.y;x0 = bb.x;yLen = aa.x - bb.x;xLen = aa.y - bb.y;}
		else { y0 = aa.y;x0 = aa.x;yLen = bb.x - aa.x;xLen = bb.y - aa.y; }
	}
	if (xLen == 0) return;
	double tg = (double)yLen / xLen;
	for (int xCur = 0;xCur <= xLen;xCur++)
	{
		double yCur = tg * xCur;
		int y1 = ceil(yCur), y2 = floor(yCur);// округление вверх и вниз("в потолок" и "в пол")
		if (xMore)
		{			//можно сделать более гладкую функцию перехода к интенсивности
			PutDot(hDC, xCur + x0, y1 + y0, isGrid, abs((int)((y1 - yCur+1) * 2.5)), isColor[randNum]);// а если хотите норм варик - заменить аналогичный фрагмент на: (для всех 4хстрок)
			PutDot(hDC, xCur + x0, y2 + y0, isGrid, abs((int)((y2 - yCur+1) * 2.5)), isColor[randNum]);//abs((int)((y2 - yCur) * 5))
		}
		else
		{
			PutDot(hDC, y1 + x0, xCur + y0, isGrid, abs((int)((y1 - yCur+1) * 2.5)), isColor[randNum]);
			PutDot(hDC, y2 + x0, xCur + y0, isGrid, abs((int)((y2 - yCur+1) * 2.5)), isColor[randNum]);
		}
	}
}
