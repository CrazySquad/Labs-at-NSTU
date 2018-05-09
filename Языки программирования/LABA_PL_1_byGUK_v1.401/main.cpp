// Lab_PL_2_byGUK.cpp: ���������� ����� ����� ��� ����������� ����������.
//

#include "stdafx.h"
#include "stdlib.h"
#include "locale.h"
#include "Book.h"
#include "BookList.h"
#define MAX_LEN 20
#define filename1 "C:/.../Source.txt" //�������� �� ����������!!!
#define amount_of_books 20  //���� ������ �� �������������
/**
* ��������
*/
void TaskMethod(BookList* bL)
{
	printf("����� e - ��������� ������,a - ������ �� ������,p - ������ �� ������������\n,i - �������� ���� ������,y - ����������� �� ��������� ����\n");
	char quest = NULL;
	scanf("%c", &quest);
	switch (quest)
	{
	case 'e':
	{
		getchar();
		break;
	}
	case 'a':
	{
		printf("����� �����?   ");
		char popo[MAX_LEN];
		scanf("%s", &popo);
		bL->ListByAuthor(popo);
		getchar();
		TaskMethod(bL);
		break;
	}
	case 'p':
	{
		printf("������������ �����?   ");
		char popo[MAX_LEN];
		scanf("%s", &popo);
		bL->ListByPublished(popo);
		getchar();
		TaskMethod(bL);
		break;
	}
	case 'i':
	{	
		bL->PrintAllInfo();
		getchar();
		TaskMethod(bL);
		break;
	}
	case 'y':
	{
		int year = 0;
		printf("��� �����?   ");
		scanf("%d", &year);
		bL->ListByYear(year);
		getchar();
		TaskMethod(bL);
		break;
	}
	default:
	{
		printf("� ���� � ���� ������ �����...\n");
		getchar();
		TaskMethod(bL);
		break;
	}
	}
}

/**
* ����� �����
*/
int main()
{
	setlocale(LC_ALL, "RUS");
	system("mode con cols=90 lines=60");
	FILE* SourceTEXT;
	SourceTEXT = fopen(filename1, "r");
	BookList* testBookList = new BookList(SourceTEXT);
	TaskMethod(testBookList);
	testBookList->~BookList();
	fclose(SourceTEXT);
	system("pause");
	return 0;
}

