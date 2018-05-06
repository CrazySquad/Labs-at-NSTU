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

#define YELLOW_C RGB(255, 202, 64) //��� ����� �������� �����
#define PINK_C RGB(148, 4, 119)
#define RED_C RGB(255, 0, 0)
#define BLUE_C RGB(92, 204, 204)
#define GRIN_C RGB(152, 211, 13)
#define SPACE_LEFT 20   //��������� �������� �� �������� ������ ���� �������
#define SPACE_UP 300

//2 ���������� - ����� ��
struct dot
{
	int x;
	int y;
};

// ��� ����������� ��������� �����
struct grid
{
	unsigned int size = 14;
	unsigned int width = 32;
	unsigned int height = 32;
};

void PutDot(HDC *hDC, int x, int y, grid isGrid);// ������ ���������������� �����
void DrawGrid(HDC *hDC, grid isGrid); //������ ������ �����

									  //-----------------------------------MAIN---------------------------------------

void main()
{
	//---------------------------------------------------------------------------
	setlocale(LC_ALL, "RUS");
	system("mode con cols=140 lines=70");// ��������� �������
	HWND hWnd = GetConsoleWindow(); // �������� ������������� ����
	HDC hDC = GetDC(hWnd); // �������� �������� �����������
	HPEN whitePen = GetStockPen(WHITE_PEN); // ������� ���� ��� ��������� �����. ���� ��������� � ��������� ��������
	HBRUSH pinkBrush = CreateSolidBrush(PINK_C);// ��� ��� ����� ������� �����. ����� �������� �� ���� ������� �����(� ����� ������ - �����)
												//---------------------------------------------------------------------------
	SelectPen(hDC, whitePen);  // ����������� ����
	SelectBrush(hDC, pinkBrush);// � �����
	grid generalGrid;
	char quest = NULL;
	cout << "������������ ��������� �������� �������?{y or something}  ";cin >> quest;
	if (quest != 'y')
	{
		cout << "������� ������ ����� (2 �����) � ����������� ������ ����� ������ \n";// ������ ��� ~30 - ����� ��
		cin >> generalGrid.width >> generalGrid.height >> generalGrid.size;
	}
	DrawGrid(&hDC, generalGrid);
	for (bool oops = true;oops;)// ����� ����, ����� �� �������� ��� � ��������� ����� � if'�� ��� switch'��
	{
		oops = false;
		dot qDot;// = { 5,5 }; // ��� ���� �����
		cout << "� ����� ������ ����� ���������?(x,y)      ";
		cin >> qDot.x >> qDot.y;
		PutDot(&hDC, qDot.x, qDot.y, generalGrid);
		cout << "����������?{y or something}  ";cin >> quest; // "��� �����?" 
		oops = quest == 'y';
	}
	//---------------------------------------------------------------------------
	DeleteObject(whitePen);// �� ������ ��������� �� �����
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
	if ((xR>SPACE_LEFT) && (yD>SPACE_UP) && (yT<yMax) && (xL<xMax))// �������� �� �����������, ����� �� ��������� ����� ������ �� ��������
		Ellipse(*hDC, xL, yT, xR, yD);
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