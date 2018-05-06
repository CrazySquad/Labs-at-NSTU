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
void Cirle(HDC *hDC, grid isGrid, dot middle, int radius);// ���������� �� ��������� ������ � �������
void LineBrez(HDC *hDC, grid isGrid, dot aa, dot bb);// ������� ������� ����������
void LineCDA(HDC *hDC, grid isGrid, dot b, dot e);// ������� ������� ���
void DrawGrid(HDC *hDC, grid isGrid);

//-----------------------------------MAIN---------------------------------------

int main()
{
	//---------------------------------------------------------------------------
	setlocale(LC_ALL, "RUS");
	system("mode con cols=140 lines=70");
	HWND hWnd = GetConsoleWindow(); // �������� ������������� ����
	HDC hDC = GetDC(hWnd); // �������� �������� �����������
	HPEN whitePen = GetStockPen(WHITE_PEN); //������� ���� ��� ��������� �����
	HPEN hPen1 = CreatePen(PS_SOLID, 1, RGB(32, 7, 114));
	HPEN hPen2 = CreatePen(PS_SOLID, 1, RGB(110, 165, 110));
	HBRUSH grinBrush = CreateSolidBrush(GRIN_C);
	HBRUSH purpleBrush = CreateSolidBrush(PURPLE_C);
	HBRUSH orangeBrush = CreateSolidBrush(ORANGE_C);
	//---------------------------------------------------------------------------
	grid totalGrid;     /** - ���������� �������� ��������� '/' � ������ �������������/**/
						/**std::cout << "������� ������ ����� (2 �����) � ����������� ������ ����� ������ \n";// ������ ��� ~12 - ����� ��
						cin >> totalGrid.width >> totalGrid.height >> totalGrid.size;/**/ //���������� ������, �����-�������������
	SelectPen(hDC, whitePen);
	DrawGrid(&hDC, totalGrid);
	short int question;
	std::cout << "\n ��� ����������?   ����� :1 -������ ���������� ���,\n 2 -������ ���������� ���������� 3 -����������\n";
	cin >> question;
	SelectPen(hDC, hPen1);
	switch (question)
	{
	case 1:
	{
		SelectBrush(hDC, purpleBrush);// ��� ������� ���� - ���� ����
		LineCDA(&hDC, totalGrid, { 10, 15 }, { 15,10 });// �� ���� ����� �������� ����
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
		std::cout << "������� ��������� �� ������";
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
	int trueRadius = radius / sqrt(2);// ��������� ������ �� ���� [0;PI/8]
	while (abs(x) >= trueRadius)
	{
		PutDot(hDC, xMiddle + x, yMiddle + y, isGrid);//�������� 8 ���
		PutDot(hDC, xMiddle + x, yMiddle - y, isGrid);//���������� ���������� ������ ��� ����������� ��������
		PutDot(hDC, xMiddle - x, yMiddle + y, isGrid);
		PutDot(hDC, xMiddle - x, yMiddle - y, isGrid);
		PutDot(hDC, xMiddle + y, yMiddle + x, isGrid);
		PutDot(hDC, xMiddle + y, yMiddle - x, isGrid);
		PutDot(hDC, xMiddle - y, yMiddle + x, isGrid);
		PutDot(hDC, xMiddle - y, yMiddle - x, isGrid);
		int dh = x * x + (y - 1)*(y - 1) - radius * radius;// ����� ���� �����
		int dc = (x - 1)*(x - 1) + (y - 1)*(y - 1) - radius * radius;// ����� ���� �����
		if (abs(dh) > abs(dc)) x--;// ����� �� �������������� ����� ������ �������� ��� ��������� ����������
		y--;//���
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
	if (dy > dx) { int t = dy; dy = dx; dx = t; ch = 1; } // ������ ������� x � y
	dx2 = dx << 1; dy2 = dy << 1; // dx2 = 2*dx; dy2 = 2*dy;
	e = dy2 - dx; // ��������� �������� ������;
	for (int i = 0; i <= dx + dy;i++)
	{
		PutDot(hDC, aa.x, aa.y, isGrid);
		if (e > 0) { if (ch) aa.x += bb.x; else aa.y += bb.y; e -= dx2; }
		else { if (ch) aa.y += bb.y; else aa.x += bb.x; e += dy2; }
	}
}
void LineCDA(HDC *hDC, grid isGrid, dot b, dot e)
{
	if (b.x > e.x)// ��������� ������ � ����� �� ����� - �
	{
		dot temp = b;
		b = e;
		e = temp;
	}
	double step = (double)(e.y - b.y) / (e.x - b.x); //�� ������� ��� ���������� � 
	int x = b.x;
	int y = b.y;
	for (double yDouble = b.y; (x <= e.x); x++)//�� ������ ������������� � ���������� ������ 1 �, ������� � ��������� �� ��������� ������ ����� �������
	{
		PutDot(hDC, x, y, isGrid);
		yDouble += step;
		y = round(yDouble);
	}
}
void DrawGrid(HDC *hDC, grid isGrid)
{
	int x, y, x1, y1;
	//������������� ��������� ��������� ����
	x = x1 = SPACE_LEFT;
	y = y1 = SPACE_UP;
	//��������� �� y
	for (unsigned int i = 0; i <= isGrid.height; i++)
	{
		MoveToEx(*hDC, x, y, NULL);
		LineTo(*hDC, x + (isGrid.width*isGrid.size), y);
		y += (isGrid.size);
	}
	//��������� �� x
	for (unsigned int j = 0; j <= isGrid.width; j++)
	{
		MoveToEx(*hDC, x1, y1, NULL);
		LineTo(*hDC, x1, y1 + (isGrid.height*isGrid.size));
		x1 += (isGrid.size);
	}
}